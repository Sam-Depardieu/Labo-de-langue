#include "AudioCommunicator.h"

Professor::Professor(const QString& serverIp) : serverIp(serverIp), context(1) {}

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
