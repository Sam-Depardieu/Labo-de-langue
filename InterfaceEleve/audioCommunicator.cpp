#include "audioCommunicator.h"
#include <QMediaDevices>
#include <QDebug>

Student::Student(const QString &groupName, const QHostAddress &groupAddress, quint16 groupPort, QObject *parent)
    : QObject(parent),
    group(groupName),
    groupAddress(groupAddress),
    groupPort(groupPort),
    serverAddress(groupAddress),
    serverPort(groupPort),
    udpSocket(this)
{
    // Configuration audio (à adapter si besoin)
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleFormat(QAudioFormat::Float);

    QAudioDevice inputDeviceInfo = QMediaDevices::defaultAudioInput();
    QAudioDevice outputDeviceInfo = QMediaDevices::defaultAudioOutput();

    if (!inputDeviceInfo.isFormatSupported(format)) {
        qWarning() << "Format audio en entrée non supporté";
        return;
    }
    if (!outputDeviceInfo.isFormatSupported(format)) {
        qWarning() << "Format audio en sortie non supporté";
        return;
    }

    audioInput = new QAudioSource(inputDeviceInfo, format, this);
    audioOutput = new QAudioSink(outputDeviceInfo, format, this);

    connect(audioInput, &QAudioSource::stateChanged, this, &Student::onAudioSourceStateChanged);

    // Connecte la socket UDP au groupe multicast initial
    connectToGroup();

    // Timer pour envoyer l'audio régulièrement (toutes les 20ms)
    connect(&sendTimer, &QTimer::timeout, this, &Student::captureAndSendAudio);
    sendTimer.start(20);
}

Student::~Student()
{
    stopAudio();

    if (audioInput) {
        delete audioInput;
        audioInput = nullptr;
    }
    if (audioOutput) {
        delete audioOutput;
        audioOutput = nullptr;
    }
}

void Student::connectToGroup()
{
    // Quitte l'ancien groupe si nécessaire
    if (udpSocket.state() == QAbstractSocket::BoundState) {
        udpSocket.leaveMulticastGroup(serverAddress);
        udpSocket.close();
    }

    if (!udpSocket.bind(QHostAddress::AnyIPv4, serverPort,
                        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        qWarning() << "Échec de la liaison UDP sur le port multicast:" << serverPort;
        return;
    }

    if (!udpSocket.joinMulticastGroup(serverAddress)) {
        qWarning() << "Échec de la jointure du groupe multicast:" << serverAddress.toString();
        return;
    }

    qDebug() << "Connecté au groupe multicast" << group << "@" << serverAddress.toString() << ":" << serverPort;

    connect(&udpSocket, &QUdpSocket::readyRead, this, &Student::receiveAudio);
}

void Student::captureAndSendAudio()
{
    if (!audioInput)
        return;

    if (!inputDevice) {
        inputDevice = audioInput->start();
        if (!inputDevice) {
            qWarning() << "Impossible de démarrer la capture audio";
            return;
        }
    }

    // Lit toutes les données disponibles sur le QIODevice
    while (inputDevice->bytesAvailable() > 0) {
        QByteArray audioData = inputDevice->read(inputDevice->bytesAvailable());
        if (!audioData.isEmpty()) {
            udpSocket.writeDatagram(audioData, serverAddress, serverPort);
        }
    }
}


void Student::receiveAudio()
{
    if (!audioOutput) return;

    while (udpSocket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(udpSocket.pendingDatagramSize()));

        udpSocket.readDatagram(datagram.data(), datagram.size());

        if (!datagram.isEmpty()) {
            if (audioOutput->state() != QAudio::ActiveState) {
                outputDevice = audioOutput->start();
            }
            if (outputDevice) {
                outputDevice->write(datagram);
            }
        }
    }
}

void Student::processCommands()
{
    while (udpSocket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(udpSocket.pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;
        udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString message = QString::fromUtf8(datagram).trimmed();
        qDebug() << "[Student] Commande reçue :" << message;

        if (message.startsWith("portGroup,")) {
            QStringList parts = message.split(',');
            if (parts.size() == 2) {
                bool ok;
                quint16 newPort = parts[1].toUShort(&ok);
                if (ok && newPort != serverPort) {
                    qDebug() << "Changement de port audio vers :" << newPort;
                    changeAudioGroup(serverAddress, newPort);
                }
            }
        } else if (message.startsWith("groupChange,")) {
            QStringList parts = message.split(',');
            if (parts.size() == 3) {
                QHostAddress newAddress(parts[1]);
                bool ok;
                quint16 newPort = parts[2].toUShort(&ok);
                if (ok && (newAddress != serverAddress || newPort != serverPort)) {
                    qDebug() << "Changement de groupe multicast vers :" << newAddress.toString() << ":" << newPort;
                    changeAudioGroup(newAddress, newPort);
                }
            }
        }
        // Autres commandes à ajouter ici...
    }
}

void Student::changeAudioGroup(const QHostAddress& newAddress, quint16 newPort)
{
    if (udpSocket.state() == QAbstractSocket::BoundState) {
        udpSocket.leaveMulticastGroup(serverAddress);
        udpSocket.close();
    }

    serverAddress = newAddress;
    serverPort = newPort;

    if (!udpSocket.bind(QHostAddress::AnyIPv4, serverPort,
                        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        qWarning() << "Erreur de liaison UDP sur le port multicast:" << serverPort;
        return;
    }

    if (!udpSocket.joinMulticastGroup(serverAddress)) {
        qWarning() << "Erreur lors de la jointure du groupe multicast:" << serverAddress.toString();
        return;
    }

    qDebug() << "Rejoint le groupe multicast" << serverAddress.toString() << "port" << serverPort;
}

void Student::onAudioSourceStateChanged(QAudio::State newState)
{
    switch (newState) {
    case QAudio::StoppedState:
        qWarning() << "La capture audio est arrêtée.";
        break;
    case QAudio::IdleState:
        qDebug() << "La capture audio est inactive.";
        break;
    case QAudio::ActiveState:
        qDebug() << "La capture audio est active.";
        break;
    default:
        qWarning() << "État inconnu de la capture audio.";
        break;
    }
}

void Student::initializeAudioCommunication()
{
    // Configurer ou redémarrer la capture audio
    if (audioInput) {
        if (inputDevice) {
            inputDevice->close();
            inputDevice = nullptr;
        }
        inputDevice = audioInput->start();
        if (!inputDevice) {
            qWarning() << "Impossible de démarrer la capture audio";
            return;
        }
    }

    // Configurer la sortie audio
    if (audioOutput) {
        if (outputDevice) {
            outputDevice->close();
            outputDevice = nullptr;
        }
        outputDevice = audioOutput->start();
        if (!outputDevice) {
            qWarning() << "Impossible de démarrer la sortie audio";
            return;
        }
    }

    // Connecter la socket UDP (si ce n’est pas déjà fait)
    connect(&udpSocket, &QUdpSocket::readyRead, this, &Student::receiveAudio);

    // Démarrer le timer qui va capturer et envoyer régulièrement l’audio
    if (!sendTimer.isActive()) {
        sendTimer.start(20); // toutes les 20ms (ou ajuster selon besoins)
    }

    qDebug() << "Communication audio initialisée.";
}

void Student::muteAudio()
{
    qDebug() << "🔇 Audio muté pour l'élève";

    if (audioInput) {
        audioInput->stop();  // Arrêter la capture micro
    }

    if (audioOutput) {
        audioOutput->stop(); // Couper la diffusion audio
    }

    isMuted = true;
}

void Student::unmuteAudio()
{
    qDebug() << "🔇 Audio muté pour l'élève";

    if (audioInput) {
        audioInput->start();  // Arrêter la capture micro
    }

    if (audioOutput) {
        audioOutput->start(); // Couper la diffusion audio
    }

    isMuted = false;
}

void Student::stopAudio()
{
    if (audioInput) {
        audioInput->stop();
    }
    if (audioOutput) {
        audioOutput->stop();
    }
    if (inputDevice) {
        inputDevice->close();
        inputDevice = nullptr;
    }
    if (outputDevice) {
        outputDevice->close();
        outputDevice = nullptr;
    }
}
