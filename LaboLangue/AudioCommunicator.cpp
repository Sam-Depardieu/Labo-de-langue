#include "AudioCommunicator.h"
#include "mainwindow.h" // Si nécessaire

#include <QAudioFormat>
#include <QMessageBox>
#include <QDebug>
#include <QHostAddress>
#include <QTimer>
#include <QMediaDevices>

#include <zmq/zmq.hpp>

// Constructeur
Professor::Professor(MainWindow *parentWindow)
    : context(1), mainWindow(parentWindow)
{
    QAudioFormat format;
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    inputDeviceInfo = QMediaDevices::defaultAudioInput();
    outputDeviceInfo = QMediaDevices::defaultAudioOutput();

    // Micro
    if (!inputDeviceInfo.isNull()) {
        try {
            audioSource = new QAudioSource(inputDeviceInfo, format);
            audioSourceDevice = audioSource->start();
        } catch (const std::exception &e) {
            QMessageBox::critical(nullptr, "Erreur", "Erreur micro : " + QString::fromStdString(e.what()));
            return;
        }
    } else {
        QMessageBox::critical(nullptr, "Erreur", "Aucun microphone détecté.");
        return;
    }

    // Haut-parleur
    if (!outputDeviceInfo.isNull()) {
        try {
            audioSink = new QAudioSink(outputDeviceInfo, format);
            audioSinkDevice = audioSink->start();
        } catch (const std::exception &e) {
            QMessageBox::critical(nullptr, "Erreur", "Erreur audio : " + QString::fromStdString(e.what()));
            return;
        }
    } else {
        QMessageBox::critical(nullptr, "Erreur", "Aucun haut-parleur détecté.");
        return;
    }

    // UDP pour les commandes
    udpSocket.bind(QHostAddress::Any, 5557);
    connect(&udpSocket, &QUdpSocket::readyRead, this, &Professor::processPendingDatagrams);
}

// Ajout dynamique d’un groupe audio avec port dédié
void Professor::addAudioGroup(const QString& groupName, int portAudio)
{
    if (audioGroupMap.contains(groupName)) return;

    QString pushAddress = "tcp://*:" + QString::number(portAudio);
    QString pullAddress = "tcp://*:" + QString::number(portAudio + 1);

    auto pushSocket = new zmq::socket_t(context, ZMQ_PUSH);
    auto pullSocket = new zmq::socket_t(context, ZMQ_PULL);

    try {
        pushSocket->bind(pushAddress.toStdString());
        pullSocket->bind(pullAddress.toStdString());
    } catch (const zmq::error_t& e) {
        QMessageBox::critical(nullptr, "ZMQ Error", "Échec bind ZMQ : " + QString::fromStdString(e.what()));
        return;
    }

    auto sendTimer = new QTimer(this);
    auto receiveTimer = new QTimer(this);

    connect(sendTimer, &QTimer::timeout, this, [this, groupName]() {
        if (audioGroupMap.contains(groupName)) {
            sendAudioDataToGroup(groupName);
        }
    });

    connect(receiveTimer, &QTimer::timeout, this, [=]() { receiveAudioDataFromGroup(groupName); });

    sendTimer->start(100);
    receiveTimer->start(100);

    AudioGroupSockets groupSockets { pushSocket, pullSocket, sendTimer, receiveTimer };
    audioGroupMap[groupName] = groupSockets;

    qDebug() << "[Professor] Groupe" << groupName << "initialisé sur ports" << portAudio << "/" << portAudio + 1;
}

// Envoi audio à un groupe
void Professor::sendAudioDataToGroup(const QString& groupName)
{
    if (!audioGroupMap.contains(groupName)) {
        qWarning() << "[sendAudioDataToGroup] Groupe inconnu:" << groupName;
        return;
    }

    if (!audioSourceDevice) {
        qWarning() << "[sendAudioDataToGroup] audioSourceDevice est null !";
        return;
    }

    if (audioSourceDevice->bytesAvailable() <= 0) {
        qDebug() << "[sendAudioDataToGroup] Rien à lire";
        return;
    }

    QByteArray data = audioSourceDevice->readAll();

    if (data.isEmpty()) {
        qWarning() << "[sendAudioDataToGroup] Data vide";
        return;
    }

    auto& push = audioGroupMap[groupName].pushSocket;

    try {
        zmq::message_t msg(data.constData(), data.size());
        push->send(msg, zmq::send_flags::none);
        qDebug() << "[Professor]" << groupName << " - audio envoyé, taille:" << data.size();
    } catch (const std::exception& e) {
        qWarning() << "[Professor] Erreur d'envoi ZMQ:" << e.what();
    }
}


// Réception audio d’un groupe
void Professor::receiveAudioDataFromGroup(const QString& groupName)
{
    if (!audioGroupMap.contains(groupName)) {
        qWarning() << "[receiveAudioDataFromGroup] Groupe inconnu:" << groupName;
        return;
    }

    auto& group = audioGroupMap[groupName];
    auto& pull = group.pullSocket;

    zmq::message_t msg;
    auto result = pull->recv(msg, zmq::recv_flags::dontwait);
    if (!result) {
        qDebug() << "[receiveAudioDataFromGroup] Rien reçu pour" << groupName;
        return;
    }

    QByteArray rawData(static_cast<char*>(msg.data()), msg.size());
    qDebug() << "[receiveAudioDataFromGroup] Message brut reçu, taille:" << rawData.size();

    int sepIndex = rawData.indexOf('|');
    if (sepIndex == -1) {
        qWarning() << "[receiveAudioDataFromGroup] Format invalide (pas de '|') reçu !";
        return;
    }

    QByteArray senderIp = rawData.left(sepIndex);
    QByteArray audioData = rawData.mid(sepIndex + 1);

    QString senderIpStr = QString::fromUtf8(senderIp);
    QString localIp = getLocalIp();
    qDebug() << "[receiveAudioDataFromGroup] senderIp =" << senderIpStr << ", localIp =" << localIp;

    if (!audioSinkDevice) {
        qWarning() << "[receiveAudioDataFromGroup] audioSinkDevice est null !";
        return;
    }

    if (senderIpStr != localIp) {
        audioSinkDevice->write(audioData);
        qDebug() << "[receiveAudioDataFromGroup] Son joué";
    } else {
        qDebug() << "[receiveAudioDataFromGroup] Ignoré (émis localement)";
    }

    for (iconEleveGroup* membre : mainWindow->listeGroup[groupName]) {
        if (membre->getIP().toUtf8() == senderIp) continue;

        try {
            QByteArray message = membre->getIP().toUtf8() + "|" + audioData;
            zmq::message_t forwardMsg(message.constData(), message.size());
            group.pushSocket->send(forwardMsg, zmq::send_flags::none);
            qDebug() << "[Professor] Relai ZMQ vers" << membre->getIP();
        } catch (const std::exception& e) {
            qWarning() << "[Professor] Erreur relai ZMQ:" << e.what();
        }
    }
}



// Commandes UDP
void Professor::sendCommandToStudent(const QString& studentIp, int port, const QString& command)
{
    if (command.isEmpty()) return;

    QByteArray datagram = command.toUtf8();
    QHostAddress addr(studentIp);
    udpSocket.writeDatagram(datagram, addr, port);
    qDebug() << "[Command] vers" << studentIp << ":" << command;
}

// Commandes audio individuelles
void Professor::muteStudent(const QString& studentIp) { sendCommandToStudent(studentIp, 5557, "mute"); }
void Professor::unmuteStudent(const QString& studentIp) { sendCommandToStudent(studentIp, 5557, "unmute"); }
void Professor::activerSonStudent(const QString& studentIp) { sendCommandToStudent(studentIp, 5557, "activerSon"); }
void Professor::desactiverSonStudent(const QString& studentIp) { sendCommandToStudent(studentIp, 5557, "desactiverSon"); }

// Vérifie le statut d’un étudiant
QString Professor::getStudentStatus(const QString& studentIp)
{
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.connect("tcp://" + serverIp.toStdString() + ":5556");

    std::string msg = "status " + studentIp.toStdString();
    zmq::message_t request(msg.size());
    memcpy(request.data(), msg.c_str(), msg.size());

    socket.send(request, zmq::send_flags::none);
    zmq::message_t reply;
    socket.recv(reply);

    return QString::fromStdString(std::string(static_cast<char*>(reply.data()), reply.size()));
}

// Réception UDP (debug)
void Professor::processPendingDatagrams()
{
    while (udpSocket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        qDebug() << "[UDP] Reçu de" << sender.toString() << ":" << datagram;
    }
}

// Nettoyage
void Professor::fermerCommunications()
{
    for (auto& group : audioGroupMap) {
        group.sendTimer->stop();
        group.receiveTimer->stop();
        delete group.pushSocket;
        delete group.pullSocket;
        delete group.sendTimer;
        delete group.receiveTimer;
    }
    audioGroupMap.clear();
    qDebug() << "[Professor] Tous les groupes audio fermés.";
}
