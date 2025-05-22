#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioSource>
#include <QAudioSink>
#include <QIODevice>
#include <QUdpSocket>
#include <QTimer>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QHostAddress>
#include <QString>
#include <QDebug>

#include <zmq/zmq.hpp>

class Student : public QObject {
    Q_OBJECT

public:
    explicit Student(QObject* parent = nullptr);

    void setIP(const QString& ip);
    void setProfIp(QString ip) {profIP = ip;}
    QString getIP() const;

    void setGroupPort(int port);  // Reçoit le port du groupe attribué
    void startAudio();
    void stopAudio();
    void setPortGroupAudio(int port) { portGroupAudio = port; }
    void initializeAudioCommunication();  // déclaration

public slots:
    void handleCommand();  // UDP : mute, unmute, etc.
    void sendAudioData();
    void receiveAudioData();

private:
    QString studentIp;
    QString profIP;
    int portGroupAudio = -1;

    // ZeroMQ
    zmq::context_t context;
    zmq::socket_t* pushSocket = nullptr;
    zmq::socket_t* pullSocket = nullptr;

    // Audio
    QAudioSource* audioSource = nullptr;
    QAudioSink* audioSink = nullptr;
    QIODevice* audioInput = nullptr;
    QIODevice* audioOutput = nullptr;
    QAudioDevice inputDevice;
    QAudioDevice outputDevice;

    // Réseaux
    QUdpSocket udpSocket;

    // Timers
    QTimer sendTimer;
    QTimer receiveTimer;

    // État
    bool isMuted = false;

    void setupZMQ();
    void closeZMQ();
};

#endif // STUDENT_H
