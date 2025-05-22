#include "audioCommunicator.h"
#include <QAudioFormat>
#include <QAudioSource>
#include <QAudioSink>
#include <QMediaDevices>
#include <QMessageBox>
#include <QTimer>
#include <QFile>
#include <QDebug>
#include <QThread>
#include <zmq/zmq.hpp>


Student::Student(int port, QObject *parent ) : QObject(parent), audioPort(port) {

    // Format audio compatible professeur
    QAudioFormat format;
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    inputDeviceInfo = QMediaDevices::defaultAudioInput();
    outputDeviceInfo = QMediaDevices::defaultAudioOutput();

    // Micro
    if (!inputDeviceInfo.isNull()) {
        qDebug() << "🎤 Micro détecté:" << inputDeviceInfo.description();
        audioSource = new QAudioSource(inputDeviceInfo, format);
        audioSourceDevice = audioSource->start();
    } else {
        QMessageBox::critical(nullptr, "Microphone non détecté",
                              "❌ Aucun microphone détecté.\nConnectez un micro et redémarrez l'application.");
        return;
    }

    // Haut-parleur
    if (!outputDeviceInfo.isNull()) {
        qDebug() << "🔊 Haut-parleur détecté:" << outputDeviceInfo.description();
        audioSink = new QAudioSink(outputDeviceInfo, format);
        audioSinkDevice = audioSink->start();
    } else {
        QMessageBox::critical(nullptr, "Haut-parleur non détecté",
                              "❌ Aucun haut-parleur détecté.\nConnectez un haut-parleur et redémarrez l'application.");
        return;
    }

    // Connexion ZeroMQ
    try {
        pushSocket.connect("tcp://localhost:5556");  // Vers professeur (pull)
        pullSocket.connect("tcp://localhost:5555");  // Depuis professeur (push)
    } catch (const zmq::error_t &e) {
        QMessageBox::critical(nullptr, "Erreur ZeroMQ",
                              "Erreur lors de la connexion ZeroMQ : " + QString::fromStdString(e.what()));
        return;
    }

    // Timers
    connect(&sendAudioTimer, &QTimer::timeout, this, &Student::sendAudioData);
    sendAudioTimer.start(100);  // Envoi toutes les 100 ms

    connect(&receiveAudioTimer, &QTimer::timeout, this, &Student::receiveAudioDataZMQ);
    receiveAudioTimer.start(100);  // Réception toutes les 100 ms

    connectToServer();
}

// Commandes UDP : mute, unmute
void Student::receiveResponse() {
    while (udpSocket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QString response = QString::fromUtf8(datagram);
        qDebug() << "📢 Commande reçue de" << sender.toString() << ":" << response;
        if (response.trimmed() == "mute") {
            toggleMute(true);
        } else if (response.trimmed() == "unmute") {
            toggleMute(false);
        }
    }
}

void Student::toggleMute(bool mute) {
    static bool isMuted = false;

    if (mute && !isMuted) {
        qDebug() << "🔇 Micro coupé.";
        if (audioSource) audioSource->stop();
        isMuted = true;
    } else if (!mute && isMuted) {
        qDebug() << "🔊 Micro réactivé.";
        if (audioSource && !inputDeviceInfo.isNull()) {
            QAudioFormat format;
            format.setSampleRate(16000);
            format.setChannelCount(1);
            format.setSampleFormat(QAudioFormat::Int16);
            audioSource->start();
        }
        isMuted = false;
    }
}

// Envoi audio via ZeroMQ
void Student::sendAudioData() {
    if (!audioSourceDevice) return;
    QByteArray data = audioSourceDevice->readAll();
    if (data.isEmpty()) return;

    try {
        zmq::message_t message(data.constData(), data.size());
        pushSocket.send(message, zmq::send_flags::dontwait);
    } catch (const zmq::error_t &e) {
        qWarning() << "❌ Erreur ZeroMQ (envoi audio) :" << e.what();
    }
}

// Réception audio via ZeroMQ
void Student::receiveAudioDataZMQ() {
    zmq::message_t message;
    auto result = pullSocket.recv(message, zmq::recv_flags::dontwait);
    if (!result) return;

    QByteArray data(static_cast<char*>(message.data()), message.size());

    if (!data.isEmpty() && audioSinkDevice) {
        audioSinkDevice->write(data);
    }
}

// Rejoint un groupe via UDP
void Student::connectToServer() {
    QByteArray joinMessage = "JOIN " + group.toUtf8();
    udpSocket.writeDatagram(joinMessage, serverAddress, serverPort);
}

// Pour lire un son local (non utilisé dans ZeroMQ)
void Student::playFeedback() {
    QAudioFormat format;
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    audioSink = new QAudioSink(format, this);
    QFile audioFile("feedback_teacher.wav");
    if (audioFile.open(QIODevice::ReadOnly)) {
        QIODevice *device = audioSink->start();
        device->write(audioFile.readAll());
    }
}
