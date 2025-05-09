#ifndef CHOIXSESSION_H
#define CHOIXSESSION_H

#include <QMainWindow>
#include <QListWidget>
#include <QColumnView>
#include <QSplitter>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class choixSession;
}
class MainWindow;

class choixSession : public QDialog
{
    Q_OBJECT

public:
    explicit choixSession(MainWindow* parentWindow);

    ~choixSession();

private slots:
    void on_listeSession_itemDoubleClicked(QListWidgetItem *item);
    void trierListeSessions(bool ordreCroissant);
    void on_findLineEdit_textChanged(const QString &arg1);

    void on_sortAZButton_clicked();
    void on_sortZAButton_clicked();

    void on_takeSessionButton_clicked();

    void on_delSessionButton_clicked();

private:
    MainWindow* mainWindow;
    Ui::choixSession *ui;

    QString basePath;
};

#endif // CHOIXSESSION_H
