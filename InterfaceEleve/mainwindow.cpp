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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) {
        isCtrlPressed = true;
    }
    if (event->key() == Qt::Key_F1) {
        isF1Pressed = true;
    }

    // 📌 Vérifie si les deux touches sont pressées
    if (isCtrlPressed && isF1Pressed) {
        QSqlQuery query("SELECT * FROM Raspberry");

        if (!query.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError();
            return;
        }

        int id_raspberry = query.lastInsertId().toInt(); // en fonction du dernière id dans la bdd
        int maxPerRow = 7;
        int maxPerColumn = 7;
        int spacing = 50;

        int column = (id_raspberry - 1) % maxPerRow;
        int row = (id_raspberry - 1) / maxPerRow % maxPerColumn;

        int x = column * (spacing + 10);
        int y = row * (spacing + 10);



        // Enregistrer la rasp sur la bdd Raspberry
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
