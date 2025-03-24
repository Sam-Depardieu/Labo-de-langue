#ifndef AUDIOCOMMUNICATOR_H
#define AUDIOCOMMUNICATOR_H

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
<<<<<<< HEAD
=======
//#include <zmq.hpp>
>>>>>>> b58bf215bd779102c84a0b57b95660ad8196f32c

class Student: public QObject {
    Q_OBJECT
public:
    Student(QObject *parent = nullptr);

    void toggleMute(bool mute);

public slots:  // Déclaration des slots ici
    void sendAudioData();  // Méthode qui sera appelée toutes les 100 ms
    void receiveAudioData();  // Méthode pour recevoir l'audio des étudiants
    void playFeedback();


private:
<<<<<<< HEAD
    QString serverIp = "192.168.89.42"; // L'adresse IP du serveur
=======
    void connectToServer();
    QUdpSocket udpSocket;
    quint16 audioPort = 12346;
    quint16 serverPort = 12345;
    QHostAddress serverAddress = QHostAddress("127.0.0.1"); // L'adresse IP du serveur
>>>>>>> b58bf215bd779102c84a0b57b95660ad8196f32c

    QAudioSource *audioSource;  // Source audio pour capter l'audio du professeur
    QAudioSink *audioSink;  // Sortie audio pour jouer l'audio des étudiants
    QIODevice *audioSourceDevice;  // Dispositif pour lire les données audio du professeur
    QIODevice *audioSinkDevice;  // Dispositif pour écrire les données audio dans les haut-parleurs
    QAudioDevice inputDeviceInfo;
    QAudioDevice outputDeviceInfo;
    QTimer sendAudioTimer;
    QTimer receiveAudioTimer;
    QString group = "groupe1";
};

#endif // AUDIOCOMMUNICATOR_H
