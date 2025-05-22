#ifndef AUDIOCOMMUNICATOR_H
#define AUDIOCOMMUNICATOR_H

#include "zmq/zmq.hpp"
#include <QtNetwork>
#include <QObject>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioSource>
#include <QAudioSink>
#include <QIODevice>
#include <QString>
#include <QDebug>
#include <QMediaDevices>
#include <QTimer>


class Student : public QObject {
    Q_OBJECT

public:
    Student(int port, QObject *parent = nullptr);
    void connectToServer();
    void playFeedback();

private slots:
    void sendAudioData();
    void receiveAudioData();
    void toggleMute(bool mute);
    void connectToProfControlChannel();
    void receiveCommandFromProf();
    void setupAudioSockets(int port);

private:
    QAudioSource *audioSource = nullptr;
    QIODevice *audioSourceDevice = nullptr;
    QAudioSink *audioSink = nullptr;
    QIODevice *audioSinkDevice = nullptr;

    QAudioDevice inputDeviceInfo;
    QAudioDevice outputDeviceInfo;

    bool isMuted = false;
    QTimer commandPollingTimer;

    QTimer sendAudioTimer;
    QTimer receiveAudioTimer;

    QUdpSocket udpSocket;
    int audioPort;
    quint16 responsePort = 5564;

    QHostAddress serverAddress = QHostAddress("192.168.64.1");
    quint16 serverPort = 5555;
    QString group = "default";

    zmq::context_t context;
    zmq::socket_t pushSocket;
    zmq::socket_t pullSocket;
};



#endif // AUDIOCOMMUNICATOR_H
