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
    // 🔍 Sélectionner le périphérique USB Audio
    const auto inputDevices = QMediaDevices::audioInputs();
    QAudioDevice selectedInputDevice;
    for (const QAudioDevice &device : inputDevices) {
        qDebug() << "🎤 Périphérique audio dispo:" << device.description();
        if (device.description().contains("USB Audio", Qt::CaseInsensitive)) {
            selectedInputDevice = device;
            break;
        }
    }

    if (!selectedInputDevice.isNull()) {
        qDebug() << "✅ Périphérique sélectionné:" << selectedInputDevice.description();
    } else {
        qWarning() << "❌ Aucun périphérique USB Audio trouvé.";
        return;
    }

    // 🎚 Format audio compatible Raspberry Pi
    QAudioFormat format;
    format.setSampleRate(16000);                  // 16 kHz
    format.setChannelCount(1);                    // Mono
    format.setSampleFormat(QAudioFormat::Int16);  // Format standard

    if (!selectedInputDevice.isFormatSupported(format)) {
        qWarning() << "❌ Format audio en entrée non supporté par le périphérique.";
        return;
    }

    // 🎧 Périphérique de sortie par défaut (optionnel)
    QAudioDevice outputDevice = QMediaDevices::defaultAudioOutput();
    if (!outputDevice.isFormatSupported(format)) {
        qWarning() << "❌ Format audio en sortie non supporté.";
        return;
    }

    // 🎤 Instanciation des flux audio
    audioInput = new QAudioSource(selectedInputDevice, format, this);
    audioOutput = new QAudioSink(outputDevice, format, this);

    connect(audioInput, &QAudioSource::stateChanged, this, &Student::onAudioSourceStateChanged);

    // 🌐 Connexion multicast
    connectToGroup();

    // ⏱ Timer pour envoyer l'audio toutes les 20ms
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
    while (udpSocket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(udpSocket.pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;
        udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        qDebug() << "📥 Réception audio de" << sender.toString() << ":" << senderPort
                 << "| taille:" << datagram.size();

        if (!audioOutput) return;
        if (audioOutput->state() != QAudio::ActiveState)
            outputDevice = audioOutput->start();
        if (outputDevice)
            outputDevice->write(datagram);
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
