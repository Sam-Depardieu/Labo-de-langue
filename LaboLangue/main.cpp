#include "mainwindow.h"

#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QAudioInput>
#include <QAudioOutput>
#include <QUdpSocket>
#include <QIODevice>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QUrl>
#include <QApplication>
#include <QCoreApplication>
#include <QNetworkInterface>
#include <QDebug>
#include <QHostInfo>
#include <QProcess>

class VoiceChat : public QObject {
    Q_OBJECT
public:
    VoiceChat(const QHostAddress &peerAddress, quint16 peerPort, quint16 localPort, QObject *parent = nullptr)
        : QObject(parent), peerAddress(peerAddress), peerPort(peerPort) {
        // 📌 Définition des paramètres audio
        QAudioFormat format;
        format.setSampleRate(44100);
        format.setChannelCount(1);  // Mono pour économiser la bande passante
        format.setSampleFormat(QAudioFormat::Int16); // Format PCM 16 bits
        // 📌 Vérifier si le format est supporté
        QAudioDevice inputDevice = QMediaDevices::defaultAudioInput();
        QAudioDevice outputDevice = QMediaDevices::defaultAudioOutput();
        if (!inputDevice.isFormatSupported(format) || !outputDevice.isFormatSupported(format)) {
            qWarning() << "Format audio non supporté";
            return;
        }
        // 🎤 Configurer la source audio (microphone)
        audioSource = new QAudioSource(inputDevice, format, this);
        audioDeviceIn = audioSource->start();  // Démarrer la capture
        // 🔊 Configurer la sortie audio (haut-parleur)
        audioSink = new QAudioSink(outputDevice, format, this);
        audioDeviceOut = audioSink->start(); // Préparer la lecture
        // 📡 Initialiser le socket UDP
        udpSocket = new QUdpSocket(this);
        udpSocket->bind(QHostAddress::AnyIPv4, localPort); // Écoute sur un port local
        // 🔄 Connecter les signaux
        connect(audioDeviceIn, &QIODevice::readyRead, this, &VoiceChat::sendAudioData);
        connect(udpSocket, &QUdpSocket::readyRead, this, &VoiceChat::receiveAudioData);
    }
public slots:
    // Envoie l'audio
    void sendAudioData() {
        QByteArray data = audioDeviceIn->readAll();  // Lire les données du micro
        udpSocket->writeDatagram(data, peerAddress, peerPort);  // Envoyer via UDP
    }
    // Lecture de l'audio reçu
    void receiveAudioData() {
        while (udpSocket->hasPendingDatagrams()) {
            QByteArray buffer;
            buffer.resize(udpSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;
            udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
            audioDeviceOut->write(buffer);  // Jouer l'audio reçu en temps réel
        }
    }
private:
    QAudioSource *audioSource;
    QAudioSink *audioSink;
    QIODevice *audioDeviceIn;
    QIODevice *audioDeviceOut;
    QUdpSocket *udpSocket;
    QHostAddress peerAddress;
    quint16 peerPort;
};


void pingAndInsertAddress(const QString &address, QSqlDatabase &db)
{
    QProcess process;
    process.start("ping", QStringList() << "-n" << "1" << address); // Utilisez "-n" au lieu de "-c" sous Windows
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    if (output.contains("1 received") || output.contains("TTL=")) { // Vérifiez la réponse pour Linux/Windows
        QSqlQuery query(db);
        query.prepare("INSERT INTO Raspberry (Id_Raspberry, IP, Status) VALUES (NULL, :ip, :status)");
        query.bindValue(":ip", address);
        query.bindValue(":status", true); // Statut à true pour indiquer que l'adresse IP est active
        if (!query.exec()) {
            qDebug() << "Erreur d'insertion:" << query.lastError().text();
        } else {
            qDebug() << "Adresse IP active insérée:" << address;
        }

        query.prepare("INSERT INTO Placement (NumPoste, X, Y) VALUES (NULL, :ip, :status)");
        query.bindValue(":ip", address);
        query.bindValue(":status", true); // Statut à true pour indiquer que l'adresse IP est active
        if (!query.exec()) {
            qDebug() << "Erreur d'insertion:" << query.lastError().text();
        } else {
            qDebug() << "Adresse IP active insérée:" << address;
        }
    }
}

bool connectToDatabase()
{
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        return true; // La connexion existe déjà
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.64.36");
    db.setDatabaseName("LaboLangue");
    db.setUserName("prof"); // Remplacez par votre nom d'utilisateur
    db.setPassword("okokok"); // Remplacez par votre mot de passe

    if (!db.open()) {
        qDebug() << "Impossible de se connecter à la base de données :" << db.lastError();
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*QString baseNetwork = "192.168.64.";

    // Connexion à la base de données SQLite
    if (!connectToDatabase()) {
        return -1;
    }

    QSqlDatabase db = QSqlDatabase::database();

    // Ping et insertion des adresses IP actives
    for (int i = 1; i < 255; ++i) { // Commencer à 1 et aller jusqu'à 254
        QString currIp = QString("%1%2").arg(baseNetwork).arg(i);
        pingAndInsertAddress(currIp, db);
    }

    db.close();*/

    return a.exec();
}
