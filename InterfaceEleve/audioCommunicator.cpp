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


Student::Student(int port, QObject *parent)
    : QObject(parent), audioPort(port), isMuted(false)
{
    // 1. Définition du format audio (mono, 16kHz, 16-bit)
    QAudioFormat format;
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    // 2. Périphériques audio
    inputDeviceInfo = QMediaDevices::defaultAudioInput();
    outputDeviceInfo = QMediaDevices::defaultAudioOutput();

    if (!inputDeviceInfo.isNull()) {
        qDebug() << "🎤 Micro détecté:" << inputDeviceInfo.description();
        audioSource = new QAudioSource(inputDeviceInfo, format);
        audioSourceDevice = audioSource->start();
    } else {
        QMessageBox::critical(nullptr, "Microphone non détecté",
                              "❌ Aucun microphone détecté.\nConnectez un micro et redémarrez l'application.");
        return;
    }

    if (!outputDeviceInfo.isNull()) {
        qDebug() << "🔊 Haut-parleur détecté:" << outputDeviceInfo.description();
        audioSink = new QAudioSink(outputDeviceInfo, format);
        audioSinkDevice = audioSink->start();
    } else {
        QMessageBox::critical(nullptr, "Haut-parleur non détecté",
                              "❌ Aucun haut-parleur détecté.\nConnectez un haut-parleur et redémarrez l'application.");
        return;
    }

    // 3. Timers pour envoi et réception audio
    connect(&sendAudioTimer, &QTimer::timeout, this, &Student::sendAudioData);
    connect(&receiveAudioTimer, &QTimer::timeout, this, &Student::receiveAudioData);

    // 4. Configuration du socket UDP pour recevoir les commandes du professeur (mute, portGroup, etc.)
    connectToProfControlChannel();

    // 5. Timer pour écouter les commandes UDP
    connect(&commandPollingTimer, &QTimer::timeout, this, &Student::receiveCommandFromProf);
    commandPollingTimer.start(100); // écoute toutes les 100 ms
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
void Student::receiveAudioData() {
    zmq::message_t message;
    auto result = pullSocket.recv(message, zmq::recv_flags::dontwait);
    if (!result) return;

    QByteArray data(static_cast<char*>(message.data()), message.size());

    if (!data.isEmpty() && audioSinkDevice) {
        audioSinkDevice->write(data);
    }
}

void Student::connectToProfControlChannel()
{
    udpSocket.bind(audioPort, QUdpSocket::ShareAddress);  // écoute sur le port donné
    serverAddress = QHostAddress("192.168.64.1");         // IP du professeur
    serverPort = 5558;                                    // Port utilisé par le prof pour envoyer les commandes
}

void Student::setupAudioSockets(int port)
{
    try {
        // Ferme les anciens sockets si redéfini
        pushSocket.close();
        pullSocket.close();

        // Push = envoie aux autres
        pushSocket = zmq::socket_t(context, ZMQ_PUSH);
        pushSocket.connect("tcp://192.168.64.1:" + std::to_string(port));  // vers les autres élèves via prof (ou relais)

        // Pull = reçoit des autres
        pullSocket = zmq::socket_t(context, ZMQ_PULL);
        QString bindAddress = "tcp://*:" + QString::number(port + 1); // Ex: 5556/5557
        pullSocket.bind(bindAddress.toStdString());

        qDebug() << "✅ Sockets ZMQ configurés pour le groupe sur ports : " << port << "/" << port + 1;

        sendAudioTimer.start(100);
        receiveAudioTimer.start(100);

    } catch (const zmq::error_t &e) {
        qWarning() << "❌ Erreur lors de la configuration ZMQ :" << e.what();
    }
}


void Student::receiveCommandFromProf()
{
    while (udpSocket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QString response = QString::fromUtf8(datagram).trimmed();
        qDebug() << "🔔 Commande UDP reçue :" << response;

        if (response.startsWith("portGroup,")) {
            QStringList parts = response.split(",");
            if (parts.size() == 2) {
                int newPort = parts[1].toInt();
                qDebug() << "🔌 Port audio du groupe : " << newPort;
                setupAudioSockets(newPort);  // méthode qui configure ZMQ
            }
        } else if (response == "mute") {
            toggleMute(true);
        } else if (response == "unmute") {
            toggleMute(false);
        }
    }
}
