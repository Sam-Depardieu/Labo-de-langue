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
    auto inputDevices = QMediaDevices::audioInputs();

    qDebug() << "Périphériques d'entrée disponibles :";
    for (const QAudioDevice &device : inputDevices) {
        qDebug() << "ENTREE :" << device.id() << "," << device.description();
    }

    // Config audio mono 48kHz 16 bits signé (compatible USB audio mono)
    QAudioFormat format;
    format.setSampleRate(48000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    // Recherche périphérique USB correspondant (ex: "Audio Adapter")
    QAudioDevice inputDeviceInfo;
    bool found = false;
    for (const QAudioDevice &device : inputDevices) {
        if (device.description().contains("Audio Adapter")) {
            inputDeviceInfo = device;
            found = true;
            break;
        }
    }

    if (!found) {
        qWarning() << "❌ Aucun périphérique USB Audio trouvé.";
        return;
    }

    if (!inputDeviceInfo.isFormatSupported(format)) {
        qWarning() << "❌ Format audio non supporté par le périphérique sélectionné.";
        return;
    }

    audioInput = new QAudioSource(inputDeviceInfo, format, this);

    // Initialisation sortie audio avec le même format
    QAudioDevice outputDeviceInfo = QMediaDevices::defaultAudioOutput();
    if (!outputDeviceInfo.isFormatSupported(format)) {
        qWarning() << "❌ Format audio non supporté par le périphérique de sortie.";
        return;
    }
    audioOutput = new QAudioSink(outputDeviceInfo, format, this);

    connect(audioInput, &QAudioSource::stateChanged, this, &Student::onAudioSourceStateChanged);

    connectToGroup();

    initializeAudioCommunication();

    connect(&sendTimer, &QTimer::timeout, this, &Student::captureAndSendAudio);
    sendTimer.start(20);
}

void Student::initializeAudioCommunication()
{
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

    connect(&udpSocket, &QUdpSocket::readyRead, this, &Student::receiveAudio);

    if (!sendTimer.isActive()) {
        sendTimer.start(20);
    }

    qDebug() << "Communication audio initialisée.";
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
        qWarning() << "Échec de la jointure du groupe multicast:" << serverAddress.toString()
                   << "| Erreur socket:" << udpSocket.errorString();
        return;
    }

    qDebug() << "Connecté au groupe multicast" << group << "@" << serverAddress.toString() << ":" << serverPort;
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

        if (audioOutput->state() != QAudio::ActiveState) {
            outputDevice = audioOutput->start();
        }

        if (outputDevice) {
            outputDevice->write(datagram);
        }
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
    qDebug() << "🔊 Audio démuté pour l'élève";  // <-- texte corrigé

    if (audioInput) {
        audioInput->start();
    }
    if (audioOutput) {
        audioOutput->start();
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
