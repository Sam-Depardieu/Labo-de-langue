#include "mainwindow.h"
#include "interfaceaudio.h"
#include <unistd.h>
#include "interfaceenregistrement.h"
#include "interfaceqcm.h"
#include "interfacevideo.h"
#include "audioCommunicator.h"
#include "ui_mainwindow.h"
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
    , loadingMovie(new QMovie(":/videos/loading.gif"))
{
    ui->setupUi(this);
    //Affiche juste la barre de titre, sans les boutons Fermer, Minimiser, Maximiser
    //setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    ui->label_Loading->setMovie(loadingMovie);
    loadingMovie->start();

    setFixedSize(800,480);
    auto *shortcut = new QShortcut(QKeySequence(Qt::Key_1), this);
    connect(shortcut, &QShortcut::activated, this, [this]() {
        auto *rec = new InterfaceEnregistrement(this);
        rec->setAttribute(Qt::WA_DeleteOnClose);
        rec->show();
        interface = "rec";
    });
    shortcutQcm = new QShortcut(QKeySequence(Qt::Key_2), this);
    connect(shortcutQcm, &QShortcut::activated, this, [this]() {
        auto *qcm = new InterfaceQCM(this);
        qcm->setAttribute(Qt::WA_DeleteOnClose);
        qcm->show();
        interface = "qcm";
    });

    // Raccourci Touche 3 → Audio (écoute simple)
    shortcutAudio = new QShortcut(QKeySequence(Qt::Key_3), this);
    connect(shortcutAudio, &QShortcut::activated, this, [this]() {
        auto *audio = new InterfaceAudio(false, this);
        audio->setAttribute(Qt::WA_DeleteOnClose);
        audio->show();
        interface = "audio";
    });

    // Raccourci Touche 4 → Vidéo (lecture simple)
    shortcutVideo = new QShortcut(QKeySequence(Qt::Key_4), this);
    connect(shortcutVideo, &QShortcut::activated, this, [this]() {
        auto *video = new InterfaceVideo(false, this);
        video->setAttribute(Qt::WA_DeleteOnClose);
        video->show();
        interface = "video";
    });
    this->setWindowTitle("Page de Connexion");
    connectToDatabase();


    udpSocketInfo.bind(QHostAddress::Any, infoPort);
    connect(&udpSocketInfo, &QUdpSocket::readyRead, this, &MainWindow::receiveInfo);

    udpSocketNomFichier = new QUdpSocket(this);
    udpSocketNomFichier->bind(QHostAddress::Any, portNomFichier);
    connect(udpSocketNomFichier, &QUdpSocket::readyRead, this, &MainWindow::receivePath);

    // DEBUG socket bind + connect
    bool ok = udpSocketInter.bind(QHostAddress::AnyIPv4, 5560); // QHostAddress::AnyIPv4 = 0.0.0.0
    qDebug() << "📡 BIND udpSocketInter ok ? " << ok;
    connect(&udpSocketInter, &QUdpSocket::readyRead, this, &MainWindow::receiveInter);


    udpSocketRestart = new QUdpSocket(this);

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
        QString cmd = QString::fromUtf8(datagram).trimmed().toUtf8();
        qDebug() << "📢 RECV:" << cmd << "depuis" << sender.toString();

        if (cmd == "mute") {
            qDebug() << "🔇 Commande MUTE reçue";
            // Appelle ta fonction mute audio ici, par exemple :
            if(currentStudent) currentStudent->muteAudio();
        }
        else if (cmd == "unmute") {
            qDebug() << "🔈 Commande DEMUTE reçue";
            // Appelle ta fonction unmute audio ici, par exemple :
            if(currentStudent) currentStudent->unmuteAudio();
        }
        else if (cmd == "activerSon") {
            qDebug() << "✅ Commande ACTIVER SON reçue";
            // Active la diffusion sonore
        }
        else if (cmd == "desactionSon") {
            qDebug() << "🚫 Commande DESACTIVER SON reçue";
            // Désactive la diffusion sonore
        }
        else if (cmd == "RESTART") {
            qDebug() << "♻️ Redémarrage imminent…";
            // Effectue l'opération de redémarrage
        }
        else if (cmd == "END") {
            qDebug() << "🛑 Fin de la session reçue";
            // Traite la fin de session (fermeture, nettoyage, etc.)
        }
        else if (cmd == "pause") {
            if(interAudio) interAudio->setAudioPause(true);
            if(interVideo) interVideo->setVideoPause(true);
        }
        else if (cmd == "lecture") {
            if(interAudio) interAudio->setAudioPause(false);
            if(interVideo) interVideo->setVideoPause(false);
        }
        else {
            qDebug() << "⚠️ Commande inconnue reçue :" << cmd;
        }
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) isCtrlPressed = true;
    if (event->key() == Qt::Key_F1)     isF1Pressed = true;

    // Détection Ctrl + F1
    if (isCtrlPressed && isF1Pressed && !actionDone) {
        // Récupération IP & MAC
        QString ipAddress, macAddress;
        for (const auto &iface : QNetworkInterface::allInterfaces()) {
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
                                 tr("Erreur réseau"),
                                 tr("Impossible de récupérer IP/MAC."));
            return;
        }

        // Vérifier si MAC existe dans BDD
        QSqlQuery checkMac;
        checkMac.prepare("SELECT COUNT(*) FROM Raspberry WHERE mac = :mac");
        checkMac.bindValue(":mac", macAddress);
        if (!checkMac.exec() || !checkMac.next()) {
            QMessageBox::critical(this, tr("Erreur BDD"), checkMac.lastError().text());
            return;
        }

        if (checkMac.value(0).toInt() > 0) {
            // Update IP si MAC existe
            QSqlQuery upd;
            upd.prepare("UPDATE Raspberry SET ip = :ip WHERE mac = :mac");
            upd.bindValue(":ip", ipAddress);
            upd.bindValue(":mac", macAddress);
            if (!upd.exec()) {
                QMessageBox::critical(this, tr("Erreur UPDATE"), upd.lastError().text());
            } else {
                QMessageBox::information(this, tr("Succès"), tr("IP mise à jour pour MAC existante."));
            }
            actionDone = true;
            return;
        }
        // Insert nouvelle entrée
        QSqlQuery insert;
        insert.prepare("INSERT INTO Raspberry (ip, mac) VALUES (:ip, :mac)");
        insert.bindValue(":ip", ipAddress);
        insert.bindValue(":mac", macAddress);
        if (!insert.exec()) {
            QMessageBox::critical(this, tr("Erreur INSERT"), insert.lastError().text());
            return;
        }

        // Broadcast UDP
        QByteArray data = macAddress.toUtf8();
        udpSocket.writeDatagram(data, QHostAddress::Broadcast, 5560);

        actionDone = true;
        return;
    }



    // Ouvrir interfaces selon touche 1, 2, 3, 4
    switch (event->key()) {
    case Qt::Key_1: {
        auto *rec = new InterfaceEnregistrement(this);
        rec->setAttribute(Qt::WA_DeleteOnClose);
        rec->show();
        break;
    }
    case Qt::Key_2: {
        auto *qcm = new InterfaceQCM(this);
        qcm->setAttribute(Qt::WA_DeleteOnClose);
        qcm->show();
        break;
    }
    case Qt::Key_3: {
        auto *audio = new InterfaceAudio(false, this);
        audio->setAttribute(Qt::WA_DeleteOnClose);
        audio->show();
        break;
    }
    case Qt::Key_4: {
        auto *video = new InterfaceVideo(false, this);
        video->setAttribute(Qt::WA_DeleteOnClose);
        video->show();
        break;
    }
    default:
        break;
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

    // Réinitialise le flag si tu veux permettre une nouvelle action après un certain temps ou événement
    // actionDone = false; // Par exemple, tu pourrais mettre ceci ici pour que l'action puisse être répétée plus tard

    QMainWindow::keyReleaseEvent(event);
}


void MainWindow::receiveInfo() {
    while (udpSocketInfo.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketInfo.pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udpSocketInfo.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString response = QString::fromUtf8(datagram).trimmed();
        qDebug() << "📢 Message reçu de" << sender.toString() << ":" << response;

        if (sender.protocol() == QAbstractSocket::IPv4Protocol) {
            ipProf = sender.toString();
            qDebug() << "📡 Adresse IPv4 de l'expéditeur :" << ipProf;
        } else {
            qDebug() << "🌐 Adresse non IPv4 reçue, ignorée :" << sender.toString();
        }

        if (response.isEmpty())
            continue;

        if (!response.contains(",")) {
            qWarning() << "⛔ Format invalide (attendu clé,valeur)";
            continue;
        }

        QStringList parts = response.split(",");
        if (parts.size() != 2) {
            qWarning() << "⛔ Format invalide (attendu clé,valeur)";
            continue;
        }

        QString key = parts[0].trimmed();
        QString value = parts[1].trimmed();

        if (key == "nomProf") {
            nomProf = value;
            qDebug() << "👤 Nom du prof reçu :" << nomProf;

        } else if (key == "ipProf") {
            ipProf = value;
            qDebug() << "👤 Adresse ip prof reçu :" << ipProf;

        }else if (key == "nomEleve") {
            nomEleve = value;
            qDebug() << "👤 Nom de l'élève reçu :" << nomEleve;

        } else if (key == "chrono") {
            remainingTime = QTime::fromString(value, "mm:ss");
            qDebug() << "⏳ Temps restant :" << value;

        } else if (key == "consigne") {
            consigne = value;
            qDebug() << "📝 Consigne :" << consigne;

        }
        else if (key == "nomFichier") {
            nomFichier = value;
            qDebug() << "📝 nom du fichier :" << nomFichier;

        } else if (key == "portGroup") {
            bool ok;
            int port = value.toInt(&ok);
            if (!ok || port <= 0 || port > 65535) {
                qWarning() << "Port invalide reçu pour portGroup:" << value;
                return;
            }

            qDebug() << "🎧 Changement de groupe, port audio :" << port;

            // Supprimer l'étudiant courant si existant (arrêt audio, libération)
            if (currentStudent) {
                currentStudent->stopAudio();
                currentStudent->deleteLater();
                currentStudent = nullptr;
            }

            // Créer l'étudiant avec le port reçu (on ne crée que là)
            // À adapter : ici on passe groupe, adresse, port selon ton constructeur Student
            QString groupName = "defaultGroup"; // à remplacer si tu as le nom du groupe
            QHostAddress profAddress("192.168.64.1"); // IP du prof à configurer dynamiquement si besoin

            currentStudent = new Student(groupName, profAddress, static_cast<quint16>(port), this);
            // currentStudent->setProfIp("192.168.64.1"); // Si tu as encore cette méthode, sinon passe via constructeur
            // currentStudent->setGroupPort(port); // Idem, si constructeur gère déjà le port

            currentStudent->initializeAudioCommunication();

            qDebug() << "✅ Étudiant initialisé pour le groupe audio";
        }
        else {
            qWarning() << "🔍 Clé non reconnue :" << key;
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

        QString cheminFichier = QString("/mnt/partage/"+QString::fromUtf8(datagram).trimmed());
        qDebug() << "📄 Chemin reçu :" << cheminFichier;

        if (currentChild) {
            currentChild->close();
            delete currentChild;
            currentChild = nullptr;
        }

        sessionPATH = cheminFichier;
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
            interAudio = new InterfaceAudio(false, this);
            currentChild = interAudio;
        }
        else if (response == "ecoute_co") {
            interAudio = new InterfaceAudio(true, this);
            currentChild = interAudio;
        }
        else if (response == "video") {
            interVideo = new InterfaceVideo(false, this);
            currentChild = interVideo;
        }
        else if (response == "video_co") {
            interVideo = new InterfaceVideo(false, this);
            currentChild = interVideo;
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

void MainWindow::sendCommandToProf(const QString& profIp, int port, const QString& command)
{
    if (command.isEmpty()) return;

    QByteArray datagram = command.toUtf8();
    QHostAddress addr(profIp);
    udpSocket.writeDatagram(datagram, addr, port);
    qDebug() << "[Command] vers" << profIp << ":" << command;
}
