#include "audioCommunicator.h"

// Envoi de l'audio capturé par l'élève
void Student::sendAudioData() {
    QByteArray audioData = audioSourceDevice->readAll();
    if (!audioData.isEmpty()) {
        zmq::message_t request(audioData.size());
        memcpy(request.data(), audioData.constData(), audioData.size());

        pushSocket->send(request, zmq::send_flags::none);
        qDebug() << "🎙 Audio envoyé, taille =" << audioData.size();
    }
}

// Fonction pour recevoir l'audio des autres étudiants
void Student::receiveAudioData() {
    zmq::message_t reply;
    pullSocket->recv(reply);

    QByteArray audioData(static_cast<char*>(reply.data()), reply.size());
    if (!audioData.isEmpty()) {
        audioSinkDevice->write(audioData);  // Lecture de l'audio reçu
        qDebug() << "🔊 Audio reçu et joué, taille =" << audioData.size();
    }
}
