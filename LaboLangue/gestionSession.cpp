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
    mainWindow->editStatusButton(mainWindow->ui->SourceButton, false);
}


QStringList gestionSession::getActivites() {
    QStringList activites;
    QSqlQuery query(database);
    if (!query.exec("SELECT Nom FROM TypeActivite ORDER BY Id_TypeActivite ASC")) {
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
    mainWindow->ui->NomProfLineEdit->setEnabled(false);
    return true;
}

void gestionSession::loadSession() {
    choixSession choix(mainWindow);
    if (choix.exec() != QDialog::Accepted) {
        return;
    }

    QFile file(mainWindow->getSource());  // récupère la source depuis MainWindow

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "❌ Impossible d'ouvrir le fichier : " << mainWindow->getSource();
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "❌ Erreur de parsing JSON :" << parseError.errorString();
        return;
    }

    if (!jsonDoc.isObject()) {
        qWarning() << "❌ Le JSON n’est pas un objet valide.";
        return;
    }

    QJsonObject obj = jsonDoc.object();

    QString nomProf = obj["nomProf"].toString();
    mainWindow->getNomProf()->operator=(nomProf);

    int idTypeActivite = obj["idTypeActivite"].toInt();
    int idClasse = obj["idClasse"].toInt();
    QString consigne = obj["consigne"].toString();

    mainWindow->setIdTypeActivite(idTypeActivite);
    mainWindow->setIdClasse(idClasse);
    mainWindow->ui->NomProfLineEdit->setText(nomProf);
    mainWindow->ui->ChoixActivite->setCurrentIndex(idTypeActivite);
    mainWindow->ui->ChoixClasse->setCurrentIndex(idClasse);
    mainWindow->ui->ConsigneTextEdit->setText(consigne);

    QJsonArray participants = obj["participants"].toArray();
    for (const QJsonValue &val : participants) {
        int id = val.toInt();

        for (iconEleveGroup* group : mainWindow->listeRasp) {
            if (group->getID() == id) {
                if (!group->getCheckItem()->isVisible()) {
                    mainWindow->showCheckIconOnGroup(group);
                }
                mainWindow->listeParticipant.push_back(group);
                break;
            }
        }
    }
}

void gestionSession::continuerCreationSession(bool sessionExistante)
{
    unsigned int i = 1;
    auto ui = mainWindow->ui;

    mainWindow->editStatusButtonHeader(ui->PresenceButton, true);
    mainWindow->editStatusButtonHeader(ui->EnregistrementButton, true);
    mainWindow->editStatusButtonHeader(ui->AppelButton, true);
    mainWindow->editStatusButtonHeader(ui->StatutButton, true);
    mainWindow->editStatusButtonHeader(ui->selectAll, false);
    mainWindow->editStatusButtonHeader(ui->selectManuel, false);

    mainWindow->selectionParticipants = false;
    mainWindow->selectAllParticipants = false;
    mainWindow->parametrageSession = false;
    ui->ParametrageSession->setVisible(false);

    if (!mainWindow->runningSession) {
        ui->SessionButton->setText("Session \nen cours");
        ui->delButton->setText("Fin session");
    }

    mainWindow->runningSession = true;

    QString sessionSave = "\\\\CIEL-T171-05\\Activites\\" + mainWindow->getSessionFolder() + "\\";

    if (!mainWindow->getSource().isEmpty()) {
        QFileInfo fileInfo(mainWindow->getSource());
        QDir dir;
        if (!dir.exists(sessionSave)) dir.mkpath(sessionSave);

        QString finalName = mainWindow->getNewName().isEmpty() ? fileInfo.fileName() : mainWindow->getNewName();
        QString destPath = sessionSave + finalName;

        if (QFile::copy(mainWindow->getSource(), destPath)) {
            QMessageBox::critical(nullptr, "Fichier enregistré avec succès",
                                  "✅ Fichier bien enregistré \nLe fichier audio/vidéo a été enregistré dans " + destPath);
        } else {
            QMessageBox::critical(nullptr, "Fichier non enregistré",
                                  "❌ Aucun fichier n'a été enregistré\n"
                                  "Veuillez le mettre manuellement dans " + destPath + ".");
        }
    }

    QFile(sessionSave).close();
    mainWindow->remainingTime = ui->DureeActivite->time();

    mainWindow->clignotementEtat = false;
    mainWindow->clignotementTimer->stop();
    ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: white; border: 2px solid white; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");

    if (mainWindow->remainingTime != QTime(0, 0)) {
        ui->chronoLabel->setVisible(true);
        ui->enleveTemps->setVisible(true);
        ui->ajouterTemps->setVisible(true);
        ui->tempsChronoLineEdit->setVisible(true);
        ui->chronoLabel->setText(mainWindow->remainingTime.toString("mm:ss"));
        mainWindow->chronoTimer->start(1000);
    }

    for (auto *eleve : mainWindow->listeRasp) {
        if (std::find(mainWindow->listeParticipant.begin(), mainWindow->listeParticipant.end(), eleve) == mainWindow->listeParticipant.end()) {
            eleve->setVisible(false);
        } else {
            QString nomAuto = QString("Élève %1").arg(i++);
            mainWindow->updateEleveNom(eleve, nomAuto);
            QFileInfo fileInfo(mainWindow->getSource());
            QString finalName = mainWindow->getNewName().isEmpty() ? fileInfo.fileName() : mainWindow->getNewName();
            mainWindow->getProf()->sendCommandToStudent(eleve->getIP(), 5558, QString("nomFichier,"+mainWindow->getNewName()));
            mainWindow->getProf()->sendCommandToStudent(eleve->getIP(), 5558, QString("chrono,%1").arg(*mainWindow->getDuree()));
            mainWindow->getProf()->sendCommandToStudent(eleve->getIP(), 5561, QString(mainWindow->getSessionFolder()));

            //qDebug() << mainWindow->getIpProf();
            //mainWindow->getProf()->sendCommandToStudent(eleve->getIP(), 5558, "ipProf:"+QString(mainWindow->getIpProf()));
        }
    }
    QMap<int, QString> activite {
        {0, "QCM"},
        {1, "ecoute"},
        {2, "ecoute_co"},
        {3, "video"},
        {4, "video_co"},
        {5, "enregistrement"}
    };

    for (auto *eleve : mainWindow->listeParticipant) {
        mainWindow->getProf()->sendCommandToStudent(eleve->getIP(), 5560, activite[mainWindow->getIdTypeActivite()]);
    }
}

void gestionSession::on_SourceButton_clicked() {
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    QString filePath  = QFileDialog::getOpenFileName(
        nullptr,
        "Sélectionner un fichier source",
        documentsPath,
        (mainWindow->getNomTypeActivite()->contains("Ecoute") ? "Audio Files (*.mp3 *.wav *.ogg *.flac *.aac)" : "Vidéos (*.mp4 *.avi *.mkv *.mov *.wmv)")
        );

    if (filePath.isEmpty()) return;

    QFileInfo fileInfo(filePath);
    QString extension = fileInfo.completeSuffix();

    // Demander un nouveau nom à l'utilisateur
    bool ok;
    QString nouveauNom = QInputDialog::getText(
        nullptr,
        "Nom du fichier",
        "Entrez un nom pour le fichier sélectionné (sans extension) :",
        QLineEdit::Normal,
        fileInfo.baseName(),
        &ok
        );

    if (!ok || nouveauNom.trimmed().isEmpty()) return;

    // Génère un nouveau chemin temporaire avec le nouveau nom
    QString nouveauNomComplet = nouveauNom + "." + extension;
    mainWindow->setNewNameFolder(nouveauNomComplet);
    mainWindow->setSource(filePath);

    mainWindow->ui->NameSourceLabel->setText(nouveauNomComplet);
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
    mainWindow->resetSources();
    mainWindow->resetSessionFolder();
    mainWindow->resetName();
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
    mainWindow->ui->enleveTemps->setVisible(false);
    mainWindow->ui->ajouterTemps->setVisible(false);
    mainWindow->ui->tempsChronoLineEdit->setVisible(false);
    mainWindow->ui->envoyerMessageTextEdit->clear();
    mainWindow->ui->TableauGroupe->setVisible(false);
    mainWindow->ui->NameSourceLabel->clear();
    mainWindow->ui->NomProfLineEdit->setEnabled(true);

    // === Réinitialisation des boutons ===
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
