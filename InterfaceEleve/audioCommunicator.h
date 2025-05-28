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
    explicit Student(QObject* parent = nullptr);
    ~Student();

    void handleCommand(const QString& cmd);

    void setGroupPort(quint16 port);
    void configureAudioPorts(quint16 portEnvoyeur, quint16 portReceveur);
    void setServerAddress(const QHostAddress& address, quint16 port);

    void startAudio();
    void stopAudio();

    void mute();
    void unmute();

signals:
    void audioDataReceived(const QByteArray& data);

private slots:
    void onReadyRead();
    void onAudioDataCaptured();

private:
    bool isMuted = false;

    QUdpSocket* udpSocketSend = nullptr;      // socket pour ENVOI audio
    QUdpSocket* udpSocketReceive = nullptr;   // socket pour RECEPTION audio

    quint16 portEnvoyeur = 0;
    quint16 portReceveur = 0;
    quint16 groupPort = 0;

    QHostAddress serverAddress;
    quint16 serverPort;

    QAudioSource* audioInput = nullptr;
    QAudioSink* audioOutput = nullptr;

    QIODevice* audioInputDevice = nullptr;
    QIODevice* audioOutputDevice = nullptr;

    QAudioFormat getAudioFormat() const;
};

#endif // STUDENT_H
