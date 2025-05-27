#include "audioCommunicator.h"
#include <QMediaDevices>
#include <QDebug>

Student::Student(const QString &groupName, const QHostAddress &serverAddress, quint16 serverPort, QObject *parent)
    : QObject(parent),
    group(groupName),
    serverAddress(serverAddress),
    serverPort(serverPort),
    udpSocket(this),
    audioInput(nullptr),
    audioOutput(nullptr),
    inputDevice(nullptr),
    outputDevice(nullptr),
    isMuted(false)
{
    // Format audio
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

    // Bind la socket UDP sur un port local dynamique (0)
    if (!udpSocket.bind(QHostAddress::AnyIPv4, 0,
                        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        qWarning() << "Erreur de liaison UDP locale pour réception audio";
        return;
    }

    connect(&udpSocket, &QUdpSocket::readyRead, this, &Student::receiveAudio);

    // Timer pour envoyer l'audio régulièrement (toutes les 20ms)
    connect(&sendTimer, &QTimer::timeout, this, &Student::captureAndSendAudio);
    sendTimer.start(20);

    qDebug() << "Student créé, UDP bind sur port local" << udpSocket.localPort();
    qDebug() << "Audio envoyé vers" << serverAddress.toString() << "port" << serverPort;
}

// Capture audio et envoi vers l’adresse du prof + port du groupe
void Student::captureAndSendAudio()
{
    if (!audioInput) return;

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

void Student::connectToGroup(const QHostAddress& profAddress, quint16 profPort)
{
    if (udpSocket.state() == QAbstractSocket::BoundState) {
        udpSocket.close();
    }

    // Bind local sur port aléatoire (0) ou fixe (ex: 12345)
    if (!udpSocket.bind(QHostAddress::AnyIPv4, 0,
                        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        qWarning() << "Erreur bind local UDP pour réception audio";
        return;
    }

    serverAddress = profAddress;
    serverPort = profPort;

    qDebug() << "[Student] Bind local sur port" << udpSocket.localPort();
    qDebug() << "[Student] Audio envoyé vers" << serverAddress.toString() << ":" << serverPort;

    connect(&udpSocket, &QUdpSocket::readyRead, this, &Student::receiveAudio);
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

void Student::changeAudioGroup(const QHostAddress& newServerAddress, quint16 newServerPort)
{
    serverAddress = newServerAddress;
    serverPort = newServerPort;
    qDebug() << "Changement du serveur audio vers" << serverAddress.toString() << "port" << serverPort;
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
    sendTimer.stop();
}

void Student::muteAudio()
{
    isMuted = true;
    stopAudio();
    qDebug() << "Audio muté";
}

void Student::unmuteAudio()
{
    isMuted = false;
    initializeAudioCommunication();
    qDebug() << "Audio démuté";
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

    if (!sendTimer.isActive()) {
        sendTimer.start(20);
    }
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
