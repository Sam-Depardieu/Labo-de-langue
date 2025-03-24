#include "audioCommunicator.h"
#include "qdir.h"
#include <QIODevice>
#include <QDebug>
#include <QTimer>
#include <QMediaDevices>
#include <QAudioSource>
#include <QAudioSink>

Student::Student(QObject *parent) : QObject(parent) {
    QAudioFormat format;
    format.setSampleRate(16000);  // 44.1 kHz standard
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

    // Ici, vous pouvez ajouter le code pour traiter ou enregistrer les données audio si nécessaire
}

// Fonction pour recevoir l'audio
void Student::receiveAudioData() {
    qDebug() << "🔹 Début receiveAudioData()";

    if (!audioSinkDevice) {
        qDebug() << "⚠️ audioSinkDevice non initialisé";
        return;
    }

    // Ici, vous pouvez ajouter le code pour recevoir et jouer des données audio si nécessaire
    qDebug() << "🔹 Fin receiveAudioData()";
}

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
