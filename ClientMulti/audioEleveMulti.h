#ifndef AUDIOELEVEMULTI_H
#define AUDIOELEVEMULTI_H

#include <QtNetwork>
#include <QtMultimedia>
#include <QObject>
#include <QMediaDevices>
#include <QAudioSource>
#include <QAudioSink>
#include <QAudioFormat>

class AudioEleveMulti : public QObject
{
public:
    explicit AudioEleveMulti(const QHostAddress &serverAddr, quint16 port, const QString &group, QObject *parent = nullptr);
    void setServeurParameters(QHostAddress serverAddress, quint16 serverPort);
    ~AudioEleveMulti();
private slots:
    void receiveAudio();
    void onAudioSourceStateChanged(QAudio::State);


private:

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
