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
    // Affiche juste la barre de titre, sans les boutons Fermer, Minimiser, Maximiser
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

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
    // 1) Détecte Ctrl + F1
    if (event->key() == Qt::Key_Control) isCtrlPressed = true;
    if (event->key() == Qt::Key_F1)     isF1Pressed   = true;

    if (isCtrlPressed && isF1Pressed && !actionDone) {
        // 2) Récupère IP & MAC
        QString ipAddress, macAddress;
        for (auto iface : QNetworkInterface::allInterfaces()) {
            if (!(iface.flags() & QNetworkInterface::IsUp) ||
                !(iface.flags() & QNetworkInterface::IsRunning))
                continue;
            for (auto entry : iface.addressEntries()) {
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol &&
                    entry.ip() != QHostAddress::LocalHost) {
                    ipAddress  = entry.ip().toString();
                    macAddress = iface.hardwareAddress();
                    break;
                }
            }
            if (!ipAddress.isEmpty()) break;
        }
        if (ipAddress.isEmpty() || macAddress.isEmpty()) {
            QMessageBox::warning(this,
                                 "Erreur réseau",
                                 "Impossible de récupérer IP/MAC.");
            return;
        }

        // 3) Vérifie si l’IP existe déjà
        QSqlQuery checkIp;
        checkIp.prepare("SELECT COUNT(*) FROM Raspberry WHERE ip = :ip");
        checkIp.bindValue(":ip", ipAddress);
        if (!checkIp.exec() || !checkIp.next()) {
            QMessageBox::critical(this,
                                  "Erreur BDD",
                                  checkIp.lastError().text());
            return;
        }
        int existing = checkIp.value(0).toInt();

        // 4) Demande de saisie manuelle si besoin
        //    et choisit INSERT ou UPDATE
        bool overrideMode = false;
        if (existing > 0) {
            // IP déjà en base : propose de modifier l’ID de cet enregistrement
            auto reply = QMessageBox::question(
                this,
                "IP déjà présente",
                QString("L'IP %1 existe déjà.\nSouhaitez-vous modifier son ID manuellement ?")
                    .arg(ipAddress),
                QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                overrideMode = true;
            } else {
                return;
            }
        }

        // 5) Récupère l’ID max actuel (pour INSERT) ou la nouvelle valeur (pour UPDATE)
        int id_raspberry = 1;
        if (!overrideMode) {
            // INSERT → on calcule le prochain id
            QSqlQuery maxId;
            maxId.exec("SELECT MAX(id_raspberry) FROM Raspberry");
            if (maxId.next())
                id_raspberry = maxId.value(0).toInt() + 1;
            // laisse l’utilisateur changer cet ID avant l’INSERT
            bool ok;
            int manual = QInputDialog::getInt(
                this,
                "Choix de l'ID",
                "Entrez l'ID Raspberry à utiliser :",
                id_raspberry,    // valeur par défaut
                1, 1000, 1, &ok);
            if (!ok) return; // annulation
            id_raspberry = manual;
        } else {
            // UPDATE → on propose un nouvel ID pour l’IP existante
            bool ok;
            int manual = QInputDialog::getInt(
                this,
                "Override d'ID",
                QString("Entrez le nouvel ID pour l'IP %1 :").arg(ipAddress),
                existing, 1, 1000, 1, &ok);
            if (!ok) return;
            id_raspberry = manual;
        }

        // 6) Calcule coordonnées X/Y (réutilisé pour INSERT et UPDATE)
        int maxPerRow = 7, spacing = 50;
        int column = (id_raspberry - 1) % maxPerRow;
        int row    = (id_raspberry - 1) / maxPerRow;
        int x = column * (spacing + 10);
        int y = row    * (spacing + 10);

        // 7) Exécute la requête adéquate
        QSqlQuery q;
        if (overrideMode) {
            // UPDATE existing row
            q.prepare(R"(
                UPDATE Raspberry
                   SET id_raspberry = :id,
                       mac          = :mac,
                       x            = :x,
                       y            = :y
                 WHERE ip = :ip
            )");
        } else {
            // INSERT new row
            q.prepare(R"(
                INSERT INTO Raspberry
                  (id_raspberry, ip, mac, x, y)
                VALUES
                  (:id, :ip, :mac, :x, :y)
            )");
        }
        q.bindValue(":id",  id_raspberry);
        q.bindValue(":ip",  ipAddress);
        q.bindValue(":mac", macAddress);
        q.bindValue(":x",   x);
        q.bindValue(":y",   y);

        if (!q.exec()) {
            QMessageBox::critical(
                this,
                overrideMode ? "Erreur UPDATE" : "Erreur INSERT",
                q.lastError().text());
        } else {
            QMessageBox::information(
                this,
                "Succès",
                overrideMode
                    ? "ID mis à jour avec succès."
                    : "Nouveau Raspberry inséré avec succès.");
            actionDone = true;
        }
    }

    // Appelle l’implémentation parente pour les autres touches
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
                qDebug() << "Lance Interface please ALED";
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
