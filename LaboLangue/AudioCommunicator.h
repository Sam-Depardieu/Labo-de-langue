#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <QObject>
#include <QUdpSocket>
#include <QMap>
#include <QSet>
#include <QHostAddress>
#include <QVector>

class Professeur : public QObject
{
    Q_OBJECT
public:
    explicit Professeur(QObject *parent = nullptr);

    // Ajouter un groupe avec un nom et un port
    void addAudioGroup(const QString& groupName, quint16 port);
    bool audioGroupExists(const QString& groupName) const{ return groups.contains(groupName); };
    void sendCommandToStudent(const QString& studentIp, int port, const QString& command);

    void muteStudent(const QString& studentIp) { sendCommandToStudent(studentIp, 5557, "mute"); }
    void unmuteStudent(const QString& studentIp) { sendCommandToStudent(studentIp, 5557, "unmute"); }
    void activerSonStudent(const QString& studentIp) { sendCommandToStudent(studentIp, 5557, "activerSon"); }
    void desactiverSonStudent(const QString& studentIp) { sendCommandToStudent(studentIp, 5557, "desactiverSon"); }

signals:
    void message(QString);

private slots:
    void processPendingDatagrams();

private:
    struct GroupInfo {
        QUdpSocket* socket = nullptr;
        QSet<QHostAddress> clients;  // Si besoin plus tard
    };

    QUdpSocket udpSocket;

    QMap<QString, GroupInfo> groups;  // groupName -> info
};

#endif // PROFESSOR_H
