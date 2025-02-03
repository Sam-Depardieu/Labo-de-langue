#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interfaceaudioco.h"  // Inclure le fichier d'en-tête pour InterfaceAudioCO
#include "interfaceenregistrement.h"
#include "interfaceqcm.h"
#include <QDebug> // Pour les messages de débogage

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // Initialisation de l'interface utilisateur

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.64.36");
    db.setDatabaseName("LaboLangue");
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

    //db.close();
    this->setStyleSheet("background-color: white; color : black;");
    this->setStatusBar(nullptr);  // Supprime la barre d'état




    this->setWindowTitle("Interface Connexion");
    qWarning() << "Connexion du signal du bouton 'Connexion'"; // Ajout de debug
    setFixedSize(800, 480); // Remplacez 800 et 480 par la largeur et la hauteur souhaitées
    qWarning() << "Signal connecté"; // Ajout de debug

    qWarning() << "Connexion du signal du bouton 'Enregistrement'";
    connect(ui->pushButtonEnregistrement, &QPushButton::clicked, this, &MainWindow::openInterfaceEnregistrement);
    qWarning() << "Signal connecté";
}

void MainWindow::openInterfaceEnregistrement()
{
    static int count = 0;
    qWarning() << "Interface Enregistrement appelé :" << ++count; // Ajout de debug avec compteur

    InterfaceEnregistrement *interfaceEnregistrement = new InterfaceEnregistrement(this);
    interfaceEnregistrement->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonConnexion_clicked()
{
    InterfaceAudioCO *interfaceAudioCO = new InterfaceAudioCO(this);
    interfaceAudioCO->show();
}

void MainWindow::on_pushButtonInterfaceQCM_clicked()
{
    InterfaceQCM *interfaceQCM = new InterfaceQCM(this);
    interfaceQCM->show();
}

