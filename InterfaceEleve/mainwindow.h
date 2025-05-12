#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QProcess>
#include <QSqlQuery>
#include <QSqlError>
#include <QNetworkInterface>
#include <QUdpSocket>
#include <QInputDialog>
#include <QShortcut>
#include <QUdpSocket>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class InterfaceQCM;
class InterfaceAudio;
class InterfaceVideo;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    QString getNomEleve() {return nomEleve;};
    QString getNomProf() {return nomProf;};
    QString getConsigne() {return consigne;};


    ~MainWindow();

private slots:

    bool connectToDatabase();
    void on_pushButtonEnregistrement_clicked();
    void on_pushButtonConnexion_clicked();

    void on_pushButtonInterfaceQCM_clicked();

    void on_pushButtonInterfaceAudio_clicked();

    void on_pushButtonInterfaceVideo_clicked();

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void receiveResponse();
    void receiveCommand(const QString& cmd);
private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    bool isCtrlPressed = false;  // 🔹 Stocke l'état de Ctrl
    bool isF1Pressed = false;
    bool actionDone  = false;

    QString nomEleve = "";
    QString nomProf = "";
    QString consigne = "";

    QUdpSocket udpSocketInfo;
    quint16 infoPort = 5558;
    QUdpSocket udpSocketConsigne;
    quint16 consignePort = 5558;
    QUdpSocket udpSocketInter;
    quint16 interPort = 5560;
    QWidget *currentChild = nullptr;
    QShortcut *shortcutQcm;
    QShortcut *shortcutAudio;
    QShortcut *shortcutVideo;
};
#endif // MAINWINDOW_H
