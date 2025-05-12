#ifndef AUDIOCOMMUNICATOR_H
#define AUDIOCOMMUNICATOR_H

#include "iconEleveGroup.h"

#include <QObject>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioSource>
#include <QAudioSink>
#include <QIODevice>
#include <QTimer>
#include <QUdpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QMediaDevices>

#include <zmq/zmq.hpp>

class MainWindow;

class Professor : public QObject {
    Q_OBJECT

public:
    explicit Professor(MainWindow* parentWindow);

    // Fonctions de contrôle audio
    void muteStudent(const QString& studentIp);
    void unmuteStudent(const QString& studentIp);
    void activerSonStudent(const QString& studentIp);
    void desactiverSonStudent(const QString& studentIp);
    void sendCommandToStudent(const QString& studentIp, int port, const QString& command);
    void fermerCommunications();

    QString getStudentStatus(const QString& studentIp);

public slots:
    void sendAudioData();      // Envoi périodique de l'audio (100 ms)
    void receiveAudioData();   // Réception audio des étudiants
    void processPendingDatagrams();

private:
    QString serverIp = "localhost";  // Adresse du serveur audio

    // ZeroMQ
    zmq::context_t context;
    zmq::socket_t* pushSocket = nullptr;
    zmq::socket_t* pullSocket = nullptr;

    // Qt Audio
    QAudioSource* audioSource = nullptr;
    QAudioSink* audioSink = nullptr;
    QIODevice* audioSourceDevice = nullptr;
    QIODevice* audioSinkDevice = nullptr;
    QAudioDevice inputDeviceInfo;
    QAudioDevice outputDeviceInfo;

    // Qt
    QTimer sendAudioTimer;
    QTimer receiveAudioTimer;
    QUdpSocket udpSocket;

    // Messages d'erreur
    bool microError = false;
    bool audioError = false;

    MainWindow* mainWindow = nullptr;
};

#endif // AUDIOCOMMUNICATOR_H
