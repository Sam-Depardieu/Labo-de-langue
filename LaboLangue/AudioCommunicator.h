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
#include <QMap>

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
    bool audioGroupExists(const QString& groupName) const {return audioGroupMap.contains(groupName);}

    // Ajoute un nouveau groupe audio
    void addAudioGroup(const QString& groupName, int portAudio);

public slots:
    void sendAudioDataToGroup(const QString& groupName);
    void receiveAudioDataFromGroup(const QString& groupName);
    void processPendingDatagrams();

private:
    QString serverIp = "localhost";  // Adresse du serveur audio

    zmq::context_t context;

    // Structure pour un groupe audio
    struct AudioGroupSockets {
        zmq::socket_t* pushSocket;
        zmq::socket_t* pullSocket;
        QTimer* sendTimer;
        QTimer* receiveTimer;
    };

    QMap<QString, AudioGroupSockets> audioGroupMap;

    // Qt Audio
    QAudioSource* audioSource = nullptr;
    QAudioSink* audioSink = nullptr;
    QIODevice* audioSourceDevice = nullptr;
    QIODevice* audioSinkDevice = nullptr;
    QAudioDevice inputDeviceInfo;
    QAudioDevice outputDeviceInfo;

    // Timers généraux (utiles si 1 seul groupe)
    QTimer sendAudioTimer;
    QTimer receiveAudioTimer;

    // Réseau
    QUdpSocket udpSocket;

    // Messages d'erreur
    bool microError = false;
    bool audioError = false;

    MainWindow* mainWindow = nullptr;

    QString getLocalIp()
    {
        return "192.168.64.1";
    }

};

#endif // AUDIOCOMMUNICATOR_H
