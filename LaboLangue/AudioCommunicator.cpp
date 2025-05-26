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
    QUdpSocket* socket = qobject_cast<QUdpSocket*>(sender());
    if (!socket)
        return;

    // Trouver le groupe lié à ce socket
    QString groupName;
    for (auto it = groups.begin(); it != groups.end(); ++it) {
        if (it.value().socket == socket) {
            groupName = it.key();
            break;
        }
    }

    if (groupName.isEmpty()) {
        qDebug() << "[Professeur] Socket inconnu dans processPendingDatagrams";
        return;
    }

    while (socket->hasPendingDatagrams()) {
        QHostAddress sender;
        quint16 senderPort;
        QByteArray buffer;
        buffer.resize(socket->pendingDatagramSize());

        socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

        // Ajout du client s'il est nouveau dans ce groupe
        if (!groups[groupName].clients.contains(sender)) {
            groups[groupName].clients.insert(sender);
            qDebug() << "[Professeur] ➕ Nouveau client" << sender.toString()
                     << "dans le groupe" << groupName;
        }

        qDebug() << "[Professeur] 📥 Données reçues de" << sender.toString()
                 << "dans le groupe" << groupName << ", taille" << buffer.size();

        // Rediffusion
        if (broadcastEnabled) {
            // 🔊 Mode broadcast global activé
            for (auto it = groups.begin(); it != groups.end(); ++it) {
                QUdpSocket* targetSocket = it.value().socket;
                for (const QHostAddress& client : it.value().clients) {
                    if (client != sender) {
                        targetSocket->writeDatagram(buffer, client, senderPort);
                        qDebug() << "[Professeur] 📤 Broadcast vers" << client.toString()
                                 << "dans le groupe" << it.key();
                    }
                }
            }
        } else {
            // 🔁 Mode normal : renvoi uniquement dans le groupe d'origine
            for (const QHostAddress& client : groups[groupName].clients) {
                if (client != sender) {
                    socket->writeDatagram(buffer, client, senderPort);
                    qDebug() << "[Professeur] ↩️ Réponse vers" << client.toString()
                             << "dans le groupe" << groupName;
                }
            }
        }
    }
}


void Professeur::broadcast(const QByteArray& audioData, const QHostAddress& excludeAddress, quint16 excludePort)
{
    for (auto it = groups.begin(); it != groups.end(); ++it) {
        const QString& groupName = it.key();
        GroupInfo& groupInfo = it.value();
        QUdpSocket* socket = groupInfo.socket;

        for (const QHostAddress& client : groupInfo.clients) {
            if (client != excludeAddress) {
                bool success = socket->writeDatagram(audioData, client, excludePort);
                if (success) {
                    qDebug() << "[Broadcast] vers" << client.toString() << "depuis groupe" << groupName << "- taille:" << audioData.size();
                } else {
                    qWarning() << "[Broadcast] échec d'envoi vers" << client.toString() << "dans groupe" << groupName;
                }
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
