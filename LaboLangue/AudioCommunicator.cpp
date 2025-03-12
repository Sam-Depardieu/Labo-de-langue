#include "AudioCommunicator.h"

#include <QAudioSource>
#include <QAudioSink>

Professor::Professor() {

    QAudioFormat format;
    format.setSampleRate(16000);               // Fréquence d'échantillonnage (16 kHz)
    format.setChannelCount(1);                 // Mono
    format.setSampleRate(16);                  // Taille de l'échantillon (16 bits)
    format.setSampleFormat(QAudioFormat::Int16);  // Type d'échantillon : entier signé

    QAudioDevice inputDeviceInfo(QMediaDevices::defaultAudioInput());
    QAudioDevice outputDeviceInfo(QMediaDevices::defaultAudioOutput());

    // Audio source pour capturer l'audio du professeur (microphone)
    audioSource = new QAudioSource(format, nullptr);
    audioSourceDevice = audioSource->start();

    // Audio sink pour jouer l'audio des étudiants (haut-parleurs)
    audioSink = new QAudioSink(format, nullptr);
    audioSinkDevice = audioSink->start();
}

void Professor::sendCommandToStudent(const QString& studentIp, const QString& command) {
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.connect("tcp://" + serverIp.toStdString() + ":5556");

    QString fullCommand = command + " " + studentIp;
    std::string message = fullCommand.toStdString();
    zmq::message_t request(message.size());
    memcpy(request.data(), message.c_str(), message.size());

    socket.send(request, zmq::send_flags::none);
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
// Envoi de l'audio capturé du professeur
void Professor::sendAudioData() {
    QByteArray audioData = audioSourceDevice->readAll();
    if (!audioData.isEmpty()) {
        zmq::message_t request(audioData.size());
        memcpy(request.data(), audioData.constData(), audioData.size());

        pushSocket->send(request, zmq::send_flags::none);
        qDebug() << "🎙 Audio envoyé, taille =" << audioData.size();
    }
}

// Fonction pour recevoir l'audio des étudiants (par exemple, d'un autre socket)
void Professor::receiveAudioData() {
    zmq::message_t reply;
    pullSocket->recv(reply);

    QByteArray audioData(static_cast<char*>(reply.data()), reply.size());
    if (!audioData.isEmpty()) {
        audioSinkDevice->write(audioData);  // Lecture de l'audio reçu
        qDebug() << "🔊 Audio reçu et joué, taille =" << audioData.size();
    }
}
