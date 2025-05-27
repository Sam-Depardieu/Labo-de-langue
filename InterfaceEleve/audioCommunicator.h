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
    void setServerAddress(const QHostAddress& address, quint16 port);

    void startAudio();
    void stopAudio();

signals:
    void audioDataReceived(const QByteArray& data);

private slots:
    void onReadyRead();
    void onAudioDataCaptured();

private:
    QUdpSocket* udpSocket;
    quint16 groupPort;

    QHostAddress serverAddress;
    quint16 serverPort;

    QAudioSource* audioInput;
    QAudioSink* audioOutput;

    QIODevice* audioInputDevice;
    QIODevice* audioOutputDevice;

    QAudioFormat getAudioFormat() const;
};

#endif // STUDENT_H
