#include "audioCommunicator.h"
#include <QDebug>
#include <QMediaDevices>

Student::Student(QObject* parent)
    : QObject(parent),
    udpSocketReceive(new QUdpSocket(this)),
    udpSocketSend(new QUdpSocket(this)),
    isMuted(false)
{
    connect(udpSocketReceive, &QUdpSocket::readyRead, this, &Student::onReadyRead);
}

Student::~Student()
{
    stopAudio();

    if (udpSocketSend->isOpen()) {
        udpSocketSend->close();
    }
    if (udpSocketReceive->isOpen()) {
        udpSocketReceive->close();
    }
}

// Configure les ports UDP envoyeur et receveur (receveur = envoyeur + 30)
void Student::configureAudioPorts(quint16 portEnvoyeur, quint16 portReceveur)
{
    // Ferme les sockets si déjà ouvertes
    if (udpSocketSend->isOpen()) udpSocketSend->close();
    if (udpSocketReceive->isOpen()) udpSocketReceive->close();

    this->portEnvoyeur = portEnvoyeur;
    this->portReceveur = portReceveur;

    // Bind uniquement la réception
    bool bindOk = udpSocketReceive->bind(QHostAddress::AnyIPv4, portReceveur);
    if (!bindOk) {
        qDebug() << "[Student] Échec du bind UDP réception sur port" << portReceveur;
        return;
    }

    qDebug() << "[Student] Ports configurés - Envoi:" << portEnvoyeur << " Réception:" << portReceveur;
}

void Student::handleCommand(const QString& cmd)
{
    if (cmd.startsWith("portGroup,")) {
        bool ok = false;
        quint16 port = cmd.mid(QString("portGroup,").length()).toUShort(&ok);
        if (ok) {
            setGroupPort(port);
        } else {
            qDebug() << "[Student] Port invalide dans commande portGroup:" << cmd;
        }
    }
}

void Student::setGroupPort(quint16 port)
{
    // groupPort = port envoyeur, port receveur = port + 30
    groupPort = port;
    quint16 portReceive = port + 30;

    configureAudioPorts(groupPort, portReceive);

    qDebug() << "[Student] Groupe port défini. Envoi =" << groupPort << ", Réception =" << portReceive;
}

void Student::setServerAddress(const QHostAddress& address, quint16 port)
{
    serverAddress = address;
    serverPort = port;
}

QAudioFormat Student::getAudioFormat() const
{
    QAudioFormat format;
    format.setSampleRate(44100);              // 44.1 kHz
    format.setChannelCount(1);                // Mono
    format.setSampleFormat(QAudioFormat::Int16); // 16 bits int
    return format;
}

void Student::startAudio()
{
    if (audioInput || audioOutput) {
        stopAudio();
    }

    QAudioFormat format = getAudioFormat();

    QAudioDevice inputDevice = QMediaDevices::defaultAudioInput();
    QAudioDevice outputDevice = QMediaDevices::defaultAudioOutput();

    if (!inputDevice.isFormatSupported(format)) {
        qDebug() << "[Student] Format audio non supporté par l'entrée, utilisation par défaut";
        // Tu peux choisir un format alternatif ou arrêter ici
        return;
    }

    if (!outputDevice.isFormatSupported(format)) {
        qDebug() << "[Student] Format audio non supporté par la sortie, utilisation par défaut";
        return;
    }

    audioInput = new QAudioSource(inputDevice, format, this);
    audioInputDevice = audioInput->start();
    if (!audioInputDevice) {
        qDebug() << "[Student] Impossible de démarrer la capture audio";
        return;
    }
    connect(audioInputDevice, &QIODevice::readyRead, this, &Student::onAudioDataCaptured);

    audioOutput = new QAudioSink(outputDevice, format, this);
    audioOutputDevice = audioOutput->start();
    if (!audioOutputDevice) {
        qDebug() << "[Student] Impossible de démarrer la sortie audio";
        return;
    }

    qDebug() << "[Student] Capture et lecture audio démarrées";
}

void Student::configureWithTeacher(const QHostAddress& teacherAddress, quint16 teacherReceivePort) //Test
{
    // Prof envoie sur 5999 → élève reçoit sur 5999
    // Prof reçoit sur 5998 ← élève envoie vers 5998

    quint16 receivePort = 5999;
    quint16 sendPort = teacherReceivePort; // 5998 en général

    setServerAddress(teacherAddress, sendPort);
    configureAudioPorts(sendPort, receivePort);

    qDebug() << "[Student] Connexion configurée avec le professeur : envoyer vers" << teacherAddress.toString() << ":" << sendPort << ", écouter sur port" << receivePort;
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
    if (!audioInputDevice || isMuted)
        return;

    QByteArray audioData = audioInputDevice->readAll();

    if (!serverAddress.isNull() && portEnvoyeur != 0) {
        qint64 sent = udpSocketSend->writeDatagram(audioData, serverAddress, portEnvoyeur);
        if (sent == -1) {
            qDebug() << "[Student] Erreur lors de l'envoi des données audio";
        }
    }
}

void Student::onReadyRead()
{
    while (udpSocketReceive->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(int(udpSocketReceive->pendingDatagramSize()));

        QHostAddress sender;
        quint16 senderPort;

        udpSocketReceive->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

        if (audioOutputDevice) {
            audioOutputDevice->write(buffer);
        }

        emit audioDataReceived(buffer);
    }
}

void Student::mute()
{
    isMuted = true;
    qDebug() << "[Student] Microphone MUTED";
}

void Student::unmute()
{
    isMuted = false;
    qDebug() << "[Student] Microphone UNMUTED";
}
