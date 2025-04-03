#include "AudioCommunicator.h"

#include <QAudioSource>
#include <QAudioSink>
#include <QHostAddress>

Professor::Professor(QObject *parent) : QObject(parent), context(1) {
    QAudioFormat format;
    format.setSampleRate(16000);  // 44.1 kHz standard
    format.setChannelCount(1);  // Mono
    format.setSampleFormat(QAudioFormat::Int16);  // Format 16-bit

    inputDeviceInfo = QMediaDevices::defaultAudioInput();
    outputDeviceInfo = QMediaDevices::defaultAudioOutput();

    if (!inputDeviceInfo.isNull()) {
        qDebug() << "🎤 Micro détecté:" << inputDeviceInfo.description();
        audioSource = new QAudioSource(inputDeviceInfo, format);
        audioSourceDevice = audioSource->start();  // Démarre l’enregistrement
    } else {
        qDebug() << "❌ Aucun micro détecté!";
    }

    if (!outputDeviceInfo.isNull()) {
        qDebug() << "🔊 Haut-parleur détecté:" << outputDeviceInfo.description();
        audioSink = new QAudioSink(outputDeviceInfo, format);
        audioSinkDevice = audioSink->start();
    } else {
        qDebug() << "❌ Aucun haut-parleur détecté!";
    }

    pushSocket = new zmq::socket_t(context, ZMQ_PUSH);
    pushSocket->connect("tcp://localhost:5555");

    pullSocket = new zmq::socket_t(context, ZMQ_PULL);
    pullSocket->bind("tcp://*:5556");

    // Connexion des timers aux slots
    connect(&sendAudioTimer, &QTimer::timeout, this, &Professor::sendAudioData);
    connect(&receiveAudioTimer, &QTimer::timeout, this, &Professor::receiveAudioData);

    //sendAudioTimer.start(100);  // Intervalle en millisecondes
    //receiveAudioTimer.start(100);
}

void Professor::sendCommandToStudent(const QString& studentIp, const QString& command) {
    QString fullCommand = command + " " + "192.168.64.75";
    QByteArray datagram = fullCommand.toUtf8();

    QHostAddress studentAddress(studentIp);
    quint16 port = 5557; // Assurez-vous que le port est bien celui utilisé par les élèves

    udpSocket.writeDatagram(datagram, studentAddress, port);
    qDebug() << "📢 Commande envoyée :" << fullCommand;
}

void Professor::muteStudent(const QString& studentIp) {
    sendCommandToStudent(studentIp, "mute");
    qDebug() << "🔇 Élève" << studentIp << "muté!";
}

void Professor::unmuteStudent(const QString& studentIp) {
    sendCommandToStudent(studentIp, "unmute");
    qDebug() << "🎤 Élève" << studentIp << "démuté!";
}


void Professor::activerSonStudent(const QString& studentIp){
    sendCommandToStudent(studentIp, "activerSon");
    qDebug() << "🎤 Élève" << studentIp << "son activé !";
}

void Professor::desactiverSonStudent(const QString& studentIp){
    sendCommandToStudent(studentIp, "desactiverSon");
    qDebug() << "🎤 Élève" << studentIp << "son desactivé !";
}

QString Professor::getStudentStatus(const QString& studentIp) {
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.connect("tcp://" + serverIp.toStdString() + ":5556");

    std::string message = "status " + studentIp.toStdString();
    zmq::message_t request(message.size());
    memcpy(request.data(), message.c_str(), message.size());

    socket.send(request, zmq::send_flags::none);
    zmq::message_t reply;
    socket.recv(reply);

    return QString::fromStdString(std::string(static_cast<char*>(reply.data()), reply.size()));
}

// Méthode pour envoyer les données audio
void Professor::sendAudioData() {
    qDebug() << "?? Début sendAudioData()";

    if (!audioSourceDevice) {
        qDebug() << "❌ Erreur: audioSourceDevice est NULL!";
        return;
    }

    QByteArray data = audioSourceDevice->readAll();
    qDebug() << "🔹 Audio lu, taille :" << data.size();

    if (data.isEmpty()) {
        qDebug() << "⚠️ Aucune donnée audio à envoyer";
        return;
    }

    if (!pushSocket) {
        qDebug() << "❌ Erreur: pushSocket est NULL!";
        return;
    }

    try {
        zmq::message_t message(data.constData(), data.size());
        pushSocket->send(message, zmq::send_flags::none);
        qDebug() << "🗣️ Professeur parle, taille des données envoyées:" << data.size();
    } catch (const std::runtime_error &e) {
        qDebug() << "❌ Erreur lors de l'envoi des données audio:" << e.what();
    }
}

// Fonction pour recevoir l'audio des étudiants
void Professor::receiveAudioData() {
    qDebug() << "🔹 Début receiveAudioData()";

    if (!pullSocket) {
        qDebug() << "⚠️ pullSocket non initialisé";
        return;
    }

    if (!audioSinkDevice) {
        qDebug() << "⚠️ audioSinkDevice non initialisé";
        return;
    }

    zmq::message_t message;
    zmq::recv_result_t result = pullSocket->recv(message, zmq::recv_flags::dontwait); // Réception non bloquante

    if (!result) {
        if (zmq_errno() != EAGAIN) {  // Ignorer l'erreur si aucune donnée n'est dispo
            qDebug() << "❌ Erreur zmq_recv:"  ;// << zmq_strerror(zmq_errno());
        } else {
            qDebug() << "⚠️ Pas de données audio disponibles";
        }
        return;
    }

    QByteArray data(static_cast<char*>(message.data()), message.size());
    qDebug() << "✅ Audio reçu, taille :" << data.size();

    audioSinkDevice->write(data);
    qDebug() << "🔹 Fin receiveAudioData()";
}
