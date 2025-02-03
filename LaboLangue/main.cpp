#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QNetworkInterface>
#include <QDebug>
#include <QHostInfo>
#include <QProcess>

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
