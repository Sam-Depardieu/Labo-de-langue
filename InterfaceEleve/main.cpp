#include "mainwindow.h"
#include <audioCommunicator.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // Gardez uniquement cette ligne
    MainWindow w;
    w.show();
    qApp->setStyleSheet("QPushButton { background-color: transparent; border: none; }");


    AudioCommunicator communicator;

    // Envoi des données audio toutes les 100ms
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &communicator, &AudioCommunicator::sendAudioData);
    timer.start(100); // Envoie les données audio toutes les 100ms

    return a.exec();
}
