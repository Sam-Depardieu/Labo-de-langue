#include "audioCommunicator.h"
#include "qdir.h"
#include <QIODevice>

#include <QDebug>
#include <QTimer>
#include <QMediaDevices>
#include <QAudioSource>
#include <QAudioSink>


Student::Student(QObject *parent) : QObject(parent) {

    udpSocket.bind(QHostAddress::Any,audioPort);
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


    connect(&udpSocket, &QUdpSocket::readyRead, this, &Student::receiveAudioData);
    // Connexion des timers aux slots
    connect(&sendAudioTimer, &QTimer::timeout, this, &Student::sendAudioData);
    //connect(&receiveAudioTimer, &QTimer::timeout, this, &Student::receiveAudioData);

    sendAudioTimer.start(100);  // Intervalle en millisecondes
    //receiveAudioTimer.start(100);

    connectToServer();
}

// Méthode pour envoyer les données audio
void Student::sendAudioData() {
    qDebug() << "?? Début sendAudioData()";

    // Démarrer la capture audio

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
    // Assurez-vous que la capture audio est prête avant de démarrer
    if(audioSource->state() == QAudio::IdleState) {
        qWarning() << "La source audio n'est pas prête.";
        audioSourceDevice = audioSource->start();
        QThread::msleep(200);

    }

    // Ici, vous pouvez ajouter le code pour traiter ou enregistrer les données audio si nécessaire
    //QThread::msleep(0);  // Attendre un peu pour que le buffer se remplisse



    qint16 availableBytes = audioSource->bytesAvailable();
    qDebug() << "Octets disponibles :" << availableBytes;
    if (1){//inputSource->state() == QAudio::ActiveState){
        if (availableBytes >0) {
            QByteArray data = audioSourceDevice->read(availableBytes); // Lire les données capturées

            if (!data.isEmpty()) {
                qDebug() << "Audio capturé, taille :" << data.size();
                udpSocket.writeDatagram(data, serverAddress, serverPort);
                qDebug() << "Audio envoyé, taille :" << data.size();
            } else {
                qDebug() << "data is empty !.";
            }
        } else {
            qDebug() << "Aucune donnée disponible dans le buffer audio.";
        }
    }
    else {
        qDebug() << "Aucune donnée capturée, état :" << audioSource->state();
    }
}

// Fonction pour recevoir l'audio
void Student::receiveAudioData() {
    qDebug() << "🔹 Début receiveAudioData()";

    while (udpSocket.hasPendingDatagrams()) {
        QByteArray data;
        data.resize(udpSocket.pendingDatagramSize());
        quint16 destinationPort = udpSocket.localPort();
        qDebug()<< "Port reception : "<< destinationPort;
        udpSocket.readDatagram(data.data(), data.size()); //&serverAddress, &serverPort
        qDebug() << "Paquet audio reçu, taille :" << data.size() << " octets";

        if (!data.isEmpty() && audioSink) {
            // Vérifier si le périphérique est prêt
            if (audioSink->state() == QAudio::SuspendedState) {
                qDebug() << "Reprise de la lecture audio.";
                audioSink->resume();
            } else if (audioSink->state() != QAudio::ActiveState) {
                qDebug() << "Le périphérique audio n'est pas actif, démarrage.";
                audioSinkDevice = audioSink->start();
            }

            // Écriture des données dans le flux audio
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
    while (udpSocket.hasPendingDatagrams()) {
        QByteArray data;
        data.resize(udpSocket.pendingDatagramSize());
        quint16 destinationPort = udpSocket.localPort();
        qDebug()<< "Port reception : "<< destinationPort;
        udpSocket.readDatagram(data.data(), data.size()); //&serverAddress, &serverPort
        qDebug() << "Paquet audio reçu, taille :" << data.size() << " octets";

        if (!data.isEmpty() && audioSink) {
            // Vérifier si le périphérique est prêt
            if (audioSink->state() == QAudio::SuspendedState) {
                qDebug() << "Reprise de la lecture audio.";
                audioSink->resume();
            } else if (audioSink->state() != QAudio::ActiveState) {
                qDebug() << "Le périphérique audio n'est pas actif, démarrage.";
                audioSinkDevice = audioSink->start();
            }

            // Écriture des données dans le flux audio
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

void Student::connectToServer() {
    // Envoie un message pour rejoindre le groupe
    QByteArray joinMessage = "JOIN " + group.toUtf8();
    udpSocket.writeDatagram(joinMessage, serverAddress, serverPort);
}
