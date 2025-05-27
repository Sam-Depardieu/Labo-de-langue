#ifndef AUDIOCOMMUNICATOR_H
#define AUDIOCOMMUNICATOR_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QMap>
#include <QSet>

class Professeur : public QObject
{
    Q_OBJECT
public:
    explicit Professeur(QObject* parent = nullptr);

    // Ajoute un groupe avec son port UDP (unique par groupe)
    void addAudioGroup(const QString& groupName, quint16 port);

    // Vérifie si un groupe existe déjà
    bool audioGroupExists(const QString& groupName) const;

    // Envoie une commande (texte) à un étudiant par IP et port
    void sendCommandToStudent(const QString& studentIp, quint16 port, const QString& cmd);

    void muteStudent(const QString& studentIp);
    void unmuteStudent(const QString& studentIp);
    void activerSonStudent(const QString& studentIp);
    void desactiverSonStudent(const QString& studentIp);

signals:
    void debugMessage(const QString& msg);

private slots:
    // Slot appelé quand un datagramme audio est reçu sur un socket groupe
    void onAudioDatagramReceived();

private:
    struct GroupInfo {
        quint16 port;
        QUdpSocket* socket = nullptr;
        QSet<QString> members;      // Étudiants du groupe
        QSet<QString> mutedMembers;
        QSet<QString> sonDesactiveMembers;
    };

    QMap<QString, GroupInfo> groups;

    // Map d'IP vers groupe pour savoir à quel groupe appartient chaque étudiant
    QMap<QString, QString> studentToGroup;

    void processIncomingAudio(const QString& groupName, const QByteArray& datagram, const QHostAddress& sender);
};

#endif // AUDIOCOMMUNICATOR_H
