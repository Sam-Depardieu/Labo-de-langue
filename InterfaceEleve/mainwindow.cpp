#include "mainwindow.h"
#include "interfaceaudio.h"
#include "interfaceenregistrement.h"
#include "interfaceqcm.h"
#include "interfacevideo.h"
#include "ui_mainwindow.h"
#include "attenteprof.h"
#include <QNetworkInterface>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(800,480);
    this->setWindowTitle("Page de Connexion");

    this->setStatusBar(nullptr);
    connectToDatabase();
}
QString getLocalIPAddress() {
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback()) {
            return address.toString();
        }
    }
    return "0.0.0.0"; // Valeur par défaut si aucune adresse trouvée
}

QString getMacAddress() {
    foreach (const QNetworkInterface &netInterface, QNetworkInterface::allInterfaces()) {
        if (!(netInterface.flags() & QNetworkInterface::IsLoopBack)) {
            return netInterface.hardwareAddress();
        }
    }
    return "00:00:00:00:00:00"; // Valeur par défaut si aucune adresse trouvée
}
bool MainWindow::connectToDatabase() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        return true; // La connexion existe déjà
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.64.36");
    db.setDatabaseName("LaboLangue");
    db.setPassword("okokok"); // Remplacez par votre mot de passe

    if (!db.open()) {
        qDebug() << "Impossible de se connecter à la base de données :" << db.lastError();
        return false;
    }
    qDebug() << "Connecté à la base de données :";
    return true;
}

void MainWindow::on_pushButtonConnexion_clicked()
{
    AttenteProf *attenteProf = new AttenteProf(this);
    attenteProf->show();

    QString ipAddress = getLocalIPAddress();
    QString macAddress = getMacAddress();
    qDebug() << "Adresse IP:" << ipAddress;
    qDebug() << "Adresse MAC:" << macAddress;

    // 2️⃣ Connexion à la base de données
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // Adapter au type de BDD utilisé
    db.setHostName("localhost");
    db.setDatabaseName("LaboLangue");  // Nom de votre base
    db.setUserName("root");  // Remplacez par votre utilisateur SQL
    db.setPassword("okokok");  // Mot de passe si nécessaire

    if (!db.open()) {
        qDebug() << "Échec de la connexion:" << db.lastError().text();
        ui->pushButtonConnexion->setText("Connexion échouée ");
        return;
    }

    // 3️⃣ Mettre à jour le statut dans la base
    QSqlQuery query;
    query.prepare("INSERT INTO Raspberry (IP, MAC, Status) "
                  "VALUES (:ip, :mac, 1) "
                  "ON DUPLICATE KEY UPDATE Status = 1");

    query.bindValue(":ip", ipAddress);
    query.bindValue(":mac", macAddress);

    if (query.exec()) {
        qDebug() << "Connexion enregistrée avec succès ";
        ui->pushButtonConnexion->setText("Connecté ");

    } else {
        qDebug() << "Erreur lors de l'insertion:" << query.lastError().text();
        ui->pushButtonConnexion->setText("Échec ");
    }

    db.close();

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
void MainWindow::closeEvent(QCloseEvent *event)
{
    // Connexion à la base
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("UPDATE Raspberry SET Status = 0 WHERE MAC = :mac");
        query.bindValue(":mac", getMacAddress());

        if (query.exec()) {
            qDebug() << "Déconnexion réussie, statut mis à jour ";
        } else {
            qDebug() << "Erreur mise à jour statut:" << query.lastError().text();
        }
    }

    event->accept();
}

