#include "audioCommunicator.h"
#include <QIODevice>
#include <zmq.hpp>
#include <QDebug>
#include <QTimer>
#include <QMediaDevices>
#include <QAudioSource>
#include <QAudioSink>

Student::Student(QObject *parent) : QObject(parent), context(1) {
    QAudioFormat format;
    format.setSampleRate(44100);  // 44.1 kHz standard
    format.setChannelCount(1);  // Mono
    format.setSampleFormat(QAudioFormat::Int16);  // Format 16-bit

    inputDeviceInfo = QMediaDevices::defaultAudioInput();
    outputDeviceInfo = QMediaDevices::defaultAudioOutput();

    if (!inputDeviceInfo.isNull()) {
        qDebug() << "🎤 Micro détecté:" << inputDeviceInfo.description();
        audioSource = new QAudioSource(inputDeviceInfo, format);
        audioSourceDevice = audioSource->start();  // Démarre l’enregistrement
    } else {
        qDebug() << "❌ Aucun micro détecté!";
    }

    if (!outputDeviceInfo.isNull()) {
        qDebug() << "🔊 Haut-parleur détecté:" << outputDeviceInfo.description();
        audioSink = new QAudioSink(outputDeviceInfo, format);
        audioSinkDevice = audioSink->start();
    } else {
        qDebug() << "❌ Aucun haut-parleur détecté!";
    }

    pushSocket = new zmq::socket_t(context, ZMQ_PUSH);
    pushSocket->connect("tcp://localhost:5555");

    pullSocket = new zmq::socket_t(context, ZMQ_PULL);
    pullSocket->bind("tcp://*:5556");

    // Connexion des timers aux slots
    connect(&sendAudioTimer, &QTimer::timeout, this, &Student::sendAudioData);
    connect(&receiveAudioTimer, &QTimer::timeout, this, &Student::receiveAudioData);

    sendAudioTimer.start(100);  // Intervalle en millisecondes
    receiveAudioTimer.start(100);
}

// Méthode pour envoyer les données audio
void Student::sendAudioData() {
    qDebug() << "?? Début sendAudioData()";

    if (!audioSourceDevice) {
        qDebug() << "❌ Erreur: audioSourceDevice est NULL!";
        return;
    }

    QByteArray data = audioSourceDevice->readAll();
    qDebug() << "🔹 Audio lu, taille :" << data.size();

    if (data.isEmpty()) {
        qDebug() << "⚠️ Aucune donnée audio à envoyer";
        return;
    }

    if (!pushSocket) {
        qDebug() << "❌ Erreur: pushSocket est NULL!";
        return;
    }

    try {
        zmq::message_t message(data.constData(), data.size());
        pushSocket->send(message, zmq::send_flags::none);
    } catch (const std::runtime_error &e) {
        qDebug() << "❌ Erreur lors de l'envoi des données audio:" << e.what();
    }
}

// Fonction pour recevoir l'audio des étudiants
void Student::receiveAudioData() {
    qDebug() << "🔹 Début receiveAudioData()";

    if (!pullSocket) {
        qDebug() << "⚠️ pullSocket non initialisé";
        return;
    }

    if (!audioSinkDevice) {
        qDebug() << "⚠️ audioSinkDevice non initialisé";
        return;
    }

    zmq::message_t message;
    zmq::recv_result_t result = pullSocket->recv(message, zmq::recv_flags::dontwait); // Réception non bloquante

    if (!result) {
        if (zmq_errno() != EAGAIN) {  // Ignorer l'erreur si aucune donnée n'est dispo
            qDebug() << "❌ Erreur zmq_recv:" << zmq_strerror(zmq_errno());
        } else {
            qDebug() << "⚠️ Pas de données audio disponibles";
        }
        return;
    }

    QByteArray data(static_cast<char*>(message.data()), message.size());
    qDebug() << "✅ Audio reçu, taille :" << data.size();

    audioSinkDevice->write(data);
    qDebug() << "🔹 Fin receiveAudioData()";
}
