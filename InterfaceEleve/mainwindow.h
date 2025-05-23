#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "audioCommunicator.h"
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QNetworkInterface>
#include <QUdpSocket>
#include <QInputDialog>
#include <QShortcut>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHostAddress>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class InterfaceQCM;
class InterfaceAudio;
class InterfaceVideo;
class InterfaceEnregistrement;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    QString getNomEleve() {return nomEleve;};
    QString getNomProf() {return nomProf;};
    QString getConsigne() {return consigne;};
    QTime getTime() {return remainingTime;};
    QString getSessionPATH() {return sessionPATH;};


    ~MainWindow();

private slots:

    bool connectToDatabase();
    void on_pushButtonConnexion_clicked();
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void askPATH();
    void receiveInter();
    void receivePath();
    void receiveInfo();
    void receiveConsigne();
    void handleRestartCommand();
    void updateChrono();           // décrémente et met à jour
    void faireClignoterLabel();   // gère le clignotement
    void stopClignotement();
    void startChrono(const QTime &duree);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    bool isCtrlPressed = false;  // 🔹 Stocke l'état de Ctrl
    bool isF1Pressed = false;
    bool actionDone  = false;

    QString nomEleve = "";
    QString nomProf = "";
    QString consigne = "";
    QString sessionPATH = "";
    QMap<int, Student*> students;
    Student* currentStudent = nullptr;  // membre de la classe MainWindow


    QUdpSocket udpSocketInfo;
    quint16 infoPort = 5558;

    QUdpSocket udpSocketInter;
    quint16 interPort = 5560;

    QUdpSocket *udpSocketRestart;

    QUdpSocket *udpSocketNomFichier;
    quint16 portNomFichier = 5561;

    QUdpSocket udpSocketDemande;
    quint16 portDemande = 5561;

    QWidget *currentChild = nullptr;
    QShortcut *shortcutQcm;
    QShortcut *shortcutAudio;
    QShortcut *shortcutVideo;
    QTimer *chronoTimer = nullptr;
    QTime remainingTime;
    bool clignotementEtat = false;
    bool chronoClignote = false;

signals:
    void chronoMisAJour(const QString &temps);
    void chronoFini();


};
#endif // MAINWINDOW_H
