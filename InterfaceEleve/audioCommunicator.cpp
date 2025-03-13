#include "audioCommunicator.h"
#include <QIODevice>
#include <zmq.hpp>
#include <QDebug>

Student::Student()
    : pushSocket(nullptr), pullSocket(nullptr),
    audioSourceDevice(nullptr), audioSinkDevice(nullptr) {
    // Initialize or allocate resources here if needed
}

// Your existing methods
void Student::sendAudioData() {
    if (!audioSourceDevice) {
        qDebug() << "Error: audioSourceDevice is null.";
        return;
    }

    QByteArray audioData = audioSourceDevice->readAll();
    if (!audioData.isEmpty()) {
        zmq::message_t request(audioData.size());
        memcpy(request.data(), audioData.constData(), audioData.size());

        pushSocket->send(request, zmq::send_flags::none);
        qDebug() << "🎙 Audio envoyé, taille =" << audioData.size();
    }
}
void Student::receiveAudioData() {
    zmq::message_t reply;
    pullSocket->recv(reply);
    QByteArray audioData(static_cast<char*>(reply.data()), reply.size());
    if (!audioData.isEmpty()) {
        audioSinkDevice->write(audioData);  // Lecture de l'audio reçu
        qDebug() << "🔊 Audio reçu et joué, taille =" << audioData.size();
    }
}
