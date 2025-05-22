#include "mainwindow.h"
#include "interfaceaudio.h"
#include "interfaceenregistrement.h"
#include "interfaceqcm.h"
#include "interfacevideo.h"
#include "audioCommunicator.h"
#include "ui_mainwindow.h"
#include "attenteprof.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QInputDialog>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Affiche juste la barre de titre, sans les boutons Fermer, Minimiser, Maximiser
    //setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    setFixedSize(800,480);
    auto *shortcut = new QShortcut(QKeySequence(Qt::Key_1), this);
    connect(shortcut, &QShortcut::activated, this, [this]() {
        auto *rec = new InterfaceEnregistrement(this);
        rec->setAttribute(Qt::WA_DeleteOnClose);
        rec->show();
    });
    shortcutQcm = new QShortcut(QKeySequence(Qt::Key_2), this);
    connect(shortcutQcm, &QShortcut::activated, this, [this]() {
        auto *qcm = new InterfaceQCM(this);
        qcm->setAttribute(Qt::WA_DeleteOnClose);
        qcm->show();
    });

    // Raccourci Touche 3 → Audio (écoute simple)
    shortcutAudio = new QShortcut(QKeySequence(Qt::Key_3), this);
    connect(shortcutAudio, &QShortcut::activated, this, [this]() {
        auto *audio = new InterfaceAudio(false, this);
        audio->setAttribute(Qt::WA_DeleteOnClose);
        audio->show();
    });

    // Raccourci Touche 4 → Vidéo (lecture simple)
    shortcutVideo = new QShortcut(QKeySequence(Qt::Key_4), this);
    connect(shortcutVideo, &QShortcut::activated, this, [this]() {
        auto *video = new InterfaceVideo(false, this);
        video->setAttribute(Qt::WA_DeleteOnClose);
        video->show();
    });
    this->setWindowTitle("Page de Connexion");
    connectToDatabase();

    // DEBUG socket bind + connect
    bool ok = udpSocketInter.bind(QHostAddress::AnyIPv4, 5560); // QHostAddress::AnyIPv4 = 0.0.0.0
    qDebug() << "📡 BIND udpSocketInter ok ? " << ok;
    connect(&udpSocketInter, &QUdpSocket::readyRead, this, &MainWindow::receiveInter);

    udpSocketInfo.bind(QHostAddress::Any, infoPort);
    connect(&udpSocketInfo, &QUdpSocket::readyRead, this, &MainWindow::receiveInfo);

    udpSocketRestart = new QUdpSocket(this);

    udpSocketNomFichier = new QUdpSocket(this);
    udpSocketNomFichier->bind(QHostAddress::Any, portNomFichier);
    connect(udpSocketNomFichier, &QUdpSocket::readyRead, this, &MainWindow::receivePath);

    if (!udpSocketRestart->bind(QHostAddress::Any, 5557)) {
        qWarning() << "❌ Impossible de binder le port 5557";
    } else {
        connect(udpSocketRestart,
                &QUdpSocket::readyRead,
                this,
                &MainWindow::handleRestartCommand);
        qDebug() << "✅ En écoute RESTART sur 5557";
    }

}

bool MainWindow::connectToDatabase() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        return true; // La connexion existe déjà
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.64.1");
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
    //this->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleRestartCommand()
{
    while (udpSocketRestart->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketRestart->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocketRestart->readDatagram(datagram.data(),
                                       datagram.size(),
                                       &sender,
                                       &senderPort);
        QString cmd = QString::fromUtf8(datagram).trimmed();
        qDebug() << "📢 RECV:" << cmd << "depuis" << sender.toString();

        if (cmd == "RESTART") {
            qDebug() << "♻️ Redémarrage imminent…";
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // 1) Détecte Ctrl + F1
    if (event->key() == Qt::Key_Control) isCtrlPressed = true;
    if (event->key() == Qt::Key_F1)     isF1Pressed   = true;

    // 2) Si les deux sont pressés et qu'on n'a pas déjà fait l'action
    if (isCtrlPressed && isF1Pressed && !actionDone) {
        // Récupère IP & MAC
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

        // Vérifie si l’IP existe déjà
        QSqlQuery checkIp;
        checkIp.prepare("SELECT COUNT(*) FROM Raspberry WHERE ip = :ip");
        checkIp.bindValue(":ip", ipAddress);
        if (!checkIp.exec() || !checkIp.next()) {
            QMessageBox::critical(this,
                                  "Erreur BDD",
                                  checkIp.lastError().text());
            return;
        }
        int existingCount = checkIp.value(0).toInt();

        // Si déjà en base, propose un override
        bool overrideMode = false;
        if (existingCount > 0) {
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

        // —————————————————————————————————————
        // Recherche du plus petit ID libre
        QSqlQuery idQuery;
        if (!idQuery.exec("SELECT id_raspberry FROM Raspberry ORDER BY id_raspberry")) {
            QMessageBox::critical(this,
                                  "Erreur BDD",
                                  idQuery.lastError().text());
            return;
        }

        int nextId = 1;
        while (idQuery.next()) {
            int existingId = idQuery.value(0).toInt();
            if (existingId == nextId) {
                ++nextId;
            } else if (existingId > nextId) {
                break;
            }
        }

        bool ok;
        int id_raspberry = nextId;
        if (!overrideMode) {
            id_raspberry = QInputDialog::getInt(
                this,
                "Choix de l'ID",
                "Entrez l'ID Raspberry à utiliser :",
                nextId,    // valeur par défaut = plus petit libre
                1, 1000, 1, &ok);
            if (!ok) return;
        } else {
            id_raspberry = QInputDialog::getInt(
                this,
                "Override d'ID",
                QString("Entrez le nouvel ID pour l'IP %1 :").arg(ipAddress),
                existingCount, 1, 1000, 1, &ok);
            if (!ok) return;
        }

        // 4) Calcule X/Y
        int maxPerRow = 7, spacing = 50;
        int column = (id_raspberry - 1) % maxPerRow;
        int row    = (id_raspberry - 1) / maxPerRow;
        int x = column * (spacing + 10);
        int y = row    * (spacing + 10);

        // 5) Exec INSERT ou UPDATE
        QSqlQuery q;
        if (overrideMode) {
            q.prepare(R"(
                UPDATE Raspberry
                   SET id_raspberry = :id,
                       mac          = :mac,
                       x            = :x,
                       y            = :y
                 WHERE ip = :ip
            )");
        } else {
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
    if (event->key() == Qt::Key_1) {
        auto *rec = new InterfaceEnregistrement(this);
        rec->setAttribute(Qt::WA_DeleteOnClose);
        rec->show();
        return;
    }

    // Touche 2 → QCM
    if (event->key() == Qt::Key_2) {
        auto *qcm = new InterfaceQCM(this);
        qcm->setAttribute(Qt::WA_DeleteOnClose);
        qcm->show();
        return;
    }

    // Touche 3 → Audio (écoute simple)
    if (event->key() == Qt::Key_3) {
        auto *audio = new InterfaceAudio(false, this);
        audio->setAttribute(Qt::WA_DeleteOnClose);
        audio->show();
        return;
    }

    // Touche 4 → Vidéo (lecture simple)
    if (event->key() == Qt::Key_4) {
        auto *video = new InterfaceVideo(false, this, this);
        video->setAttribute(Qt::WA_DeleteOnClose);
        video->show();
        return;
    }
    // Enfin, on laisse Qt traiter le reste
    QMainWindow::keyPressEvent(event);
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

void MainWindow::askPATH()
{

}

void MainWindow::receiveInfo() {
    while (udpSocketInfo.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketInfo.pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udpSocketInfo.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString response = QString::fromUtf8(datagram).trimmed();
        qDebug() << "📢 I reçue de" << sender.toString() << ":" << response;

        if (!response.isEmpty()) {
            // Vérifie que le message contient bien ':'
            if (response.contains(",")) {
                QStringList parts = response.split(",");

                if (parts.size() == 2) {
                    QString key = parts[0].trimmed();
                    QString value = parts[1].trimmed();

                    if (key == "nomProf") {
                        nomProf = value;
                        qDebug() << "👤 Nom du prof reçu :" << nomProf;
                    } else if (key == "nomEleve") {
                        nomEleve = value;
                        qDebug() << "👤 Nom de l'élève reçu :" << nomEleve;
                    }else if (key == "chrono"){
                        remainingTime = QTime::fromString(value,"mm:ss");
                        qDebug() << "temps restant :" << value;
                        qDebug() << "temps restant :" << remainingTime;
                    } else if (key =="consigne"){
                        consigne =value;
                        qDebug() <<"Consigne: " << consigne;
                    }else if (key == "portGroup"){
                        qDebug() << "value : " << value;
                        int port = value.toInt();
                        qDebug() << "port : " << port;
                        Student student(port);

                    } else {
                        qWarning() << "🔍 Clé non reconnue :" << key;
                    }
                }
            } else {
                qWarning() << "⛔ Format invalide (attendu nom:valeur)";
            }
        }
    }
}
void MainWindow::receivePath(){
    while (udpSocketNomFichier->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketNomFichier->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;
        udpSocketNomFichier->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString cheminFichier = QString::fromUtf8(datagram).trimmed();
        qDebug() << "📄 Chemin reçu :" << cheminFichier;

        if (!QFile::exists(cheminFichier)) {
            qWarning() << "❌ Fichier introuvable :" << cheminFichier;
            return;
        }

        if (currentChild) {
            currentChild->close();
            delete currentChild;
            currentChild = nullptr;
        }

        sessionPATH = cheminFichier;
        /*currentChild = new InterfaceQCM(this, cheminFichier);
        currentChild->setAttribute(Qt::WA_DeleteOnClose);
        currentChild->show();*/
    }
}

void MainWindow::receiveInter(){
    while (udpSocketInter.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketInter.pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;
        udpSocketInter.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString response = QString::fromUtf8(datagram).trimmed();
        qDebug() << "📢 Interface reçue :" << response;

        if (response.isEmpty())
            continue;

        if (currentChild) {
            currentChild->close();
            currentChild = nullptr;
        }

        if (response == "QCM") {
            currentChild = new InterfaceQCM(this);
        }
        else if (response == "ecoute") {
            currentChild = new InterfaceAudio(false, this);
        }
        else if (response == "ecoute_co") {
            currentChild = new InterfaceAudio(true, this);
        }
        else if (response == "video") {
            currentChild = new InterfaceVideo(false, this);
        }
        else if (response == "video_co") {
            currentChild = new InterfaceVideo(true, this);
        }
        else if (response == "enregistrement") {
            currentChild = new InterfaceEnregistrement(this);
        }

        if (currentChild) {
            currentChild->setAttribute(Qt::WA_DeleteOnClose);
            currentChild->show();
        }
    }
}

void MainWindow::startChrono(const QTime &duree)
{
    remainingTime = duree;

    if (!chronoTimer) {
        chronoTimer = new QTimer(this);
        connect(chronoTimer, &QTimer::timeout, this, &MainWindow::updateChrono);
    }
    chronoTimer->start(1000);
    chronoClignote = false;
    clignotementEtat = false;
}

void MainWindow::updateChrono()
{
    remainingTime = remainingTime.addSecs(-1);
    QString temps = remainingTime.toString("mm:ss");

    emit chronoMisAJour(temps); // 🔔 toutes les interfaces reçoivent

    if (remainingTime <= QTime(0, 0, 30)) {
        faireClignoterLabel();
    }

    if (remainingTime == QTime(0, 0)) {
        chronoTimer->stop();
        stopClignotement();
        emit chronoFini(); // 🔔 on notifie la fin
    }
}

void MainWindow::faireClignoterLabel()
{
    clignotementEtat = !clignotementEtat;
    chronoClignote = true;
}

void MainWindow::stopClignotement()
{
    chronoClignote = false;
    clignotementEtat = false;
}
void MainWindow::receiveConsigne()
{

}
