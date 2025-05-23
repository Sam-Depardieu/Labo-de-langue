#include "gestionSession.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

// Constructeur
gestionSession::gestionSession(QSqlDatabase db, QObject *parent)
    : QObject(parent), m_db(db) {}


QStringList gestionSession::getActivites() {
    QStringList activites;
    QSqlQuery query(database);
    if (!query.exec("SELECT Nom FROM TypeActivite")) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError();
        return activites;
    }
    while (query.next()) {
        activites << query.value(0).toString();
    }
    return activites;
}

QStringList gestionSession::getClasses() {
    QStringList classes;
    QSqlQuery query(database);
    if (!query.exec("SELECT Nom FROM Classe")) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError();
        return classes;
    }
    while (query.next()) {
        classes << query.value(0).toString();
    }
    return classes;
}

bool gestionSession::validerEtEnregistrerSession(const QString &nomProf, const QString &nomActivite, const QString &nomClasse,
    const QTime &dureeActivite, const QString &consigne, const QString &source, std::vector<iconEleveGroup*> &participants, std::vector<int> &idsParticipants,
    int &idProf, bool sessionExistante)
{
    QSqlQuery query(m_db);

    // Récupération des IDs
    int idTypeActivite = -1;
    int idClasse = -1;

    query.prepare("SELECT Id_TypeActivite FROM TypeActivite WHERE Nom = :nom");
    query.bindValue(":nom", nomActivite);
    if (query.exec() && query.next()) {
        idTypeActivite = query.value(0).toInt();
    }

    query.prepare("SELECT Id_Classe FROM Classe WHERE Nom = :nom");
    query.bindValue(":nom", nomClasse);
    if (query.exec() && query.next()) {
        idClasse = query.value(0).toInt();
    }

    query.prepare("SELECT Id_Prof FROM Prof WHERE Nom = :nom");
    query.bindValue(":nom", nomProf);
    if (query.exec() && query.next()) {
        idProf = query.value(0).toInt();
    } else {
        // Créer le prof
        query.prepare("INSERT INTO SessionProf (Nom, Date_Session) VALUES (:nom, :date)");
        query.bindValue(":nom", nomProf);
        query.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        if (query.exec()) {
            idProf = query.lastInsertId().toInt();
        } else {
            qDebug() << "Erreur insertion Prof :" << query.lastError().text();
            return false;
        }
    }

    if (idTypeActivite == -1 || idClasse == -1 || idProf == -1) {
        qDebug() << "Erreur : IDs introuvables.";
        return false;
    }

    // Insérer l'activité
    QString dureeStr = dureeActivite.toString("mm:ss");
    query.prepare("INSERT INTO Activite (Source, Consigne, Duree_Activite, DateActivite, Id_TypeActivite, Id_Classe, Id_Prof) "
                  "VALUES (:source, :consigne, :duree, :date, :type, :classe, :prof)");
    query.bindValue(":source", source);
    query.bindValue(":consigne", consigne);
    query.bindValue(":duree", dureeStr);
    query.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":type", idTypeActivite);
    query.bindValue(":classe", idClasse);
    query.bindValue(":prof", idProf);
    if (!query.exec()) {
        qDebug() << "Erreur insertion activité :" << query.lastError();
        return false;
    }

    // Insérer les participants
    for (iconEleveGroup *participant : participants) {
        int idRaspberry = participant->getID();
        query.prepare("INSERT INTO SessionEleve (Date_Session, Id_Raspberry, Id_Classe) VALUES (:date, :raspberry, :classe)");
        query.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":raspberry", idRaspberry);
        query.bindValue(":classe", idClasse);
        if (!query.exec()) {
            qDebug() << "Erreur insertion participant" << idRaspberry << ":" << query.lastError();
            continue;
        }

        int idEleve = query.lastInsertId().toInt();
        idsParticipants.push_back(idEleve);
        participant->setIDELeve(idEleve);
        participant->getCheckItem()->setVisible(false);
        participant->getMicroActiver()->setVisible(true);
        participant->getCasqueActiver()->setVisible(true);
    }
    return true;
}
