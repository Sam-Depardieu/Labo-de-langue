#include "mainwindow.h"
#include "interfaceaudio.h"
#include "interfaceenregistrement.h"
#include "interfaceqcm.h"
#include "interfacevideo.h"
#include "ui_mainwindow.h"
#include "attenteprof.h"
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(800,480);
    this->setWindowTitle("Page de Connexion");
    connect(ui->pushButtonConnexion, &QPushButton::clicked, this, &MainWindow::on_pushButtonConnexion_clicked);

    this->setStatusBar(nullptr);
    connectToDatabase();
}


bool MainWindow::connectToDatabase() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        return true; // La connexion existe déjà
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("LaboLangue");
    db.setUserName("root");
    db.setPassword("okokok");

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données:" << db.lastError().text();
        return false;
    }
    return true;
}
void MainWindow::on_pushButtonConnexion_clicked()
{
    AttenteProf *attenteProf = new AttenteProf(this);
    attenteProf->show();
}
void MainWindow::on_pushButtonEnregistrement_clicked()
{
    InterfaceEnregistrement *interfaceEnregistrement = new InterfaceEnregistrement(this);
    interfaceEnregistrement->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButtonInterfaceQCM_clicked()
{
    InterfaceQCM *interfaceQCM = new InterfaceQCM(this);
    interfaceQCM->show();
}
void MainWindow::on_pushButtonInterfaceAudio_clicked()
{
    InterfaceAudio *interfaceAudio = new InterfaceAudio(this);
    interfaceAudio->show();
}
void MainWindow::on_pushButtonInterfaceVideo_clicked()
{
    InterfaceVideo *interfaceVideo = new InterfaceVideo(this);
    interfaceVideo->show();
}

