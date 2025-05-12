#include "AudioCommunicator.h"
#include <QAudioSource>
#include <QAudioSink>
#include <QHostAddress>
#include <QThread>
#include <QMessageBox>
#include <zmq/zmq.hpp>

Professor::Professor(MainWindow *parentWindow) : context(1), mainWindow(parentWindow) {
    QAudioFormat format;
    format.setSampleRate(16000);  // 16 kHz pour une qualité audio acceptable
    format.setChannelCount(1);    // Mono
    format.setSampleFormat(QAudioFormat::Int16);  // 16 bits par échantillon

    inputDeviceInfo = QMediaDevices::defaultAudioInput();
    outputDeviceInfo = QMediaDevices::defaultAudioOutput();

    // Initialisation du micro
    if (!inputDeviceInfo.isNull()) {
        try {
            audioSource = new QAudioSource(inputDeviceInfo, format);
            audioSourceDevice = audioSource->start();  // Démarre l'enregistrement
        } catch (const std::exception &e) {
            QMessageBox::critical(nullptr, "Erreur", "Erreur lors de l'enregistrement du micro : " + QString::fromStdString(e.what()));
            return;
        }
    } else {
        QMessageBox::critical(nullptr, "Microphone non détecté", "Aucun microphone n'a été détecté. La communication audio est impossible.");
        return;
    }

    // Initialisation des haut-parleurs
    if (!outputDeviceInfo.isNull()) {
        try {
            audioSink = new QAudioSink(outputDeviceInfo, format);
            audioSinkDevice = audioSink->start();  // Démarre la sortie audio
        } catch (const std::exception &e) {
            QMessageBox::critical(nullptr, "Erreur", "Erreur lors de la sortie audio : " + QString::fromStdString(e.what()));
            return;
        }
    } else {
        QMessageBox::critical(nullptr, "Haut-parleur non détecté", "Aucun haut-parleur n'a été détecté. La communication audio est impossible.");
        return;
    }

    // Initialisation des sockets ZeroMQ pour l'envoi et la réception d'audio
    try {
        pushSocket = new zmq::socket_t(context, ZMQ_PUSH);
        pushSocket->connect("tcp://localhost:5555");

        pullSocket = new zmq::socket_t(context, ZMQ_PULL);
        pullSocket->bind("tcp://*:5556");
    } catch (const zmq::error_t &e) {
        QMessageBox::critical(nullptr, "Erreur ZeroMQ", "Erreur lors de la création des sockets : " + QString::fromStdString(e.what()));
        return;
    }

    // Configuration des timers pour l'envoi et la réception des données audio
    connect(&sendAudioTimer, &QTimer::timeout, this, &Professor::sendAudioData);
    connect(&receiveAudioTimer, &QTimer::timeout, this, &Professor::receiveAudioData);

    sendAudioTimer.start(100);  // Envoi toutes les 100 ms
    receiveAudioTimer.start(100);  // Réception toutes les 100 ms
}

void Professor::sendCommandToStudent(const QString& studentIp, int port, const QString& command) {
    if (command.isEmpty()) return;

    QByteArray datagram = command.toUtf8();
    QHostAddress studentAddress(studentIp);
    udpSocket.writeDatagram(datagram, studentAddress, port);
    qDebug() << "Commande envoyée : " << command;
}

void Professor::muteStudent(const QString& studentIp) {
    sendCommandToStudent(studentIp, 5557, "mute");
}

void Professor::unmuteStudent(const QString& studentIp) {
    sendCommandToStudent(studentIp, 5557, "unmute");
}

void Professor::activerSonStudent(const QString& studentIp) {
    sendCommandToStudent(studentIp, 5557, "activerSon");
}

void Professor::desactiverSonStudent(const QString& studentIp) {
    sendCommandToStudent(studentIp, 5557, "desactiverSon");
}

QString Professor::getStudentStatus(const QString& studentIp) {
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.connect("tcp://" + serverIp.toStdString() + ":5556");

    std::string message = "status " + studentIp.toStdString();
    zmq::message_t request(message.size());
    memcpy(request.data(), message.c_str(), message.size());

    socket.send(request, zmq::send_flags::none);
    zmq::message_t reply;
    socket.recv(reply);

    return QString::fromStdString(std::string(static_cast<char*>(reply.data()), reply.size()));
}

// Envoi des données audio capturées
void Professor::sendAudioData() {
    QByteArray data = audioSourceDevice->readAll();

    if (data.isEmpty()) return;  // Si aucune donnée audio, on ne fait rien

    try {
        zmq::message_t message(data.constData(), data.size());
        pushSocket->send(message, zmq::send_flags::none);
    } catch (const std::runtime_error &e) {
        // Erreur lors de l'envoi des données
    }
}

// Réception des données audio des étudiants
void Professor::receiveAudioData() {
    zmq::message_t message;
    zmq::recv_result_t result = pullSocket->recv(message, zmq::recv_flags::dontwait);  // Réception non bloquante

    if (!result) return;

    QByteArray data(static_cast<char*>(message.data()), message.size());
    audioSinkDevice->write(data);  // Lecture des données audio reçues
}

void Professor::processPendingDatagrams() {
    while (udpSocket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        qDebug() << "📩 Commande reçue de" << sender.toString() << ":" << QString::fromUtf8(datagram);
    }
}
