#include "mainwindow.h"
#include "AudioCommunicator.h"
#include "qsqlerror.h"
#include "qsqlquery.h"

#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QAudioInput>
#include <QAudioOutput>
#include <QUdpSocket>
#include <QIODevice>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QUrl>
#include <QApplication>
#include <QCoreApplication>
#include <QNetworkInterface>
#include <QDebug>
#include <QHostInfo>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}



