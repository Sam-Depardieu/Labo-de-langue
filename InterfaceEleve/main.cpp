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

    return a.exec();
}
