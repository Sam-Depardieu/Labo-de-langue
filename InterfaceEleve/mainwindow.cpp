#include "mainwindow.h"
#include "interfaceaudio.h"
#include "interfaceenregistrement.h"
#include "interfaceqcm.h"
#include "interfacevideo.h"
#include "ui_mainwindow.h"
#include "attenteprof.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(800,480);
    this->setWindowTitle("Page de Connexion");
    connectToDatabase();
}

bool MainWindow::connectToDatabase() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        return true; // La connexion existe déjà
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.64.36");
    db.setDatabaseName("LaboLangue");
    db.setUserName("prof");
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
    this->hide();
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

bool isCtrlPressed = false;
bool isF1Pressed = false;

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) {
        isCtrlPressed = true;
    }
    if (event->key() == Qt::Key_F1) {
        isF1Pressed = true;
    }

    // ✅ Vérifie si Ctrl + F1 sont pressés en même temps
    if (isCtrlPressed && isF1Pressed) {
        qDebug() << "CTRL + F1 détecté !";

        // 🔎 Récupération de l'adresse IP et MAC
        QString ipAddress, macAddress;
        QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
        for (const QNetworkInterface &iface : interfaces) {
            if (iface.flags() & QNetworkInterface::IsUp && iface.flags() & QNetworkInterface::IsRunning) {
                QList<QNetworkAddressEntry> entries = iface.addressEntries();
                for (const QNetworkAddressEntry &entry : entries) {
                    if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol && entry.ip() != QHostAddress::LocalHost) {
                        ipAddress = entry.ip().toString();
                        macAddress = iface.hardwareAddress();
                        break;
                    }
                }
            }
            if (!ipAddress.isEmpty()) break;
        }

        qDebug() << "Adresse IP : " << ipAddress;
        qDebug() << "Adresse MAC : " << macAddress;

        // 🔍 Vérifier le dernier ID dans la BDD
        QSqlQuery query;
        query.prepare("SELECT MAX(id_raspberry) FROM Raspberry");
        if (!query.exec()) {
            qDebug() << "Erreur lors de la récupération de l'ID max :" << query.lastError();
            return;
        }

        int id_raspberry = 1; // Valeur par défaut
        if (query.next()) {
            id_raspberry = query.value(0).toInt() + 1; // Incrémentation
        }

        // 📌 Calcul des coordonnées X et Y
        int maxPerRow = 7;
        int spacing = 50;
        int column = (id_raspberry - 1) % maxPerRow;
        int row = (id_raspberry - 1) / maxPerRow;

        int x = column * (spacing + 10);
        int y = row * (spacing + 10);

        qDebug() << "Coordonnées calculées : X =" << x << ", Y =" << y;

        // ✅ Insérer les données dans la base
        query.prepare("INSERT INTO Raspberry (id_raspberry, ip, mac, x, y, Status) VALUES (:id, :ip, :mac, :x, :y, :status)");
        query.bindValue(":id", id_raspberry);
        query.bindValue(":ip", ipAddress);
        query.bindValue(":mac", macAddress);
        query.bindValue(":x", x);
        query.bindValue(":y", y);

        // On insère 1 si l'appareil est allumé (true), sinon 0 (false)
        int status = 1; // L'appareil est allumé
        query.bindValue(":status", status);

        if (!query.exec()) {
            qDebug() << "Erreur lors de l'insertion :" << query.lastError();
        } else {
            qDebug() << "✅ Insertion réussie dans la base de données !";
        }
    }

    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) {
        isCtrlPressed = false;
    }
    if (event->key() == Qt::Key_F1) {
        isF1Pressed = false;
    }

    QMainWindow::keyReleaseEvent(event);
}
