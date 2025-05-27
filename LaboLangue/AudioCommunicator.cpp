#include "AudioCommunicator.h"
#include <QDebug>

Professeur::Professeur(QObject* parent)
    : QObject(parent)
{
}

void Professeur::addAudioGroup(const QString& groupName, quint16 port)
{
    if (groups.contains(groupName)) {
        qDebug() << QString("Le groupe '%1' existe déjà").arg(groupName);
        return;
    }

    GroupInfo group;
    group.port = port;
    group.socket = new QUdpSocket(this);

    // Bind le socket au port attribué pour ce groupe (écoute UDP)
    if (!group.socket->bind(QHostAddress::AnyIPv4, port)) {
        qDebug() << QString("Impossible de binder le port %1 pour le groupe %2").arg(port).arg(groupName);
        group.socket->deleteLater();
        return;
    }

    connect(group.socket, &QUdpSocket::readyRead, this, &Professeur::onAudioDatagramReceived);

    groups[groupName] = group;

    qDebug() << QString("Groupe '%1' créé sur le port %2").arg(groupName).arg(port);
}

bool Professeur::audioGroupExists(const QString& groupName) const
{
    return groups.contains(groupName);
}

void Professeur::onAudioDatagramReceived()
{
    QUdpSocket* socket = qobject_cast<QUdpSocket*>(sender());
    if (!socket)
        return;

    QString groupName;
    for (auto it = groups.begin(); it != groups.end(); ++it) {
        if (it.value().socket == socket) {
            groupName = it.key();
            break;
        }
    }

    if (groupName.isEmpty()) {
        qDebug() << "Impossible d'identifier le groupe pour ce datagramme";
        return;
    }

    GroupInfo& group = groups[groupName];

    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(socket->pendingDatagramSize()));

        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString senderStr = sender.toString();  // Convertir en QString pour usage uniforme

        if (!group.members.contains(senderStr)) {
            group.members.insert(senderStr);
            studentToGroup[senderStr] = groupName;
            qDebug() << "Nouvel étudiant" << senderStr << "ajouté au groupe" << groupName;
        }

        // Si l'expéditeur est muté, ne pas redistribuer son audio
        if (group.mutedMembers.contains(senderStr)) {
            qDebug() << "Audio de" << senderStr << "ignoré (muted)";
            continue;
        }

        // Redistribuer à tous les membres sauf l'expéditeur
        for (const QString& memberStr : group.members) {
            if (memberStr != senderStr) {
                QHostAddress memberAddress(memberStr);
                socket->writeDatagram(datagram, memberAddress, group.port); // ✅ ici le bon port
            }
        }
    }
}


void Professeur::muteStudent(const QString& studentIp)
{

    if (!studentToGroup.contains(studentIp)) {
        qDebug() << "muteStudent: étudiant" << studentIp << "non trouvé";
        return;
    }

    QString groupName = studentToGroup.value(studentIp);
    GroupInfo& group = groups[groupName];

    if (!group.members.contains(studentIp)) {
        qDebug() << "muteStudent: étudiant" << studentIp << "n'est pas dans le groupe" << groupName;
        return;
    }

    if (!group.mutedMembers.contains(studentIp)) {
        group.mutedMembers.insert(studentIp);
        qDebug() << "Étudiant" << studentIp << "muté dans le groupe" << groupName;
    } else {
        qDebug() << "muteStudent: étudiant" << studentIp << "est déjà muté dans le groupe" << groupName;
    }
}

void Professeur::unmuteStudent(const QString& studentIp)
{

    if (!studentToGroup.contains(studentIp)) {
        qDebug() << "unmuteStudent: étudiant" << studentIp << "non trouvé";
        return;
    }

    QString groupName = studentToGroup.value(studentIp);
    GroupInfo& group = groups[groupName];

    if (!group.members.contains(studentIp)) {
        qDebug() << "unmuteStudent: étudiant" << studentIp << "n'est pas dans le groupe" << groupName;
        return;
    }

    if (group.mutedMembers.remove(studentIp) > 0) {
        qDebug() << "Étudiant" << studentIp << "unmuté dans le groupe" << groupName;
    } else {
        qDebug() << "unmuteStudent: étudiant" << studentIp << "n'était pas muté dans le groupe" << groupName;
    }
}

void Professeur::desactiverSonStudent(const QString& studentIp)
{

    if (!studentToGroup.contains(studentIp)) {
        qDebug() << "desactiverSonStudent: étudiant" << studentIp << "non trouvé";
        return;
    }

    QString groupName = studentToGroup.value(studentIp);
    GroupInfo& group = groups[groupName];

    if (!group.members.contains(studentIp)) {
        qDebug() << "desactiverSonStudent: étudiant" << studentIp << "n'est pas dans le groupe" << groupName;
        return;
    }

    if (!group.sonDesactiveMembers.contains(studentIp)) {
        group.sonDesactiveMembers.insert(studentIp);
        qDebug() << "Son désactivé pour étudiant" << studentIp << "dans le groupe" << groupName;
    } else {
        qDebug() << "desactiverSonStudent: son déjà désactivé pour étudiant" << studentIp << "dans le groupe" << groupName;
    }
}

void Professeur::activerSonStudent(const QString& studentIp)
{

    if (!studentToGroup.contains(studentIp)) {
        qDebug() << "activerSonStudent: étudiant" << studentIp << "non trouvé";
        return;
    }

    QString groupName = studentToGroup.value(studentIp);
    GroupInfo& group = groups[groupName];

    if (!group.members.contains(studentIp)) {
        qDebug() << "activerSonStudent: étudiant" << studentIp << "n'est pas dans le groupe" << groupName;
        return;
    }

    if (group.sonDesactiveMembers.remove(studentIp) > 0) {
        qDebug() << "Son activé pour étudiant" << studentIp << "dans le groupe" << groupName;
    } else {
        qDebug() << "activerSonStudent: son n'était pas désactivé pour étudiant" << studentIp << "dans le groupe" << groupName;
    }
}
