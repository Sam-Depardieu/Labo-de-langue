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


    udpSocketInfo.bind(QHostAddress::Any, infoPort);
    connect(&udpSocketInfo, &QUdpSocket::readyRead, this, &MainWindow::receiveResponse);

    udpSocketConsigne.bind(QHostAddress::Any, consignePort);
    connect(&udpSocketConsigne, &QUdpSocket::readyRead, this, &MainWindow::receiveResponse);

    udpSocketInter.bind(QHostAddress::Any, interPort);
    connect(&udpSocketInter, &QUdpSocket::readyRead, this, &MainWindow::receiveResponse);

}

bool MainWindow::connectToDatabase() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        return true; // La connexion existe déjà
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.89.42");
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
    // Vérification des touches Ctrl et F1
    if (event->key() == Qt::Key_Control) {
        isCtrlPressed = true;
    }
    if (event->key() == Qt::Key_F1) {
        isF1Pressed = true;
    }

    // Vérifie si Ctrl + F1 sont pressés en même temps
    if (isCtrlPressed && isF1Pressed) {
        // Si l'action a déjà été effectuée, ne rien faire
        if (actionDone) {
            qDebug() << "L'action a déjà été effectuée. Aucune insertion.";
            return;
        }

        // Récupérer l'adresse IP et MAC
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

        if (ipAddress.isEmpty() || macAddress.isEmpty()) {
            qDebug() << "Erreur : Impossible de récupérer l'adresse IP/MAC.";
            return;
        }

        qDebug() << "Adresse IP : " << ipAddress;
        qDebug() << "Adresse MAC : " << macAddress;

        // Vérification si l'IP est déjà présente dans la base de données
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM Raspberry WHERE ip = :ip");
        query.bindValue(":ip", ipAddress);
        if (!query.exec()) {
            qDebug() << "Erreur lors de la vérification de l'IP : " << query.lastError();
            return;
        }

        // Vérifie si l'adresse IP existe déjà
        query.next();
        int count = query.value(0).toInt();
        if (count > 0) {
            qDebug() << "L'adresse IP " << ipAddress << " existe déjà dans la base de données.";
            return;  // Ne pas insérer dans la base de données
        }

        // Si l'adresse IP n'existe pas, on procède à l'insertion
        qDebug() << "Adresse IP unique, insertion dans la base de données...";

        // Vérifier le dernier ID dans la BDD
        query.prepare("SELECT MAX(id_raspberry) FROM Raspberry");
        if (!query.exec()) {
            qDebug() << "Erreur lors de la récupération de l'ID max :" << query.lastError();
            return;
        }

        int id_raspberry = 1; // Valeur par défaut
        if (query.next()) {
            id_raspberry = query.value(0).toInt() + 1; // Incrémentation
        }

        // Calcul des coordonnées X et Y
        int maxPerRow = 7;
        int spacing = 50;
        int column = (id_raspberry - 1) % maxPerRow;
        int row = (id_raspberry - 1) / maxPerRow;

        int x = column * (spacing + 10);
        int y = row * (spacing + 10);

        qDebug() << "Coordonnées calculées : X =" << x << ", Y =" << y;

        // Insérer les données dans la base
        query.prepare("INSERT INTO Raspberry (id_raspberry, ip, mac, x, y) VALUES (:id, :ip, :mac, :x, :y)");
        query.bindValue(":id", id_raspberry);
        query.bindValue(":ip", ipAddress);
        query.bindValue(":mac", macAddress);
        query.bindValue(":x", x);
        query.bindValue(":y", y);


        if (!query.exec()) {
            qDebug() << "Erreur lors de l'insertion :" << query.lastError();
        } else {
            qDebug() << "Insertion réussie dans la base de données !";
            actionDone = true;  // Marque l'action comme terminée pour empêcher les nouvelles insertions
        }
    }

    QMainWindow::keyPressEvent(event);
}
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{ if (event->key() == Qt::Key_Control) {
        isCtrlPressed = false;
    }
    if (event->key() == Qt::Key_F1) {
        isF1Pressed = false;
    }

    // Réinitialise le flag si tu veux permettre une nouvelle action après un certain temps ou événement
    // actionDone = false; // Par exemple, tu pourrais mettre ceci ici pour que l'action puisse être répétée plus tard

    QMainWindow::keyReleaseEvent(event);
}

void MainWindow::receiveResponse() {
    while (udpSocketInfo.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketInfo.pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udpSocketInfo.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString response = QString::fromUtf8(datagram).trimmed();
        qDebug() << "📢 Réponse reçue de" << sender.toString() << ":" << response;

        if (!response.isEmpty()) {
            // Vérifie que le message contient bien ':'
            if (response.contains(":")) {
                QStringList parts = response.split(":");

                if (parts.size() == 2) {
                    QString key = parts[0].trimmed();
                    QString value = parts[1].trimmed();

                    if (key == "nomProf") {
                        nomProf = value;
                        qDebug() << "👤 Nom du prof reçu :" << nomProf;
                    } else if (key == "nomEleve") {
                        nomEleve = value;
                        qDebug() << "👤 Nom de l'élève reçu :" << nomEleve;
                    } else {
                        qWarning() << "🔍 Clé non reconnue :" << key;
                    }
                }
            } else {
                qWarning() << "⛔ Format invalide (attendu nom:valeur)";
            }
        }
    }

    while (udpSocketConsigne.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketConsigne.pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udpSocketConsigne.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString response = QString::fromUtf8(datagram).trimmed();
        qDebug() << "📢 Réponse reçue de" << sender.toString() << ":" << response;

        if (!response.isEmpty()) {
            consigne = response;
        }
    }

    while (udpSocketInter.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketInter.pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udpSocketInter.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString response = QString::fromUtf8(datagram).trimmed();
        qDebug() << "📢 Interface reçue :" << response;

        if (!response.isEmpty()) {
            if (response == "QCM") {
                (new InterfaceQCM())->show();
            } else if (response == "ecoute") {
                (new InterfaceAudio(false))->show();
            } else if (response == "ecoute_co") {
                (new InterfaceAudio(true))->show();
            } else if (response == "video") {
                (new InterfaceVideo(false))->show();
            } else if (response == "video_co") {
                (new InterfaceVideo(true))->show();
            } else if (response == "enregistrement") {
                (new InterfaceEnregistrement())->show();
            }
        }
    }
}
