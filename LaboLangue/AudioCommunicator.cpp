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
        emit message(QString("Le groupe %1 existe déjà").arg(groupName));
        return;
    }

    QUdpSocket* socket = new QUdpSocket(this);
    bool bindResult = socket->bind(QHostAddress::AnyIPv4, port);
    if (!bindResult) {
        emit message(QString("Erreur bind port %1 pour groupe %2").arg(port).arg(groupName));
        delete socket;
        return;
    }

    GroupInfo info;
    info.socket = socket;

    groups[groupName] = info;

    connect(socket, &QUdpSocket::readyRead, this, &Professeur::processPendingDatagrams);

    emit message(QString("Groupe audio %1 créé sur le port %2").arg(groupName).arg(port));
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
        emit message("Socket inconnu pour processPendingDatagrams");
        return;
    }

    while (socket->hasPendingDatagrams()) {
        QHostAddress sender;
        quint16 senderPort;
        QByteArray buffer;
        buffer.resize(socket->pendingDatagramSize());

        socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

        // Pour l'instant on ne traite pas les JOIN, on se contente de rediffuser

        emit message(QString("Groupe %1: paquet reçu de %2, taille %3 bytes")
                         .arg(groupName)
                         .arg(sender.toString())
                         .arg(buffer.size()));

        // Rediffuser à tous les clients du groupe (on pourrait gérer clients plus tard)
        for (const QHostAddress& client : groups[groupName].clients) {
            if (client != sender) {
                socket->writeDatagram(buffer, client, senderPort);
            }
        }

        // Pour le moment, si on ne gère pas clients, on ne rediffuse pas
        // Tu peux ajouter la gestion clients plus tard
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


