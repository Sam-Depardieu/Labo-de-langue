#include "AudioCommunicator.h"
#include <QDebug>

Professeur::Professeur(QObject *parent)
    : QObject(parent)
{
    // Le serveur ne bind plus un seul socket, mais en crée un par groupe
}

void Professeur::addAudioGroup(const QString& groupName, quint16 port)
{
    if (groups.contains(groupName)) {
        qDebug() << "Le groupe" << groupName << "existe déjà";
        return;
    }

    QUdpSocket* socket = new QUdpSocket(this);
    bool bindResult = socket->bind(QHostAddress::AnyIPv4, port);
    if (!bindResult) {
        qDebug() << "Erreur bind port" << port << "pour groupe" << groupName;
        delete socket;
        return;
    }

    GroupInfo info;
    info.socket = socket;

    groups[groupName] = info;

    connect(socket, &QUdpSocket::readyRead, this, &Professeur::processPendingDatagrams);

    qDebug() << "Groupe audio" << groupName << "créé sur le port" << port;
}

void Professeur::processPendingDatagrams()
{
    // On identifie quel socket a déclenché l'événement
    QUdpSocket* socket = qobject_cast<QUdpSocket*>(sender());
    if (!socket)
        return;

    // Trouver à quel groupe appartient ce socket
    QString groupName;
    for (auto it = groups.begin(); it != groups.end(); ++it) {
        if (it.value().socket == socket) {
            groupName = it.key();
            break;
        }
    }

    if (groupName.isEmpty()) {
        qDebug() << "Socket inconnu pour processPendingDatagrams";
        return;
    }

    while (socket->hasPendingDatagrams()) {
        QHostAddress sender;
        quint16 senderPort;
        QByteArray buffer;
        buffer.resize(socket->pendingDatagramSize());

        socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

        // Ajout du client s'il n'est pas déjà dans la liste (QSet donc insert)
        if (!groups[groupName].clients.contains(sender)) {
            groups[groupName].clients.insert(sender);
            qDebug() << "Ajout client" << sender.toString() << "au groupe" << groupName;
        }

        qDebug() << "Groupe" << groupName << ": paquet reçu de" << sender.toString()
                 << ", taille" << buffer.size() << "bytes";

        // Rediffuser à tous les clients du groupe sauf l'envoyeur
        for (const QHostAddress& client : groups[groupName].clients) {
            if (client != sender) {
                socket->writeDatagram(buffer, client, senderPort);
            }
        }
    }
}

void Professeur::sendCommandToStudent(const QString& studentIp, int port, const QString& command)
{
    if (command.isEmpty()) return;

    QByteArray datagram = command.toUtf8();
    QHostAddress addr(studentIp);
    udpSocket.writeDatagram(datagram, addr, port);
    qDebug() << "[Command] vers" << studentIp << ":" << command;
}
