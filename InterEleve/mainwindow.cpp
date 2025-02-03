#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interfacevideo.h"
#include "interfaceaudio.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , loadingMovie(new QMovie(":/Video/loading.gif"))
{
    ui->setupUi(this);
    this->setWindowTitle("Attente");

    setFixedSize(800,480);// place la fenêtre aux coordonnés : 100px,100px
        // largeur fixée à 500px et hauteur à 600px

    ui->label_Loading->setMovie(loadingMovie);
    loadingMovie->start();  // Démarrer l'animation

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.64.36");
    db.setDatabaseName("banque");
    db.setUserName("root");
    db.setPassword("okokok");
    db.setPort(3306);
    if (!db.open()) {
        qWarning() << "Erreur de connexion à la base de données:" << db.lastError().text();
    }
    else
    {
        qDebug() << "Connexion à la base de données réussie!";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete loadingMovie;
}
void MainWindow::startLoading()
{
    ui->label_Loading->setVisible(true);
    loadingMovie->start();
}
void MainWindow::stopLoading()
{
    ui->label_Loading->setVisible(false);
    loadingMovie->stop();
}
void MainWindow::on_pushButton_InterVideo_clicked()
{

    InterfaceVideo *interfaceVideo = new InterfaceVideo(this);
    interfaceVideo->show();
}
void MainWindow::on_label_Loading_linkActivated(const QString &link)
{

}


void MainWindow::on_pushButton_InterAudio_clicked()
{
    interfaceaudio *interfaceAudio = new interfaceaudio(this);
    interfaceAudio->show();
}

