#ifndef AUDIOCOMMUNICATOR_H
#define AUDIOCOMMUNICATOR_H

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
#include <zmq/zmq.hpp>

class Professor: public QObject {
    Q_OBJECT
public:
    Professor();
    void muteStudent(const QString& studentIp);
    void unmuteStudent(const QString& studentIp);
    void sendCommandToStudent(const QString& studentIp, const QString& command);
    QString getStudentStatus(const QString& studentIp);

public slots:  // Déclaration des slots ici
    void sendAudioData();  // Méthode qui sera appelée toutes les 100 ms
    void receiveAudioData();  // Méthode pour recevoir l'audio des étudiants

private:
    QString serverIp = "localhost"; // L'adresse IP du serveur
    zmq::context_t context;  // Contexte ZeroMQ
    zmq::socket_t *pushSocket;  // Socket pour envoyer l'audio
    zmq::socket_t *pullSocket;  // Socket pour recevoir l'audio

    QAudioSource *audioSource;  // Source audio pour capter l'audio du professeur
    QAudioSink *audioSink;  // Sortie audio pour jouer l'audio des étudiants
    QIODevice *audioSourceDevice;  // Dispositif pour lire les données audio du professeur
    QIODevice *audioSinkDevice;  // Dispositif pour écrire les données audio dans les haut-parleurs
    QAudioDevice inputDeviceInfo;
    QAudioDevice outputDeviceInfo;
    QTimer sendAudioTimer;
    QTimer receiveAudioTimer;

};

#endif // AUDIOCOMMUNICATOR_H
