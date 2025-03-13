#include "AudioCommunicator.h"

#include <QAudioSource>
#include <QAudioSink>

Professor::Professor() : context(1) {

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

    pushSocket = new zmq::socket_t(context, ZMQ_PUSH);
    pullSocket = new zmq::socket_t(context, ZMQ_PULL);

    // Connexion des timers aux slots
    connect(&sendAudioTimer, &QTimer::timeout, this, &Professor::sendAudioData);
    connect(&receiveAudioTimer, &QTimer::timeout, this, &Professor::receiveAudioData);

    sendAudioTimer.moveToThread(this->thread());
    receiveAudioTimer.moveToThread(this->thread());

    // Démarrer les timers
    sendAudioTimer.start(100);
    receiveAudioTimer.start(100);
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
    qDebug() << "🔹 Début sendAudioData()";

    if (!pushSocket) {
        qDebug() << "⚠️ pushSocket non initialisé";
        return;
    }

    if (!audioSourceDevice) {
        qDebug() << "⚠️ audioSourceDevice non initialisé";
        return;
    }

    QByteArray data = audioSourceDevice->read(4096); // Lit 4KB de données
    qDebug() << "🔹 Audio lu, taille :" << data.size();

    if (data.isEmpty()) {
        qDebug() << "⚠️ Aucune donnée audio à envoyer";
        return;
    }

    int rc = zmq_send(*pushSocket, data.data(), data.size(), 0);
    if (rc == -1) {
        qDebug() << "❌ Erreur zmq_send:" << zmq_strerror(zmq_errno());
    } else {
        qDebug() << "✅ Audio envoyé, taille :" << rc;
    }

    qDebug() << "🔹 Fin sendAudioData()";
}


// Fonction pour recevoir l'audio des étudiants (par exemple, d'un autre socket)
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

    char buffer[4096];
    int rc = zmq_recv(*pullSocket, buffer, sizeof(buffer), ZMQ_DONTWAIT); // Réception non bloquante

    if (rc == -1) {
        if (zmq_errno() != EAGAIN) {  // Ignorer l'erreur si aucune donnée n'est dispo
            qDebug() << "❌ Erreur zmq_recv:" << zmq_strerror(zmq_errno());
        } else {
            qDebug() << "⚠️ Pas de données audio disponibles";
        }
        return;
    }

    QByteArray data(buffer, rc);
    qDebug() << "✅ Audio reçu, taille :" << data.size();

    audioSinkDevice->write(data);
    qDebug() << "🔹 Fin receiveAudioData()";
}

