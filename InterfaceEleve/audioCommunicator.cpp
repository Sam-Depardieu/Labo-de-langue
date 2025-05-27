#include "audioCommunicator.h"
#include <QDebug>
#include <QMediaDevices>

Student::Student(QObject* parent)
    : QObject(parent),
    udpSocket(new QUdpSocket(this)),
    groupPort(0),
    serverPort(0),
    audioInput(nullptr),
    audioOutput(nullptr),
    audioInputDevice(nullptr),
    audioOutputDevice(nullptr)
{
    connect(udpSocket, &QUdpSocket::readyRead, this, &Student::onReadyRead);
}

Student::~Student()
{
    stopAudio();
    if (udpSocket->isOpen()) {
        udpSocket->close();
    }
}

void Student::handleCommand(const QString& cmd)
{
    if (cmd.startsWith("portGroup,")) {
        bool ok = false;
        quint16 port = cmd.mid(QString("portGroup,").length()).toUShort(&ok);
        if (ok) {
            setGroupPort(port);
        }
    }
}

void Student::setGroupPort(quint16 port)
{
    if (udpSocket->isOpen()) {
        udpSocket->close();
    }

    groupPort = port;

    bool success = udpSocket->bind(QHostAddress::AnyIPv4, groupPort);
    if (!success) {
        qWarning() << "Impossible de binder sur le port UDP" << groupPort;
        return;
    }
    qDebug() << "Student bind sur port UDP groupe:" << groupPort;
}

void Student::setServerAddress(const QHostAddress& address, quint16 port)
{
    serverAddress = address;
    serverPort = port;
}

QAudioFormat Student::getAudioFormat() const
{
    QAudioFormat format;
    format.setSampleRate(44100);          // 44.1 kHz
    format.setChannelCount(1);            // Mono
    format.setSampleFormat(QAudioFormat::Int16); // Qt6 change ici
    return format;
}

void Student::startAudio()
{
    if (audioInput || audioOutput) {
        stopAudio();
    }

    QAudioFormat format = getAudioFormat();

    // Choix des périphériques audio avec Qt6
    QAudioDevice inputDevice = QMediaDevices::defaultAudioInput();
    QAudioDevice outputDevice = QMediaDevices::defaultAudioOutput();

    if (!inputDevice.isFormatSupported(format)) {
        qWarning() << "Format audio non supporté par l'entrée, utilisation du format par défaut";
        format = inputDevice.nearestFormat(format);
    }

    if (!outputDevice.isFormatSupported(format)) {
        qWarning() << "Format audio non supporté par la sortie, utilisation du format par défaut";
        format = outputDevice.nearestFormat(format);
    }

    audioInput = new QAudioInput(inputDevice, format, this);
    audioInputDevice = audioInput->start();

    if (!audioInputDevice) {
        qWarning() << "Impossible de démarrer la capture audio";
        return;
    }
    connect(audioInputDevice, &QIODevice::readyRead, this, &Student::onAudioDataCaptured);

    audioOutput = new QAudioOutput(outputDevice, format, this);
    audioOutputDevice = audioOutput->start();

    if (!audioOutputDevice) {
        qWarning() << "Impossible de démarrer la sortie audio";
        return;
    }

    qDebug() << "Capture et lecture audio démarrées";
}

void Student::stopAudio()
{
    if (audioInput) {
        audioInput->stop();
        audioInput->deleteLater();
        audioInput = nullptr;
    }
    if (audioOutput) {
        audioOutput->stop();
        audioOutput->deleteLater();
        audioOutput = nullptr;
    }
    audioInputDevice = nullptr;
    audioOutputDevice = nullptr;
}

void Student::onAudioDataCaptured()
{
    if (!audioInputDevice)
        return;

    QByteArray audioData = audioInputDevice->readAll();

    if (!serverAddress.isNull() && serverPort != 0) {
        qint64 sent = udpSocket->writeDatagram(audioData, serverAddress, serverPort);
        if (sent == -1) {
            qWarning() << "Erreur lors de l'envoi des données audio";
        }
    }
}

void Student::onReadyRead()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(int(udpSocket->pendingDatagramSize()));

        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

        if (audioOutputDevice) {
            audioOutputDevice->write(buffer);
        }

        emit audioDataReceived(buffer);
    }
}
