#include "audioCommunicator.h"
#include <QDir>
#include <QIODevice>
#include <QDebug>
#include <QTimer>
#include <QMediaDevices>
#include <QAudioSource>
#include <QAudioSink>

Student::Student(QObject *parent) : QObject(parent) {
    // Initialisation du socket UDP pour recevoir les réponses
    udpSocket.bind(QHostAddress::Any, responsePort);
    connect(&udpSocket, &QUdpSocket::readyRead, this, &Student::receiveResponse);

    // Configuration d'un timer pour vérifier périodiquement les datagrammes
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Student::checkForDatagrams);
    timer->start(100); // Vérifie toutes les 100 ms

    qDebug() << "Port initialisé et en attente de messages sur le port" << responsePort;

    // Initialisation du socket UDP pour l'audio
    udpSocket.bind(QHostAddress::Any, audioPort);
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

    // Connexion des timers aux slots
    connect(&sendAudioTimer, &QTimer::timeout, this, &Student::sendAudioData);
    sendAudioTimer.start(3000);  // Intervalle en millisecondes

    connectToServer();
}

void Student::checkForDatagrams() {
    if (udpSocket.hasPendingDatagrams()) {
        receiveResponse();
    }
}

void Student::receiveResponse() {
    while (udpSocket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString response = QString::fromUtf8(datagram);
        qDebug() << "📢 Réponse reçue de" << sender.toString() << ":" << response;

        // Vérifiez si le message est "mute"
        if (response.trimmed() == "mute") {
            toggleMute(true);
        }
    }
}

void Student::toggleMute(bool mute) {
    static bool isMuted = false; // Garde l'état du mute

    if (mute && !isMuted) {
        qDebug() << "Coupure du son du micro.";

        if (audioSource) {
            audioSource->stop();  // Stopper l'enregistrement
        }
        isMuted = true;
    } else if (!mute && isMuted) {
        qDebug() << "Reprise du son du micro.";
        if (audioSource && inputDeviceInfo.isNull() == false) {
            QAudioFormat format;
            format.setSampleRate(44100);
            format.setChannelCount(1);
            format.setSampleFormat(QAudioFormat::Int16);
            audioSource->start();
        }
        isMuted = false;
    }
}


// Méthode pour envoyer les données audio
void Student::sendAudioData() {
    qDebug() << "?? Début sendAudioData()";

    if (audioSource->state() == QAudio::SuspendedState) {
        qDebug() << "Reprise de la lecture audio.";
        audioSource->resume();
        QThread::msleep(200);
    } else if (audioSource->state() != QAudio::ActiveState) {
        qDebug() << "Le périphérique audio n'est pas actif, démarrage.";
        audioSourceDevice = audioSource->start();
        QThread::msleep(200);
    }

    if (!audioSourceDevice) {
        qWarning() << "Impossible de démarrer l'enregistrement audio.";
        return;
    }

    if (audioSource->state() == QAudio::IdleState) {
        qWarning() << "La source audio n'est pas prête.";
        audioSourceDevice = audioSource->start();
        QThread::msleep(200);
    }

    qint16 availableBytes = audioSource->bytesAvailable();
    qDebug() << "Octets disponibles :" << availableBytes;
    if (availableBytes > 0) {
        QByteArray data = audioSourceDevice->read(availableBytes); // Lire les données capturées

        if (!data.isEmpty()) {
            udpSocket.writeDatagram(data, serverAddress, serverPort);
        } else {
            qDebug() << "data is empty !.";
        }
    } else {
        qDebug() << "Aucune donnée disponible dans le buffer audio.";
    }
}

// Fonction pour recevoir l'audio
void Student::receiveAudioData() {
    qDebug() << "🔹 Début receiveAudioData()";

    while (udpSocket.hasPendingDatagrams()) {
        QByteArray data;
        data.resize(udpSocket.pendingDatagramSize());
        quint16 destinationPort = udpSocket.localPort();
        qDebug() << "Port reception : " << destinationPort;
        udpSocket.readDatagram(data.data(), data.size());
        qDebug() << "Paquet audio reçu, taille :" << data.size() << " octets";

        if (!data.isEmpty() && audioSink) {
            if (audioSink->state() == QAudio::SuspendedState) {
                qDebug() << "Reprise de la lecture audio.";
                audioSink->resume();
            } else if (audioSink->state() != QAudio::ActiveState) {
                qDebug() << "Le périphérique audio n'est pas actif, démarrage.";
                audioSinkDevice = audioSink->start();
            }

            if (audioSinkDevice) {
                audioSinkDevice->write(data);
                qDebug() << "Lecture audio en cours...:" + QString::number(data.size());
            } else {
                qDebug() << "Erreur : Impossible d'écrire dans le périphérique audio.";
            }
        } else {
            qDebug() << "Aucune donnée reçue ou périphérique non initialisé.";
        }
    }

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

void Student::connectToServer() {
    // Envoie un message pour rejoindre le groupe
    QByteArray joinMessage = "JOIN " + group.toUtf8();
    udpSocket.writeDatagram(joinMessage, serverAddress, serverPort);
}
