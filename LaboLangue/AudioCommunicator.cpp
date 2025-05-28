#include "AudioCommunicator.h"
#include <QMediaDevices>
#include <QDebug>

Professeur::Professeur(QObject* parent)
    : QObject(parent),
    //Test udpSocketReceive(new QUdpSocket(this)),
    udpSocketSend(new QUdpSocket(this)),
    audioInput(nullptr),    //Test
    audioInputDevice(nullptr),     //Test
    destinationPort(0),    //Test
    isGroupCall(false)     //Test
{
}

Professeur::~Professeur() //Test
{
    stopAudio();
    if (udpSocketSend->isOpen()) {
        udpSocketSend->close();
    }
}

QAudioFormat Professeur::getAudioFormat() const //Test
{
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);
    return format;
}

void Professeur::startAudio() //Test
{
    QAudioFormat format = getAudioFormat();
    QAudioDevice inputDevice = QMediaDevices::defaultAudioInput();

    if (!inputDevice.isFormatSupported(format)) {
        qDebug() << "[Prof] Format audio non supporté";
        return;
    }

    audioInput = new QAudioSource(inputDevice, format, this);
    audioInputDevice = audioInput->start();

    if (!audioInputDevice) {
        qDebug() << "[Prof] Impossible de démarrer la capture audio";
        return;
    }

    connect(audioInputDevice, &QIODevice::readyRead, this, &Professeur::onAudioDataCaptured);
    qDebug() << "[Prof] Capture audio démarrée";
}

void Professeur::callStudent(const QHostAddress& address, quint16 port) //Test
{
    destinationAddress = address;
    destinationPort = port;
    isGroupCall = false;
    startAudio();
    qDebug() << "[Prof] Appel un élève à" << address.toString() << ":" << port;
}

/*
void Professeur::appeler (quint16 portReceveur){

}*/

void Professeur::callGroup(const QHostAddress& groupAddress, quint16 port) //Test
{
    destinationAddress = groupAddress;
    destinationPort = port;
    isGroupCall = true;

    udpSocketSend->setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
    startAudio();
    qDebug() << "[Prof] Appel groupe à" << groupAddress.toString() << ":" << port;
}

void Professeur::onAudioDataCaptured() //Test
{
    if (!audioInputDevice)
        return;

    QByteArray audioData = audioInputDevice->readAll();

    qint64 sent = udpSocketSend->writeDatagram(audioData, destinationAddress, destinationPort);
    if (sent == -1) {
        qDebug() << "[Prof] Erreur lors de l'envoi des données audio";
    }
}
void Professeur::stopAudio() //Test
{
    if (audioInput) {
        audioInput->stop();
        audioInput->deleteLater();
        audioInput = nullptr;
    }
    audioInputDevice = nullptr;
}


void Professeur::addAudioGroup(const QString& groupName, quint16 portEnvoyeur, quint16 portReceveur)
{
    if (groups.contains(groupName)) {
        qDebug() << QString("Le groupe '%1' existe déjà").arg(groupName);
        return;
    }

    GroupInfo group;
    group.portEnvoyeur = portEnvoyeur;
    group.portReceveur = portReceveur;
    group.socket = new QUdpSocket(this);

    if (!group.socket->bind(QHostAddress::AnyIPv4, portEnvoyeur)) {
        qDebug() << QString("Impossible de binder le port %1 pour le groupe %2").arg(portEnvoyeur).arg(groupName);
        group.socket->deleteLater();
        return;
    }

    connect(group.socket, &QUdpSocket::readyRead, this, &Professeur::onAudioDatagramReceived);
    groups[groupName] = group;

    qDebug() << QString("Groupe '%1' créé. Envoi sur %2, réception sur %3")
                    .arg(groupName).arg(portEnvoyeur).arg(portReceveur);
}



void Professeur::appelerTous(){
    //MULTICAST
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
        qDebug() << "[Professeur] Impossible d'identifier le groupe pour ce datagramme";
        return;
    }

    GroupInfo& group = groups[groupName];

    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(socket->pendingDatagramSize()));

        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString senderStr = sender.toString();

        qDebug() << QString("[Professeur][Groupe %1] Datagram reçu de %2:%3, taille %4 octets")
                        .arg(groupName).arg(senderStr).arg(senderPort).arg(datagram.size());

        if (!group.members.contains(senderStr)) {
            group.members.insert(senderStr);
            studentToGroup[senderStr] = groupName;
            qDebug() << QString("[Professeur][Groupe %1] Nouvel étudiant %2 ajouté au groupe")
                            .arg(groupName).arg(senderStr);
        }

        if (group.mutedMembers.contains(senderStr)) {
            qDebug() << QString("[Professeur][Groupe %1] Audio de %2 ignoré (muted)")
                            .arg(groupName).arg(senderStr);
            continue;
        }

        // Redistribution à tous les membres sauf l'expéditeur
        for (const QString& memberStr : group.members) {
            if (memberStr != senderStr) {
                QHostAddress memberAddress(memberStr);

                qint64 sent = socket->writeDatagram(datagram, memberAddress, group.portReceveur);
                if (sent == -1) {
                    qDebug() << QString("[Professeur][Groupe %1] Erreur en envoyant audio à %2:%3")
                                    .arg(groupName).arg(memberStr).arg(group.portReceveur);
                } else {
                    qDebug() << QString("[Professeur][Groupe %1] Datagram audio envoyé à %2:%3, taille %4 octets")
                                    .arg(groupName).arg(memberStr).arg(group.portReceveur).arg(datagram.size());
                }
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

void Professeur::sendCommandToStudent(const QString& studentIp, quint16 port, const QString& cmd)
{
    QUdpSocket socket;
    QByteArray data = cmd.toUtf8();
    QHostAddress address(studentIp);

    socket.writeDatagram(data, address, port);
    // Pas besoin de socket persistant ici, on crée juste pour envoyer
    qDebug() << "[Professeur] Commande envoyée à" << studentIp << ":" << cmd;
}
