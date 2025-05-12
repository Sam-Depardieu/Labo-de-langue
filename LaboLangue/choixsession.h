#ifndef CHOIXSESSION_H
#define CHOIXSESSION_H

// === Qt Core / GUI ===
#include <QDialog>
#include <QListWidget>
#include <QDir>
#include <QFile>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardItemModel>

class MainWindow;

namespace Ui {
class choixSession;
}

class choixSession : public QDialog {
    Q_OBJECT

public:
    explicit choixSession(MainWindow* parentWindow);
    ~choixSession();

private slots:
    void on_listeSession_itemDoubleClicked(QListWidgetItem *item);
    void on_findLineEdit_textChanged(const QString &arg1);
    void on_sortAZButton_clicked();
    void on_sortZAButton_clicked();
    void on_takeSessionButton_clicked();
    void on_delSessionButton_clicked();

private:
    Ui::choixSession *ui;
    MainWindow* mainWindow;
    QString basePath;

    void trierListeSessions(bool ordreCroissant);
};

#endif // CHOIXSESSION_H
