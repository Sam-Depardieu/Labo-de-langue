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
    void processCommands();
    void changeAudioGroup(const QHostAddress& newAddress, quint16 newPort);
    void onAudioSourceStateChanged(QAudio::State newState);
    void initializeAudioCommunication();

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
};

#endif // STUDENT_H
