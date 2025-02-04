#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // Gardez uniquement cette ligne
    MainWindow w;
    w.show();
    return a.exec();
}
