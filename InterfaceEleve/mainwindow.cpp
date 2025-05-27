#include "mainwindow.h"
#include "interfaceaudio.h"
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
#include <QShortcut>
#include <QMovie>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , loadingMovie(new QMovie(":/videos/loading.gif"))
{
    ui->setupUi(this);
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

    shortcutAudio = new QShortcut(QKeySequence(Qt::Key_3), this);
    connect(shortcutAudio, &QShortcut::activated, this, [this]() {
        auto *audio = new InterfaceAudio(false, this);
        audio->setAttribute(Qt::WA_DeleteOnClose);
        audio->show();
        interface = "audio";
    });

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

    bool ok = udpSocketInter.bind(QHostAddress::AnyIPv4, 5560);
    qDebug() << "📡 BIND udpSocketInter ok ? " << ok;
    connect(&udpSocketInter, &QUdpSocket::readyRead, this, &MainWindow::receiveInter);

    udpSocketRestart = new QUdpSocket(this);
    if (!udpSocketRestart->bind(QHostAddress::Any, 5557)) {
        qWarning() << "❌ Impossible de binder le port 5557";
    } else {
        connect(udpSocketRestart, &QUdpSocket::readyRead, this, &MainWindow::handleRestartCommand);
        qDebug() << "✅ En écoute RESTART sur 5557";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete loadingMovie;
}

bool MainWindow::connectToDatabase() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) return true;

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

void MainWindow::startLoading() {
    ui->label_Loading->setVisible(true);
    loadingMovie->start();
}

void MainWindow::stopLoading() {
    ui->label_Loading->setVisible(false);
    loadingMovie->stop();
}

void MainWindow::handleRestartCommand() {
    while (udpSocketRestart->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketRestart->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocketRestart->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QString cmd = QString::fromUtf8(datagram).trimmed().toUtf8();

        qDebug() << "📢 RECV:" << cmd << "depuis" << sender.toString();

        if (cmd == "mute") {
            if(currentStudent) currentStudent->muteAudio();
        }
        else if (cmd == "unmute") {
            if(currentStudent) currentStudent->unmuteAudio();
        }
        else if (cmd == "pause") {
            if(interAudio) interAudio->setAudioPause(true);
            if(interVideo) interVideo->setVideoPause(true);
        }
        else if (cmd == "lecture") {
            if(interAudio) interAudio->setAudioPause(false);
            if(interVideo) interVideo->setVideoPause(false);
        }
        else if (cmd == "RESTART") {
            qDebug() << "♻️ Redémarrage imminent…";
        }
        else if (cmd == "END") {
            qDebug() << "🛑 Fin de la session reçue";
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

    if (isCtrlPressed && isF1Pressed && !actionDone) {
        QString ipAddress, macAddress;
        for (const auto &iface : QNetworkInterface::allInterfaces()) {
            if (!(iface.flags() & QNetworkInterface::IsUp) || !(iface.flags() & QNetworkInterface::IsRunning)) continue;
            for (auto entry : iface.addressEntries()) {
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol && entry.ip() != QHostAddress::LocalHost) {
                    ipAddress = entry.ip().toString();
                    macAddress = iface.hardwareAddress();
                    break;
                }
            }
            if (!ipAddress.isEmpty()) break;
        }

        if (ipAddress.isEmpty() || macAddress.isEmpty()) {
            QMessageBox::warning(this, tr("Erreur réseau"), tr("Impossible de récupérer IP/MAC."));
            return;
        }

        QSqlQuery checkMac;
        checkMac.prepare("SELECT COUNT(*) FROM Raspberry WHERE mac = :mac");
        checkMac.bindValue(":mac", macAddress);
        if (!checkMac.exec() || !checkMac.next()) {
            QMessageBox::critical(this, tr("Erreur BDD"), checkMac.lastError().text());
            return;
        }

        if (checkMac.value(0).toInt() > 0) {
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

        QSqlQuery insert;
        insert.prepare("INSERT INTO Raspberry (ip, mac) VALUES (:ip, :mac)");
        insert.bindValue(":ip", ipAddress);
        insert.bindValue(":mac", macAddress);
        if (!insert.exec()) {
            QMessageBox::critical(this, tr("Erreur INSERT"), insert.lastError().text());
            return;
        }

        QByteArray data = macAddress.toUtf8();
        udpSocket.writeDatagram(data, QHostAddress::Broadcast, 5560);
        actionDone = true;
        return;
    }

    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) isCtrlPressed = false;
    if (event->key() == Qt::Key_F1) isF1Pressed = false;
    QMainWindow::keyReleaseEvent(event);
}

void MainWindow::receiveInfo() {
    // [... Code de receiveInfo inchangé ...]
}

void MainWindow::receivePath() {
    // [... Code de receivePath inchangé ...]
}

void MainWindow::receiveInter() {
    // [... Code de receiveInter inchangé ...]
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
    emit chronoMisAJour(temps);
    if (remainingTime <= QTime(0, 0, 30)) faireClignoterLabel();
    if (remainingTime == QTime(0, 0)) {
        chronoTimer->stop();
        stopClignotement();
        emit chronoFini();
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

// ✅ MÉTHODE AJOUTÉE
void MainWindow::sendCommandToProf(const QString& profIp, int port, const QString& command)
{
    if (command.isEmpty()) return;

    QByteArray datagram = command.toUtf8();
    QHostAddress addr(profIp);
    udpSocket.writeDatagram(datagram, addr, port);
    qDebug() << "[Command] vers" << profIp << ":" << command;
}
