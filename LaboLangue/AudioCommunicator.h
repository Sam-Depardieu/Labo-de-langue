#ifndef AUDIOCOMMUNICATOR_H
#define AUDIOCOMMUNICATOR_H

#include <QString>
#include <zmq.hpp>
#include <QDebug>

class Professor {
public:
    Professor(const QString& serverIp);
    void muteStudent(const QString& studentIp);
    void unmuteStudent(const QString& studentIp);
    void sendCommandToStudent(const QString& studentIp, const QString& command);
    QString getStudentStatus(const QString& studentIp);

private:
    QString serverIp;
    zmq::context_t context;
};

#endif // AUDIOCOMMUNICATOR_H
