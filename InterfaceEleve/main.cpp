#include "mainwindow.h"
#include <audioCommunicator.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // Gardez uniquement cette ligne
    MainWindow w;
    w.showFullScreen();

    qApp->setStyleSheet("QPushButton { background-color: transparent; border: none; }");


    // Utiliser un timer pour envoyer et recevoir l'audio
    /*
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &profAudio, &Student::sendAudioData);
    timer.start(100);  // Envoie des données toutes les 100 ms

    // Vous pouvez également configurer un timer pour recevoir l'audio si nécessaire
    QTimer receiveAudioTimer;
    QObject::connect(&receiveAudioTimer, &QTimer::timeout, &profAudio, &Student::receiveAudioData);
    receiveAudioTimer.start(100);  // Recevoir des données toutes les 100 ms
    */
    return a.exec();
}
