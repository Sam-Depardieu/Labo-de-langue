#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include <QAudioSource>
#include <QAudioSink>
#include <QAudioDevice>
#include <QAudioFormat>
#include <QTimer>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(const QString &groupName, const QHostAddress &groupAddress, quint16 groupPort, QObject *parent = nullptr);
    ~Student();

    void setProfIp(const QString& ip);  // si besoin, sinon tu peux l'enlever
    void stopAudio();

signals:

public slots:
    void captureAndSendAudio();
    void receiveAudio();
    void changeAudioGroup(const QHostAddress& newAddress, quint16 newPort);
    void onAudioSourceStateChanged(QAudio::State newState);
    void initializeAudioCommunication();
    void connectToGroup(const QHostAddress& profAddress, quint16 profPort);

    void muteAudio();
    void unmuteAudio();

private:
    void connectToGroup();
    void connectToServer();  // si tu utilises encore cette méthode

    QString group;
    QHostAddress groupAddress;
    quint16 groupPort;

    QString serverIp;       // Si tu veux stocker l'IP du prof, ou sinon enlever
    QHostAddress serverAddress;  // Adresse du serveur / groupe multicast actuel
    quint16 serverPort;          // Port actuel utilisé

    QUdpSocket udpSocket;

    QAudioSource* audioInput = nullptr;
    QAudioSink* audioOutput = nullptr;

    QIODevice* inputDevice = nullptr;
    QIODevice* outputDevice = nullptr;

    QTimer sendTimer;
    bool isMuted = false;
};

#endif // STUDENT_H
