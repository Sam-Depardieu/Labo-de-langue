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
#include <QKeyEvent>
#include <QDialog>
#include <QMovie>


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
    QString getIpProf() {return ipProf;}
    QString getNomFichier() {return nomFichier;}

    void sendCommandToProf(const QString& ipProf, int port, const QString& command);


    ~MainWindow();

private slots:

    bool connectToDatabase();
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void receiveInter();
    void receivePath();
    void receiveInfo();
    void handleRestartCommand();
    void updateChrono();           // décrémente et met à jour
    void faireClignoterLabel();   // gère le clignotement
    void stopClignotement();
    void startChrono(const QTime &duree);
    void receiveEndMessage(); // Slot pour recevoir le message "END"
    void moveAndSendFiles();
private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    bool isCtrlPressed = false;  // 🔹 Stocke l'état de Ctrl
    bool isF1Pressed = false;
    bool actionDone  = false;

    QString nomEleve = "";
    QString nomProf = "";
    QString ipProf = "";
    QString consigne = "";
    QString sessionPATH = "";
    QMap<int, Student*> students;
    Student* currentStudent = nullptr;  // membre de la classe MainWindow
    QUdpSocket *udpSocket;

    QUdpSocket *udpSocketEnd;
    quint16 EndPort = 5557;

    QUdpSocket udpSocketInfo;
    quint16 infoPort = 5558;

    QUdpSocket udpSocketInter;
    quint16 interPort = 5560;

    QUdpSocket *udpSocketRestart;

    QUdpSocket *udpSocketNomFichier;
    quint16 portNomFichier = 5561;
    QUdpSocket udpSocketConsigne;
    quint16 portConsigne = 5558;

    QUdpSocket udpSocketDemande;
    quint16 portDemande = 5561;

    InterfaceAudio* interAudio = nullptr;
    InterfaceVideo* interVideo = nullptr;

    QWidget *currentChild = nullptr;
    QShortcut *shortcutQcm;
    QShortcut *shortcutAudio;
    QShortcut *shortcutVideo;
    QTimer *chronoTimer = nullptr;
    QTime remainingTime;
    bool clignotementEtat = false;
    bool chronoClignote = false;
    QString interface = "";
    QString nomFichier = "";

    QMovie *loadingMovie;

    void startLoading();
    void stopLoading();
    void mountNetworkDrive();
signals:
    void chronoMisAJour(const QString &temps);
    void chronoFini();


};
#endif // MAINWINDOW_H
