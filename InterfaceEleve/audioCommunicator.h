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


class Student: public QObject {
    Q_OBJECT
public:
    Student(QObject *parent = nullptr);

    void toggleMute(bool mute);

    void sendCommandToStudent(const QString& studentIp, const QString& command); // Nouvelle méthode

public slots:  // Déclaration des slots ici
    void sendAudioData();  // Méthode qui sera appelée toutes les 100 ms
    void receiveAudioData();  // Méthode pour recevoir l'audio des étudiants
    void playFeedback();
    void receiveResponse(); // Nouveau slotvoid checkForDatagrams() {
    void checkForDatagrams();



private:
    //QString serverIp = "192.168.89.41"; // L'adresse IP du serveur
    void connectToServer();
    QUdpSocket udpSocket;
    quint16 audioPort = 12346;
    quint16 serverPort = 12345;
    QHostAddress serverAddress = QHostAddress("192.168.64.19"); // L'adresse IP du serveur
    QAudioSource *audioSource;  // Source audio pour capter l'audio du professeur
    QAudioSink *audioSink;  // Sortie audio pour jouer l'audio des étudiants
    QIODevice *audioSourceDevice;  // Dispositif pour lire les données audio du professeur
    QIODevice *audioSinkDevice;  // Dispositif pour écrire les données audio dans les haut-parleurs
    QAudioDevice inputDeviceInfo;
    QAudioDevice outputDeviceInfo;
    QTimer sendAudioTimer;
    QTimer receiveAudioTimer;
    QString group = "groupe1";
    quint16 responsePort = 5557; // Port pour recevoir les réponses


};

#endif // AUDIOCOMMUNICATOR_H
