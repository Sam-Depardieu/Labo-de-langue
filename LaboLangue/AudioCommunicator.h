#ifndef AUDIOCOMMUNICATOR_H
#define AUDIOCOMMUNICATOR_H



#include <QAudioSource>
#include <QIODevice>
#include <QAudioFormat>
#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QMap>
#include <QSet>

#include "iconEleveGroup.h"

class Professeur : public QObject
{
    Q_OBJECT

public:
    explicit Professeur(QObject* parent = nullptr);
    ~Professeur(); //Test
    void callStudent(const QHostAddress& address, quint16 port);    //Test
    void callGroup(const QHostAddress& groupAddress, quint16 groupPort);    //Test
    void stopAudio();   //Test
    void startAudioOutput(); //Test
    void onReadyReadFromStudent(); //Test
    void configureReceptionFromStudent(quint16 port); //Test


    //Gestion Audio
        // Ajoute un groupe avec son port UDP (unique par groupe)
        void addAudioGroup(const QString& groupName, quint16 portEnvoyeur, quint16 portReceveur);
        void appeler (quint16 portReceveur);
        void appelerTous();
        void configureAudioPorts(quint16 portEnvoyeur, quint16 portReceveur);

    // Vérifie si un groupe existe déjà
    bool audioGroupExists(const QString& groupName) const;

    // Envoie une commande (texte) à un étudiant par IP et port
    void sendCommandToStudent(const QString& studentIp, quint16 port, const QString& cmd);
    void muteStudent(const QString& studentIp);
    void unmuteStudent(const QString& studentIp);
    void activerSonStudent(const QString& studentIp);
    void desactiverSonStudent(const QString& studentIp);
    void stopAllAudioCommunication();


signals:
    void debugMessage(const QString& msg);

private slots:
    void onAudioDataCaptured();     // Test

    // Slot appelé quand un datagramme audio est reçu sur un socket groupe
    void onAudioDatagramReceived();

private:
    void startAudio();  //Test
    QAudioFormat getAudioFormat() const;    //Test

    QUdpSocket* udpSocketSend;  //Test
    QAudioSource* audioInput;   //Test
    QIODevice* audioInputDevice;    //Test

    QHostAddress destinationAddress;    //Test
    quint16 destinationPort;    //Test
    bool isGroupCall;   //Test
    QUdpSocket* udpSocketReceive; //Test
    QAudioSink* audioOutput; //Test
    QIODevice* audioOutputDevice; //Test
    quint16 portReceptionEleve; //Test



    quint16 portEnvoyeur = 9999;
    quint16 portReceveur = 9998;
    //Test QUdpSocket udpSocketReceive;
    //Test QUdpSocket udpSocketSend;

    struct GroupInfo {
        quint16 portEnvoyeur;      // Port d'écoute des paquets entrants (depuis les élèves)
        quint16 portReceveur;      // Port vers lequel rediriger les paquets audio
        QUdpSocket* socket;        // Socket lié au portEnvoyeur
        QSet<QString> members;     // IPs des élèves
        QSet<QString> mutedMembers;
        QSet<QString> sonDesactiveMembers;
    };

    MainWindow* mainWindow;
    QMap<QString, GroupInfo> groups;

    // Map d'IP vers groupe pour savoir à quel groupe appartient chaque étudiant
    QMap<QString, QString> studentToGroup;

    void processIncomingAudio(const QString& groupName, const QByteArray& datagram, const QHostAddress& sender);
};

#endif // AUDIOCOMMUNICATOR_H
