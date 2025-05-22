#include "audioCommunicator.h"

Student::Student(QObject* parent)
    : QObject(parent),
    context(1)
{
    inputDevice = QMediaDevices::defaultAudioInput();
    outputDevice = QMediaDevices::defaultAudioOutput();
    startAudio();

    connect(&sendTimer, &QTimer::timeout, this, &Student::sendAudioData);
    connect(&receiveTimer, &QTimer::timeout, this, &Student::receiveAudioData);
    connect(&udpSocket, &QUdpSocket::readyRead, this, &Student::handleCommand);

    // Écoute les commandes UDP du professeur
    udpSocket.bind(5557, QUdpSocket::ShareAddress);
}

void Student::setIP(const QString& ip) {
    studentIp = ip;
}

QString Student::getIP() const {
    return studentIp;
}

void Student::setGroupPort(int port) {
    if (portGroupAudio != -1) {
        stopAudio();
        closeZMQ();
    }

    portGroupAudio = port;
    setupZMQ();
    startAudio();
}

void Student::setupZMQ() {
    try {
        // PUSH pour envoyer
        pushSocket = new zmq::socket_t(context, ZMQ_PUSH);
        pushSocket->connect(("tcp://localhost:" + QString::number(portGroupAudio)).toStdString());

        // PULL pour recevoir
        pullSocket = new zmq::socket_t(context, ZMQ_PULL);
        pullSocket->connect(("tcp://localhost:" + QString::number(portGroupAudio + 1)).toStdString());
    } catch (const zmq::error_t& e) {
        qCritical() << "Erreur ZMQ (setup) :" << e.what();
    }
}

void Student::closeZMQ() {
    if (pushSocket) {
        pushSocket->close();
        delete pushSocket;
        pushSocket = nullptr;
    }
    if (pullSocket) {
        pullSocket->close();
        delete pullSocket;
        pullSocket = nullptr;
    }
}

void Student::startAudio() {
    QAudioFormat format;
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    if (!inputDevice.isNull()) {
        audioSource = new QAudioSource(inputDevice, format);
        audioInput = audioSource->start();
    }

    if (!outputDevice.isNull()) {
        audioSink = new QAudioSink(outputDevice, format);
        audioOutput = audioSink->start();
    }

    sendTimer.start(100);
    receiveTimer.start(100);
}

void Student::stopAudio() {
    sendTimer.stop();
    receiveTimer.stop();

    if (audioSource) {
        audioSource->stop();
        delete audioSource;
        audioSource = nullptr;
    }
    if (audioSink) {
        audioSink->stop();
        delete audioSink;
        audioSink = nullptr;
    }
}

// Envoi périodique de l'audio au groupe
void Student::sendAudioData() {
    if (!audioInput) {
        qDebug() << "[Student] Aucun périphérique d'entrée audio.";
        return;
    }

    if (isMuted) {
        qDebug() << "[Student] Microphone muet - aucune donnée envoyée.";
        return;
    }

    if (!pushSocket) {
        qDebug() << "[Student] Socket PUSH non initialisée.";
        return;
    }

    QByteArray data = audioInput->readAll();
    if (data.isEmpty()) {
        qDebug() << "[Student] Aucun audio lu depuis le micro.";
        return;
    }

    qDebug() << "[Student] Envoi de" << data.size() << "octets audio au groupe (port:" << portGroupAudio << ")";

    try {
        zmq::message_t message(data.constData(), data.size());
        pushSocket->send(message, zmq::send_flags::none);
    } catch (const zmq::error_t& e) {
        qWarning() << "[Student] Erreur lors de l'envoi audio via ZMQ:" << e.what();
    }
}


// Réception de l'audio du groupe
void Student::receiveAudioData() {
    if (!pullSocket) {
        qDebug() << "[Student] Socket PULL non initialisée.";
        return;
    }

    if (!audioOutput) {
        qDebug() << "[Student] Aucun périphérique de sortie audio.";
        return;
    }

    zmq::message_t message;
    zmq::recv_result_t result = pullSocket->recv(message, zmq::recv_flags::dontwait);

    if (!result) {
        qDebug() << "[Student] Aucun flux audio reçu à ce cycle.";
        return;
    }

    QByteArray data(static_cast<char*>(message.data()), message.size());
    qDebug() << "[Student] Reçu" << data.size() << "octets audio du groupe (port:" << portGroupAudio << ")";

    qint64 bytesWritten = audioOutput->write(data);
    if (bytesWritten <= 0) {
        qWarning() << "[Student] Échec lors de l'écriture de l'audio sur la sortie.";
    }
}


// Réception des commandes UDP
void Student::handleCommand() {
    while (udpSocket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 port;
        udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &port);

        QString msg = QString::fromUtf8(datagram).trimmed();
        qDebug() << "[Student] Commande reçue :" << msg;

        if (msg == "mute") {
            isMuted = true;
        } else if (msg == "unmute") {
            isMuted = false;
        } else if (msg == "activerSon") {
            startAudio();
        } else if (msg == "desactiverSon") {
            stopAudio();
        } else if (msg.startsWith("portGroup,")) {
            bool ok = false;
            int newPort = msg.section(',', 1).toInt(&ok);
            if (ok) {
                setGroupPort(newPort);
            }
        }
    }
}

void Student::initializeAudioCommunication() {
    if (portGroupAudio == -1 || profIP.isEmpty()) {
        qWarning() << "[Student] Port ou IP du prof non défini pour audio.";
        return;
    }

    try {
        if (pullSocket) {
            delete pullSocket;
            pullSocket = nullptr;
        }

        pullSocket = new zmq::socket_t(context, ZMQ_PULL);
        QString addr = "tcp://" + profIP + ":" + QString::number(portGroupAudio);
        pullSocket->connect(addr.toStdString());

        qDebug() << "[Student] Connecté au flux audio du groupe sur" << addr;
    } catch (const zmq::error_t& e) {
        qWarning() << "[Student] Erreur lors de la connexion audio au prof:" << e.what();
    }
}
