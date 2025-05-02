#include "AudioCommunicator.h"

#include <QAudioSource>
#include <QAudioSink>
#include <QHostAddress>
#include <QThread>

Professor::Professor(QObject *parent) : QObject(parent), context(1) {
    QAudioFormat format;
    format.setSampleRate(16000);  // 44.1 kHz standard
    format.setChannelCount(1);  // Mono
    format.setSampleFormat(QAudioFormat::Int16);  // Format 16-bit

    inputDeviceInfo = QMediaDevices::defaultAudioInput();
    outputDeviceInfo = QMediaDevices::defaultAudioOutput();

    // Vérification et initialisation du micro
    if (!inputDeviceInfo.isNull()) {
        qDebug() << "🎤 Micro détecté:" << inputDeviceInfo.description();
        try {
            audioSource = new QAudioSource(inputDeviceInfo, format);
            audioSourceDevice = audioSource->start();  // Démarre l’enregistrement
            if (audioSourceDevice) {
                qDebug() << "✅ Enregistrement du micro lancé";
            } else {
                qDebug() << "❌ Échec de l'enregistrement du micro";
            }
        } catch (const std::exception &e) {
            qDebug() << "❌ Erreur lors de la création du QAudioSource:" << e.what();
        }
    } else {
        QMessageBox::critical(
            nullptr,
            "Microphone non détecté",
            "❌ Aucun microphone n'a été détecté.\n"
            "La communication audio avec les élèves est impossible.\n\n"
            "Veuillez connecter un microphone et redémarrer l'application."
            );
            return;
        }

    // Vérification et initialisation des haut-parleurs
    if (!outputDeviceInfo.isNull()) {
        qDebug() << "🔊 Haut-parleur détecté:" << outputDeviceInfo.description();
        try {
            audioSink = new QAudioSink(outputDeviceInfo, format);
            audioSinkDevice = audioSink->start();
            if (audioSinkDevice) {
                qDebug() << "✅ Sortie audio lancée";
            } else {
                qDebug() << "❌ Échec de la sortie audio";
            }
        } catch (const std::exception &e) {
            qDebug() << "❌ Erreur lors de la création du QAudioSink:" << e.what();
        }
    } else {
        QMessageBox::critical(
            nullptr,
            "Haut parleur non détecté",
            "❌ Aucun haut parleur n'a été détecté.\n"
            "La communication audio avec les élèves est impossible.\n\n"
            "Veuillez connecter un microphone et redémarrer l'application."
            );
        return;
    }

    // Vérification des sockets ZeroMQ
    if (pushSocket == nullptr) {
        try {
            pushSocket = new zmq::socket_t(context, ZMQ_PUSH);
            pushSocket->connect("tcp://localhost:5555");
            qDebug() << "✅ Socket PUSH créé et connecté.";
        } catch (const zmq::error_t &e) {
            qDebug() << "❌ Erreur lors de la création du socket PUSH:" << e.what();
        }
    }

    if (pullSocket == nullptr) {
        try {
            pullSocket = new zmq::socket_t(context, ZMQ_PULL);
            pullSocket->bind("tcp://*:5556");
            qDebug() << "✅ Socket PULL créé et lié.";
        } catch (const zmq::error_t &e) {
            qDebug() << "❌ Erreur lors de la création du socket PULL:" << e.what();
        }
    }

    // Connexion des timers aux slots
    connect(&sendAudioTimer, &QTimer::timeout, this, &Professor::sendAudioData);
    connect(&receiveAudioTimer, &QTimer::timeout, this, &Professor::receiveAudioData);

    // Lancement des timers
    sendAudioTimer.start(100);  // Intervalle en millisecondes
    receiveAudioTimer.start(100);

    //sendCommandToStudent("192.168.64.113", "mute");
}

void Professor::sendCommandToStudent(const QString& studentIp, int port, const QString& command) {
    if(command == "" )
    {
        return;
    }
    QString fullCommand = command;
    QByteArray datagram = fullCommand.toUtf8();
    QHostAddress studentAddress(studentIp);
    udpSocket.writeDatagram(datagram, studentAddress, port);
    qDebug() << "📢 Commande envoyée :" << fullCommand;
}

void Professor::muteStudent(const QString& studentIp) {
    sendCommandToStudent(studentIp, 5557, "mute");
    qDebug() << "🔇 Élève" << studentIp << "muté!";
}

void Professor::unmuteStudent(const QString& studentIp) {
    sendCommandToStudent(studentIp, 5557, "unmute");
    qDebug() << "🎤 Élève" << studentIp << "démuté!";
}


void Professor::activerSonStudent(const QString& studentIp){
    sendCommandToStudent(studentIp, 5557, "activerSon");
    qDebug() << "🎤 Élève" << studentIp << "son activé !";
}

void Professor::desactiverSonStudent(const QString& studentIp){
    sendCommandToStudent(studentIp, 5557, "desactiverSon");
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
    //qDebug() << "?? Début sendAudioData()";



    QByteArray data = audioSourceDevice->readAll();
    //qDebug() << "🔹 Audio lu, taille :" << data.size();

    if (data.isEmpty()) {
        //qDebug() << "⚠️ Aucune donnée audio à envoyer";
        return;
    }

    if (!pushSocket) {
        //qDebug() << "❌ Erreur: pushSocket est NULL!";
        return;
    }

    try {
        zmq::message_t message(data.constData(), data.size());
        pushSocket->send(message, zmq::send_flags::none);
        //qDebug() << "🗣️ Professeur parle, taille des données envoyées:" << data.size();
    } catch (const std::runtime_error &e) {
        //qDebug() << "❌ Erreur lors de l'envoi des données audio:" << e.what();
    }
}

// Fonction pour recevoir l'audio des étudiants
void Professor::receiveAudioData() {
    //qDebug() << "🔹 Début receiveAudioData()";

    if (!pullSocket) {
        //qDebug() << "⚠️ pullSocket non initialisé";
        return;
    }

    zmq::message_t message;
    zmq::recv_result_t result = pullSocket->recv(message, zmq::recv_flags::dontwait); // Réception non bloquante

    if (!result) {
        return;
    }

    QByteArray data(static_cast<char*>(message.data()), message.size());
    //qDebug() << "✅ Audio reçu, taille :" << data.size();

    audioSinkDevice->write(data);
    //qDebug() << "🔹 Fin receiveAudioData()";
}


