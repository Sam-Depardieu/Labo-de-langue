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

namespace Ui {
class choixSession;
}
class MainWindow;

class choixSession : public QWidget
{
    Q_OBJECT

public:
    explicit choixSession(MainWindow* parentWindow);

    ~choixSession();

private slots:
    void on_listeSession_itemDoubleClicked(QListWidgetItem *item);

private:
    MainWindow* mainWindow;
    Ui::choixSession *ui;

    QString basePath;
};

#endif // CHOIXSESSION_H
