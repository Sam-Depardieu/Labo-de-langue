#include "gestionSession.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

// Constructeur
gestionSession::gestionSession(MainWindow *mainW, QSqlDatabase db, QObject *parent)
    : QObject(parent), mainWindow(mainW), m_db(db) {
    auto *ui = mainWindow->ui;

    // Créer le layout principal pour le parametrage de session avec les éléments disposés
    QVBoxLayout *layoutParametrageSession = new QVBoxLayout();
    layoutParametrageSession->setContentsMargins(8, 8, 15, 8);
    layoutParametrageSession->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    // Ajout des sections dans le layoutParametrageSession
    mainWindow->addHorizontalLayout(layoutParametrageSession, {ui->NomProfLabel, ui->NomProfLineEdit, ui->loadSession});
    mainWindow->addHorizontalLayout(layoutParametrageSession, {ui->ChoixActLabel, ui->ChoixActivite});
    mainWindow->addHorizontalLayout(layoutParametrageSession, {ui->DureeLabel, ui->DureeActivite});
    mainWindow->addHorizontalLayout(layoutParametrageSession, {ui->ClasseLabel, ui->ChoixClasse});
    mainWindow->addHorizontalLayout(layoutParametrageSession, {ui->ParticipantsLabel, ui->selectAll, ui->selectManuel});
    mainWindow->addHorizontalLayout(layoutParametrageSession, {ui->SourceLabel, ui->NameSourceLabel, ui->SourceButton});
    mainWindow->addHorizontalLayout(layoutParametrageSession, {ui->ConsigneLabel, ui->ConsigneTextEdit});
    QHBoxLayout *hLayoutParametrageSession = new QHBoxLayout();
    hLayoutParametrageSession->addWidget(ui->errorLabel);
    layoutParametrageSession->addLayout(hLayoutParametrageSession);
    layoutParametrageSession->addSpacing(10);
    mainWindow->addHorizontalLayout(layoutParametrageSession, {ui->delButton, ui->echapButton, ui->validButton});
    // Appliquez le layout à ParametrageSession
    ui->ParametrageSession->setLayout(layoutParametrageSession);

    ui->ParametrageSession->setVisible(false);
}


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

void gestionSession::reset()
{
    for(unsigned int i=0; i!=mainWindow->listeParticipant.size();i++) mainWindow->getProf()->sendCommandToStudent(mainWindow->listeParticipant[i]->getIP(), 5557, "END");
    // === Réinitialisation des IDs et variables de base ===
    mainWindow->setIdTypeActivite(-1);
    mainWindow->setIdClasse(-1);
    mainWindow->setIdProf(-1);

    // === Réinitialisation des listes d'élèves et groupes ===
    mainWindow->listeRasp.clear();
    mainWindow->listeParticipant.clear();
    mainWindow->listeEleveParticipant.clear();
    mainWindow->listeEditEleve.clear();
    mainWindow->listeGroup.clear();
    mainWindow->couleursGroup.clear();

    // === Réinitialisation des variables d'état ===
    mainWindow->runningSession = false;
    mainWindow->parametrageSession = false;
    mainWindow->selectionParticipants = false;
    mainWindow->selectAllParticipants = false;
    mainWindow->parametrageEleve = false;
    mainWindow->eleveActuellementParametre = nullptr;
    mainWindow->interfaceQCMOpen = false;

    // === Réinitialisation des chaînes de caractères ===
    mainWindow->getSource()->clear();
    mainWindow->getNomProf()->clear();
    mainWindow->getDuree()->clear();
    mainWindow->getNomTypeActivite()->clear();
    mainWindow->ui->errorLabel->clear();

    // === Réinitialisation de l'interface utilisateur ===
    mainWindow->ui->NomProfLineEdit->clear();
    mainWindow->ui->ConsigneTextEdit->clear();
    mainWindow->ui->DureeActivite->setTime(QTime(0, 0, 0));
    mainWindow->ui->ChoixActivite->setCurrentIndex(0);
    mainWindow->ui->ChoixClasse->setCurrentIndex(0);
    mainWindow->ui->ParametrageSession->setVisible(false);
    mainWindow->ui->cadenaCloseButton->setVisible(true);
    mainWindow->ui->cadenaOpenButton->setVisible(false);
    mainWindow->ui->chronoLabel->setVisible(false);
    mainWindow->ui->envoyerMessageTextEdit->clear();
    mainWindow->ui->TableauGroupe->setVisible(false);

    // === Réinitialisation des boutons ===
    mainWindow->editStatusButton(mainWindow->ui->PlanButton, false);
    mainWindow->editStatusButton(mainWindow->ui->PresenceButton, false);
    mainWindow->editStatusButton(mainWindow->ui->EnregistrementButton, false);
    mainWindow->editStatusButton(mainWindow->ui->AppelButton, false);
    mainWindow->editStatusButton(mainWindow->ui->StatutButton, false);
    mainWindow->editStatusButton(mainWindow->ui->selectAll, true);
    mainWindow->editStatusButton(mainWindow->ui->selectManuel, true);
    mainWindow->ui->selectManuel->setStyleSheet("background-color: gray;");
    mainWindow->ui->selectAll->setStyleSheet("background-color: gray;");

    mainWindow->ui->SessionButton->setText("Nouv. Session");
    mainWindow->ui->delButton->setText("Supprimer");

    // === Réinitialisation des tableaux s'ils existent ===
    if (mainWindow->TableauGroupe) mainWindow->TableauGroupe->clearContents();

    if (mainWindow->StatutTableauGroupe) mainWindow->StatutTableauGroupe->clearContents();

    // === Réinitialisation de la scène graphique ===
    if (mainWindow->scene) {
        mainWindow->scene->clear();
        mainWindow->loadImagesFromDB();  // Recharge les images depuis la base (avatars, etc.)
    }

    // === Nettoyage AudioCommunicator / réseau si actif ===
    if (mainWindow->udpSocketPATH) {
        mainWindow->udpSocketPATH->close();
        delete mainWindow->udpSocketPATH;
        mainWindow->udpSocketPATH = nullptr;
    }

    if (mainWindow->udpSocketQCM) {
        mainWindow->udpSocketQCM->close();
        delete mainWindow->udpSocketQCM;
        mainWindow->udpSocketQCM = nullptr;
    }
}
