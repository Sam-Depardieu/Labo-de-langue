#ifndef AUDIOPROFMULTI_H
#define AUDIOPROFMULTI_H

#include <QtNetwork>
#include <QtMultimedia>
#include <QObject>
#include <QMediaDevices>
#include <QAudioSource>
#include <QAudioSink>
#include <QAudioFormat>

class AudioProfMulti : public QObject
{
public:
    explicit AudioProfMulti(const QHostAddress &serverAddr, quint16 port, const QString &group, QObject *parent = nullptr);
    void setServeurParameters(QHostAddress serverAddress, quint16 serverPort);
    ~AudioProfMulti();
private slots:
    void captureAndSendAudio();
    void onAudioSourceStateChanged(QAudio::State);


private:
    void sendAudio();

    QUdpSocket udpSocket;
    QHostAddress serverAddress;
    quint16 serverPort;

    QAudioSource *audioInput;
    QAudioSink *audioOutput;

    QIODevice *inputDevice;
    QIODevice *outputDevice;

    //QByteArray audioBuffer;  // Stocker les données audio reçues
    QBuffer outputBuffer;    // Lire les données du buffer
    QAudioDevice outputAudioDevice;
    QAudioDevice inputAudioDevice;
    //QIODevice *audioDevice;

    QTimer sendTimer;
    QString group;  // Nom du groupe auquel le client appartient

};

#endif // AUDIOCLIENT_H
