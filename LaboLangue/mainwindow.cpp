#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);  // Supprime la barre de titre et les boutons
    //showFullScreen();
    connectToDatabase();

    // Création de la scène
    scene = new QGraphicsScene(0, 0, 631, 681, this);
    ui->PlanClasse->setScene(scene);

    ui->ParametrageSession->setVisible(false);
    ui->ParametrageEleve->setVisible(false);

    // Désactivation des boutons
    editStatusButton(ui->PlanButton, false);
    editStatusButton(ui->PresenceButton, false);
    editStatusButton(ui->EnregistrementButton, false);
    editStatusButton(ui->AppelButton, false);
    editStatusButton(ui->StatutButton, false);
    editStatusButton(ui->CreationButton, false);

    // Créer le layout principal pour le parametrage de session avec les éléments disposés
    QVBoxLayout *layoutParametrageSession = new QVBoxLayout();
    layoutParametrageSession->setContentsMargins(8, 8, 15, 8);
    layoutParametrageSession->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    // Ajout des sections dans le layoutParametrageSession
    addHorizontalLayout(layoutParametrageSession, {ui->NameLabel, ui->NameLineEdit, ui->loadSession});
    addHorizontalLayout(layoutParametrageSession, {ui->ChoixActLabel, ui->ChoixActivite});
    addHorizontalLayout(layoutParametrageSession, {ui->DureeLabel, ui->DureeActivite});
    addHorizontalLayout(layoutParametrageSession, {ui->ClasseLabel, ui->ChoixClasse});
    addHorizontalLayout(layoutParametrageSession, {ui->ParticipantsLabel, ui->selectAll, ui->selectManuel});
    addHorizontalLayout(layoutParametrageSession, {ui->SourceLabel, ui->NameSourceLabel, ui->SourceButton});
    addHorizontalLayout(layoutParametrageSession, {ui->ConsigneLabel, ui->ConsigneTextEdit});
    QHBoxLayout *hLayoutParametrageSession = new QHBoxLayout();
    hLayoutParametrageSession->addWidget(ui->errorLabel);
    layoutParametrageSession->addLayout(hLayoutParametrageSession);
    layoutParametrageSession->addSpacing(10);
    addHorizontalLayout(layoutParametrageSession, {ui->delButton, ui->echapButton, ui->validButton});
    // Appliquez le layout à ParametrageSession
    ui->ParametrageSession->setLayout(layoutParametrageSession);

    // Créer le layout principal pour la gestion audio des élèves et des groupes avec les éléments disposés
    QVBoxLayout *layoutParametrageEleve = new QVBoxLayout();
    layoutParametrageEleve->setContentsMargins(8, 8, 15, 8);
    layoutParametrageEleve->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    // Ajout des sections dans le layoutParametrageEleve
    addHorizontalLayout(layoutParametrageEleve, {ui->nomGroupeLabel, ui->nomEleveLineEdit, ui->Communication});
    addHorizontalLayout(layoutParametrageEleve, {ui->muteButton, ui->demuteButton});
    addHorizontalLayout(layoutParametrageEleve, {ui->desactiverSonButton, ui->activerSonButton});
    addHorizontalLayout(layoutParametrageEleve, {ui->creerGroupeButton, ui->annulerButton});
    addHorizontalLayout(layoutParametrageEleve, {ui->supprimerGroupeButton, ui->selectionGroupe});
    addHorizontalLayout(layoutParametrageEleve, {ui->alignerTableau, ui->TableauGroupe, ui->envoyerMessageTextEdit});
    addHorizontalLayout(layoutParametrageEleve, {ui->envoyerMessagePersonne, ui->envoyerMessageGroupe});
    layoutParametrageEleve->addSpacing(10);
    ui->envoyerMessageGroupe->setVisible(false);
    ui->envoyerMessagePersonne->setVisible(false);
    ui->envoyerMessageTextEdit->setVisible(false);
    ui->TableauGroupe->setVisible(false);
    ui->envoyerMessageTextEdit->setPlaceholderText("Ecrire un message...");
    // Appliquez le layout à ParametrageEleve
    ui->ParametrageEleve->setLayout(layoutParametrageEleve);


    // Créer le layout principal pour le parametrage de session avec les éléments disposés
    QVBoxLayout *layoutPageStatut = new QVBoxLayout();
    layoutPageStatut->setContentsMargins(8, 8, 15, 8);
    layoutPageStatut->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    // Ajout des sections dans le layoutPageStatut
    addHorizontalLayout(layoutPageStatut, {ui->alignerTableau_2, ui->StatutTableauGroupe});
    layoutPageStatut->addSpacing(10);
    // Appliquez le layout à PageStatut
    ui->PageStatut->setLayout(layoutPageStatut);
    ui->alignerTableau_2->setVisible(false);
    ui->PageStatut->setVisible(false);



    // Initialiser les ComboBoxes et charger les images depuis la base de données
    setupClassesComboBox();
    setupActivitiesComboBox();
    loadImagesFromDB();

    QPixmap clairPixmap("../img/clair.png");
    QPixmap sombrePixmap("../img/sombre.png");

    ui->modeSombreButton->setIcon(sombrePixmap);
    ui->modeSombreButton->setIconSize(QSize(45, 45));
    ui->modeClairButton->setIcon(clairPixmap);
    ui->modeClairButton->setIconSize(QSize(45, 45));

    ui->modeClairButton->setVisible(true);
    ui->modeSombreButton->setVisible(false);

    ui->ParametrageEleve->setStyleSheet("background-color: gray;");
    ui->PlanClasse->setStyleSheet("background-color: gray;");
    ui->ParametrageSession->setStyleSheet("background-color: gray;");

    ui->centralwidget->setStyleSheet("background-color: black;");
}

MainWindow::~MainWindow()
{
    ui->PlanClasse->setScene(nullptr); // Déconnecter la scène avant de la supprimer
    delete scene;
    delete ui;
}

// Ouverture page paramétrage Eleve
void MainWindow::toggleSettingEleve(iconEleveGroup *group, bool open)
{
    ui->Communication->setVisible(true);

    ui->PageStatut->setVisible(false);
    ui->ParametrageSession->setVisible(false);
    parametrageEleve = open;
    ui->ParametrageEleve->setVisible(open);

    if (open && group != nullptr)
    {
        ui->nomEleveLineEdit->setText(QString(group->getNom()));
    }
}


void MainWindow::setupActivitiesComboBox()
{
    QSqlQuery query("SELECT Nom FROM TypeActivite");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError();
        return;
    }

    while (query.next()) {
        QString nom = query.value(0).toString();

        ui->ChoixActivite->addItem(nom);
    }

    return;
}

void MainWindow::setNomEtudiantLineEdit(QString nom)
{
    ui->nomEleveLineEdit->setText(nom);
}

void MainWindow::setupClassesComboBox()
{
    QSqlQuery query;
    query.prepare("SELECT Nom FROM Classe");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError();
        return;
    }

    while (query.next()) {
        QString nom = query.value(0).toString();

        ui->ChoixClasse->addItem(nom);
    }

    return;
}



void MainWindow::editStatusButton(QPushButton *button, bool status)
{
    button->setEnabled(status);
    if(status == false)
    {
        button->setStyleSheet(
            "background-color: #cccccc; font: 9pt \"Segoe UI\"; color: #999999; "
            "border: 1px solid #999999; border-radius: 10px;"
            );
    }
    else
    {
        button->setStyleSheet("background-color: black;\nfont: 9pt \"Segoe UI\";\ncolor: white;\nborder: 1px solid white;\nborder-radius:10px;");
    }

}

void MainWindow::updateCheckItemsVisibility() {
    bool shouldShow = parametrageSession && (selectionParticipants || selectAllParticipants);

    for (auto *eleve : listeRasp) {
        if (eleve->getCheckItem()) {
            eleve->getCheckItem()->setVisible(shouldShow &&
                                              std::find(listeParticipant.begin(), listeParticipant.end(), eleve) != listeParticipant.end());
        }
    }
}


void MainWindow::addHorizontalLayout(QVBoxLayout *layout, std::initializer_list<QWidget*> widgets)
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    for (QWidget *w : widgets) {
        if (w) hLayout->addWidget(w);
    }
    layout->addLayout(hLayout);
    layout->addSpacing(15);
}

void MainWindow::majStatusQCM()
{
    while (udpSocketQCM->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress sender;
        quint16 senderPort;

        datagram.resize(udpSocketQCM->pendingDatagramSize());
        udpSocketQCM->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString ipSender = sender.toString();  // IP de l'expéditeur
        QString message = QString::fromUtf8(datagram);

        // 🔍 Chercher l'élève par IP
        for (unsigned int row = 0; row < listeParticipant.size(); ++row) {
            if (listeParticipant[row]->getIP() == ipSender) {
                // 🧠 Exemple : mettre à jour la colonne 3 avec le message reçu
                QTableWidgetItem* item = StatutTableauGroupe->item(row, 3);
                if (item) {
                    listeParticipant[row]->setNumQCM(message.toInt());
                    item->setText(message);
                    item->setTextAlignment(Qt::AlignCenter);
                }
                break;
            }
        }
    }
}

void MainWindow::resetSession()
{
    //Réinitialisation des IDs et des variables
    idTypeActivite = -1;
    idClasse = -1;
    idProf = -1;
    typeActivite = -1;

    //Réinitialisation des listes
    listeRasp.clear();
    listeParticipant.clear();
    listeEleveParticipant.clear();

    //Réinitialisation des variables de session
    runningSession = false;
    parametrageSession = false;
    selectionParticipants = false;
    selectAllParticipants = false;
    parametrageEleve = false;
    eleveActuellementParametre = nullptr;

    //Réinitialisation des chaînes de caractères
    source.clear();
    nomProf.clear();
    duree.clear();
    nomTypeActivite.clear();
    ui->errorLabel->clear();

    //Réinitialisation des éléments de l'interface graphique
    ui->NameLineEdit->clear();
    ui->ConsigneTextEdit->clear();
    ui->DureeActivite->setTime(QTime(0, 0, 0));
    ui->ChoixActivite->setCurrentIndex(0);
    ui->ChoixClasse->setCurrentIndex(0);
    ui->ParametrageSession->setVisible(false);

    //Réinitialisation des boutons
    editStatusButton(ui->PlanButton, false);
    editStatusButton(ui->PresenceButton, false);
    editStatusButton(ui->EnregistrementButton, false);
    editStatusButton(ui->AppelButton, false);
    editStatusButton(ui->StatutButton, false);
    editStatusButton(ui->selectAll, true);
    editStatusButton(ui->selectManuel, true);
    ui->selectManuel->setStyleSheet("background-color: gray;");
    ui->selectAll->setStyleSheet("background-color: gray;");

    ui->SessionButton->setText("Nouv. Session");
    ui->delButton->setText("Supprimer");

    //Réinitialisation de la scène graphique (si nécessaire)
    if (scene) {
        scene->clear();
        loadImagesFromDB();
    }

}

void MainWindow::changeNameTable(QTableWidgetItem* item)
{
    // Vérifier si la modification a eu lieu dans la colonne 0 (celle du nom)
    if (item->column() == 0) {
        QString nouveauNom = item->text();  // La nouvelle valeur de la cellule
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        if (nouveauNom.isEmpty()) {
            qWarning() << "Le nom ne peut pas être vide.";
            return;  // Si le nom est vide, on arrête la fonction
        }

        // Récupérer l'ID de l'élève
        int idParticipant = listeParticipant[item->row()]->getIDEleve(); // Identifiant du participant

        // Préparer la requête de mise à jour
        QSqlQuery query;
        query.prepare("UPDATE sessioneleve SET Nom = :nom WHERE Id_eleve = :id");
        query.bindValue(":nom", nouveauNom);
        query.bindValue(":id", idParticipant);

        // Exécuter la requête
        if (!query.exec()) {
            qDebug() << "Erreur de mise à jour dans la base de données : " << query.lastError();
            // Afficher un message d'erreur à l'utilisateur si nécessaire
        } else {
            qDebug() << "Mise à jour du nom du participant dans la base de données réussie.";
            // Afficher un message de confirmation si nécessaire

            for (iconEleveGroup* group : listeRasp) {
                if (group->getIDEleve() == idParticipant) {
                    // Mise à jour du textItem dans le groupe
                    group->setTextItem(nouveauNom);  // Met à jour le texte dans l'icône
                    group->setNom(nouveauNom);
                    break;  // Sortir de la boucle une fois le groupe trouvé
                }
            }
        }
    }
}


void MainWindow::changeNameGroup(iconEleveGroup *group, QString newName)
{
    // Préparer la requête de mise à jour
    QSqlQuery query;
    query.prepare("UPDATE sessioneleve SET Nom = :nom WHERE Id_eleve = :id");
    query.bindValue(":id", group->getID());
    query.bindValue(":nom", newName);

    // Exécuter la requête
    if (!query.exec()) {
        qDebug() << "Erreur de mise à jour dans la base de données : " << query.lastError();
        // Afficher un message d'erreur à l'utilisateur
    }
    group->setTextItem(newName);
    group->setNom(newName);
    loadInformationTable();
}

/**
 * Fonctions lié aux icons de raspberry (icons)
 */
void MainWindow::loadImagesFromDB()
{
    if (!connectToDatabase()) {
        qDebug() << "Erreur de connexion à la base de données.";
        return;
    }

    QSqlQuery query("SELECT IP, X, Y FROM Raspberry");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError();
        return;
    }

    // Vérifier si on a des résultats
    if (!query.first()) {
        qDebug() << "Aucun Raspberry trouvé dans la base de données.";
        return;
    }

    QPixmap personPixmap("../img/person.png");
    QPixmap checkPixmap("../img/check.png");
    QPixmap microPixmap("../img/micro.png");

    if (personPixmap.isNull() || checkPixmap.isNull() || microPixmap.isNull()) {
        qWarning("Une ou plusieurs images n'ont pas pu être chargées. Vérifiez les chemins.");
        return;
    }

    int column = 0;
    int row = 0;
    int spacing = 10;
    int maxPerRow = 7;

    int imageWidth = personPixmap.width();
    int imageHeight = personPixmap.height();

    int id = 1;
    do {
        QString ip = query.value(0).toString();
        int x = query.value(1).toInt();
        int y = query.value(2).toInt();

        // Vérification et position par défaut si nécessaire
        if (query.value(1).isNull() || query.value(2).isNull()) {
            x = column * (imageWidth + spacing);
            y = row * (imageHeight + spacing + 10);
        }

        // Création des éléments graphiques
        QGraphicsPixmapItem *imageItem = new QGraphicsPixmapItem(personPixmap);
        imageItem->setFlag(QGraphicsItem::ItemIsMovable);

        QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::number(id));
        textItem->setDefaultTextColor(Qt::black);
        textItem->setPos(18, personPixmap.height());

        // Création du groupe personnalisé
        iconEleveGroup *group = new iconEleveGroup(id, ip, textItem, this);
        group->addToGroup(imageItem);
        group->addToGroup(textItem);
        group->setFlag(QGraphicsItem::ItemIsMovable);

        // Création des icônes Check et Cross
        QGraphicsPixmapItem *checkItem = new QGraphicsPixmapItem(checkPixmap);
        checkItem->setPos(imageItem->boundingRect().right() - checkPixmap.width(), imageItem->boundingRect().top());
        checkItem->setVisible(false); // Caché par défaut

        QGraphicsPixmapItem *micro = new QGraphicsPixmapItem(microPixmap);
        micro->setPos(imageItem->boundingRect().left(), imageItem->boundingRect().top());
        micro->setVisible(false); // Caché par défaut

        // Ajout des icônes au groupe
        group->addToGroup(checkItem);
        group->addToGroup(micro);

        // Sauvegarde des icônes dans l'objet pour pouvoir les modifier après
        group->setCheckItem(checkItem);
        group->setMicro(micro);

        // Positionnement et ajout à la scène
        group->setPos(x, y);
        listeRasp.push_back(group);
        scene->addItem(group);

        // Connexion du signal double-clic
        connect(group, &iconEleveGroup::doubleClicked, this, &MainWindow::onImageGroupDoubleClicked);

        // Gestion du placement
        column++;
        if (column >= maxPerRow) {
            column = 0;
            row++;
        }
        id++;

    } while (query.next());

    ui->PlanClasse->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::showCheckIconOnGroup(iconEleveGroup *group)
{
    if (!group) return;

    group->getCheckItem()->setVisible(!group->getCheckItem()->isVisible());
}

void MainWindow::onImageGroupDoubleClicked() {}

/**
 * Fonction pour se connecter à la Base de donnée (BDD)
*/
bool MainWindow::connectToDatabase() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        return true; // La connexion existe déjà
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.89.42");
    db.setDatabaseName("LaboLangue");
    db.setPort(3306);
    db.setUserName("prof"); // Remplacez par votre nom d'utilisateur
    db.setPassword("okokok"); // Remplacez par votre mot de passe

    if (!db.open()) {
        qDebug() << "Impossible de se connecter à la base de données :" << db.lastError();
        return false;
    }
    return true;
}

/**
 * Fonction pour sauvegarder la session sur le partage SMB
 * @param isNewSession : true si nouvelle session, false si suppression
 */
void MainWindow::saveSessionData(bool isNewSession)
{
    if (nomProf.trimmed().isEmpty()) {
        qDebug() << "❌ Erreur : nomProf est vide.";
        return;
    }

    // Préparation des chemins
    QString sanitizedName = nomProf;
    sanitizedName.replace(" ", "_").remove(QRegularExpression("[^a-zA-Z0-9_-]"));

    QString hostName = QHostInfo::localHostName();
    QString networkPath = QString(R"(\\%1\Activites\)").arg(hostName);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm");
    sessionFolder = networkPath + sanitizedName + "_" + timestamp;
    qDebug() << sessionFolder;

    // Création du dossier de session
    QDir dir;
    if (!dir.exists(sessionFolder) && !dir.mkpath(sessionFolder)) {
        qDebug() << "❌ Erreur : Impossible de créer le dossier de session.";
        return;
    }

    // ---------- Écriture de `generalConfig.laboconfig` ----------
    QJsonObject generalConfig {
        {"nomProf", nomProf},
        {"idTypeActivite", idTypeActivite},
        {"idClasse", idClasse},
        {"fichier", sessionFolder}
    };

    QString generalConfigPath = networkPath + "generalConfig.laboconfig";
    QFile generalConfigFile(generalConfigPath);
    if (generalConfigFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        generalConfigFile.write(QJsonDocument(generalConfig).toJson(QJsonDocument::Indented));
        generalConfigFile.close();
    } else {
        qDebug() << "❌ Erreur écriture `generalConfig.laboconfig` :" << generalConfigFile.errorString();
    }

    // ---------- Écriture de `config.labo` ----------
    QJsonArray participantsArray;
    for (auto participant : listeParticipant)
        if (participant)
            participantsArray.append(participant->getID());

    QJsonObject sessionConfig {
        {"nomProf", nomProf},
        {"idTypeActivite", idTypeActivite},
        {"idClasse", idClasse},
        {"consigne", ui->ConsigneTextEdit->toPlainText()},
        {"participants", participantsArray}
    };

    QString configPath = sessionFolder + "/config.labo";
    QFile sessionConfigFile(configPath);
    if (sessionConfigFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        sessionConfigFile.write(QJsonDocument(sessionConfig).toJson(QJsonDocument::Indented));
        sessionConfigFile.close();
    } else {
        qDebug() << "❌ Erreur écriture `config.labo` :" << sessionConfigFile.errorString();
    }

    // ---------- Écriture de `bilan.txt` ----------
    QString bilanPath = sessionFolder + "/bilan.txt";
    QFile bilanFile(bilanPath);
    if (bilanFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&bilanFile);
        stream << "Session créée par " << nomProf << "\n"
               << "Classe : " << ui->ChoixClasse->itemText(idClasse - 1) << "\n"
               << "Date : " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "\n"
               << "Id Prof : " << idProf << "\n"
               << "Activité : " << nomTypeActivite << "\n"
               << "Source : " << source << "\n"
               << "Consigne : " << ui->ConsigneTextEdit->toPlainText() << "\n"
               << "Durée : " << duree << "\n"
               << "Participants : " << listeParticipant.size() << "\n";
        bilanFile.close();
    } else {
        qDebug() << "❌ Erreur écriture `bilan.txt` :" << bilanFile.errorString();
    }
}

/**
 * Fonctions lié aux boutons de l'IHM (Boutton)
 */
void MainWindow::on_SessionButton_clicked()
{
    ui->PageStatut->setVisible(false);
    ui->ParametrageEleve->setVisible(false);
    parametrageEleve = false;

    parametrageSession = true;
    ui->ParametrageSession->setVisible(!ui->ParametrageSession->isVisible());
    ui->PlanClasse->setVisible(true);

    if(listeParticipant.size() > 0) selectionParticipants = true;
    for(unsigned int i=0; i!=listeParticipant.size(); i++)
    {
        showCheckIconOnGroup(listeParticipant[i]);
    }

}

void MainWindow::on_delButton_clicked()
{
    if (runningSession){
        resetSession();
    }

    for (auto rasp : listeRasp) {
        if (rasp) rasp->getCheckItem()->setVisible(false);
    }
}

void MainWindow::on_PlanButton_clicked()
{
    ui->PlanClasse->setVisible(!ui->PlanClasse->isVisible());
}

void MainWindow::on_ChoixActivite_currentIndexChanged(int index)
{
    QString selectedActivity = ui->ChoixActivite->itemText(index);
    typeActivite = index;
}

void MainWindow::on_selectManuel_clicked()
{
    if(selectionParticipants && !selectAllParticipants)
    {
        selectionParticipants = false;
        ui->selectManuel->setStyleSheet("background-color: gray;");
    }
    else{
        selectionParticipants = true;
        ui->selectManuel->setStyleSheet("background-color: blue; color: white; font-weight: bold;");
        ui->selectAll->setStyleSheet("background-color: gray;");
    }
    selectAllParticipants = false;
}

void MainWindow::on_selectAll_clicked()
{
    // Vérification de la couleur du bouton pour désélectionner
    if (listeParticipant.size() == listeRasp.size() && !selectionParticipants) { // Si tout est déjà sélectionné, on désélectionne
        ui->selectAll->setStyleSheet("background-color: gray;");

        for (unsigned int i = 0; i < listeRasp.size(); i++) {
            listeRasp[i]->getCheckItem()->setVisible(false);  // Masquer les icônes
        }
        listeParticipant.clear();  // Réinitialiser la liste
    } else { // Sinon, on sélectionne tout
        ui->selectAll->setStyleSheet("background-color: blue; color: white; font-weight: bold;");
        if (listeParticipant.size() != listeRasp.size()){
            listeParticipant.clear(); // Assurer qu'il n'y a pas de doublons
            for (unsigned int i = 0; i < listeRasp.size(); i++) {
                if(!listeRasp[i]->getCheckItem()->isVisible()) showCheckIconOnGroup(listeRasp[i]);          //Si la rasp n'est pas selectionné
                listeParticipant.push_back(listeRasp[i]);                                                   //Dans tous les cas
            }
        }
    }

    if (selectionParticipants) {
        selectionParticipants = false;
        ui->selectManuel->setStyleSheet("background-color: gray;");
        ui->selectAll->setStyleSheet("background-color: blue; color: white; font-weight: bold;");
    }

    selectionParticipants = true;
    selectAllParticipants = true;
}

void MainWindow::on_SourceButton_clicked()
{
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation); // Récupère le dossier Documents

    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Sélectionner un fichier audio",
        documentsPath,  // Définit "Documents" comme dossier par défaut
        "Audio Files (*.mp3 *.wav *.ogg *.flac *.aac), Vidéos (*.mp4 *.avi *.mkv *.mov *.wmv)"        // Filtre uniquement les fichiers audio
        );
    if (fileName.isEmpty()) return;
    source = fileName;
    QFileInfo fileInfo(fileName);
    ui->NameSourceLabel->setText(fileInfo.fileName());
}

void MainWindow::on_validButton_clicked()
{
    ui->errorLabel->clear();

    // Vérification des champs obligatoires
    if (ui->NameLineEdit->text().isEmpty()) {
        ui->errorLabel->setText("Veuillez indiquer votre nom!");
    }
    if (ui->ChoixActivite->currentText().isEmpty()) {
        ui->errorLabel->setText("Veuillez indiquer une activité!");
    }
    if (ui->DureeActivite->time().isNull()) {
        ui->errorLabel->setText("Veuillez indiquer une durée!");
    }
    if (ui->ChoixClasse->currentText().isEmpty()) {
        ui->errorLabel->setText("Veuillez indiquer une classe!");
    }
    if (listeParticipant.empty()) {
        ui->errorLabel->setText("Veuillez indiquer des participants!");
    }
    if(ui->errorLabel->text() != nullptr) return;

    // Récupération des IDs de la base de données
    QSqlQuery query;
    query.prepare("SELECT Id_TypeActivite FROM TypeActivite WHERE Nom = :nom");
    query.bindValue(":nom", ui->ChoixActivite->currentText());
    idTypeActivite = query.exec() && query.next() ? query.value(0).toInt() : -1;

    query.prepare("SELECT Id_Classe FROM Classe WHERE Nom = :nom");
    query.bindValue(":nom", ui->ChoixClasse->currentText());
    idClasse = query.exec() && query.next() ? query.value(0).toInt() : -1;

    query.prepare("SELECT Id_Prof FROM Prof WHERE Nom = :nom");
    query.bindValue(":nom", ui->NameLineEdit->text());
    nomProf = ui->NameLineEdit->text();

    if (query.exec() && query.next()) {
        idProf = query.value(0).toInt();
    } else {
        // 🔹 Si le professeur n'existe pas, l'ajouter
        query.prepare("INSERT INTO SessionProf (Nom, Date_Session) VALUES (:nom, :date)");
        query.bindValue(":nom", ui->NameLineEdit->text());
        query.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        if (query.exec()) {
            idProf = query.lastInsertId().toInt();
        } else {
            qDebug() << "Erreur insertion Prof :" << query.lastError().text();
            return;
        }
    }

    // Vérification des IDs avant l'insertion de l'activité
    if (idTypeActivite == -1 || idClasse == -1 || idProf == -1) {
        qDebug() << "Erreur : Impossible de récupérer tous les identifiants nécessaires.";
        return;
    }

    duree = ui->DureeActivite->time().toString("HH:mm:ss");

    // Insérer l'activité
    query.prepare("INSERT INTO Activite (Source, Consigne, Duree_Activite, DateActivite, Id_TypeActivite, Id_Classe, Id_Prof) "
                  "VALUES (:source, :consigne, :duree, :date, :type, :classe, :prof)");
    query.bindValue(":source", source);
    query.bindValue(":consigne", ui->ConsigneTextEdit->toPlainText());
    query.bindValue(":duree", duree);
    query.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":type", idTypeActivite);
    query.bindValue(":classe", idClasse);
    query.bindValue(":prof", idProf);
    if (!query.exec()) {
        qDebug() << "Erreur insertion activité :" << query.lastError();
        return;
    }

    // Insérer les participants
    for (auto participant : listeParticipant) {
        int idRaspberry = participant->getID();
        query.prepare("INSERT INTO SessionEleve (Date_Session, Id_Raspberry, Id_Classe) VALUES (:date, :raspberry, :classe)");
        query.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":raspberry", idRaspberry);
        query.bindValue(":classe", idClasse);
        if (!query.exec()) {
            qDebug() << "Erreur insertion participant" << idRaspberry << ":" << query.lastError();
        }
        participant->getMicro()->setVisible(true);

        listeEleveParticipant.push_back(query.lastInsertId().toInt());
        participant->setIDELeve(query.lastInsertId().toInt());
    }

    prof = new Professor();

    unsigned int i = 1;
    for (auto *eleve : listeRasp) {
        // Si l'élément n'est PAS dans listeParticipant
        if (std::find(listeParticipant.begin(), listeParticipant.end(), eleve) == listeParticipant.end()) {
            eleve->setVisible(false); // ou eleve->hide(); selon ta classe
        }
        else
        {
            changeNameGroup(eleve, QString("Éleve " + QString::number(i++)));

            QMap<int, QString> activite;
            activite[1] = "QCM";
            activite[2] = "ecoute";
            activite[3] = "ecoute_co";
            activite[4] = "video";
            activite[5] = "video_co";
            activite[6] = "enregistrement";

            prof->sendCommandToStudent(eleve->getIP(), 5560, "nomProf:"+nomProf);
            prof->sendCommandToStudent(eleve->getIP(), 5558, ui->ConsigneTextEdit->toPlainText());
            prof->sendCommandToStudent(eleve->getIP(), 5561, activite.value(idTypeActivite));

        }
    }

    // Activation des boutons
    editStatusButton(ui->PlanButton, true);
    editStatusButton(ui->PresenceButton, true);
    editStatusButton(ui->EnregistrementButton, true);
    editStatusButton(ui->AppelButton, true);
    editStatusButton(ui->StatutButton, true);

    //Desactivatio, button participants
    editStatusButton(ui->selectAll, false);
    editStatusButton(ui->selectManuel, false);

    // Sauvegarde des fichiers
    saveSessionData(true);

    // Mettre à jour l'interface
    if(ui->ChoixActivite->currentText() == "QCM")
    {
        editStatusButton(ui->CreationButton, true);
        on_CreationButton_clicked();

        udpSocketQCM = new QUdpSocket(this);
        udpSocketQCM->bind(45454, QUdpSocket::ShareAddress);  // Choisis un port libre
        connect(udpSocketQCM, &QUdpSocket::readyRead, this, &MainWindow::majStatusQCM);
    }


    selectionParticipants = false;
    selectAllParticipants = false;
    parametrageSession = false;
    on_echapButton_clicked();
    ui->SessionButton->setText("Session \nen cours");
    ui->delButton->setText("Fin session");
    runningSession = true;

    if(!source.isEmpty())
    {
        QFileInfo fileInfo(source);

        QDir dir;
        if (!dir.exists(sessionFolder)) {
            dir.mkpath(sessionFolder); // Crée le dossier s'il n'existe pas
        }

        // Copier le fichier
        if (QFile::copy(source, sessionFolder)) {
            QMessageBox::critical(
                nullptr,
                "Fichier enregistré avec succès",
                "✅ Fichier bien enregistré \n"
                "Le fichier audio/vidéo à été enregistré dans " + sessionFolder
                );
        } else {
            QMessageBox::critical(
                nullptr,
                "Fichier n'as pas pu être enregistré",
                "❌ Aucun fichier n'a été enregistré\n"
                "Il vous sera impossible de récupérer le fichier après la fin de session\n\n"
                "Veuillez le mettre manuellement dans " + sessionFolder + "."
                );
        }
    }
}

void MainWindow::on_echapButton_clicked()
{
    on_delButton_clicked();
    ui->ParametrageSession->setVisible(false);
}

void MainWindow::on_loadSession_clicked()
{
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation); // Récupère le dossier Documents

    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Sélectionner un fichier labo",
        documentsPath,  // Définit "Documents" comme dossier par défaut
        "Fichiers LABO (*.labo)"        // Filtre uniquement les fichiers audio
        );
    source = fileName;
    QFileInfo fileInfo(fileName);
}

void MainWindow::on_CreationButton_clicked()
{
    QCM *qcmWindow = new QCM(this, this);
    if(!interfaceQCMOpen) qcmWindow->show();
    interfaceQCMOpen = true;
}

// Bouton de l'interface de ParametrageEleve
void MainWindow::on_muteButton_clicked()
{
    for(unsigned int i = 0; i < listeEditEleve.size(); i++){
        prof->muteStudent(listeEditEleve[i]->getIP());
    }
}

void MainWindow::on_demuteButton_clicked()
{
    for(unsigned int i = 0; i < listeEditEleve.size(); i++){
        prof->unmuteStudent(listeEditEleve[i]->getIP());
    }
}

void MainWindow::on_desactiverSonButton_clicked()
{
    for(unsigned int i = 0; i < listeEditEleve.size(); i++){
        prof->activerSonStudent(listeEditEleve[i]->getIP());
    }
}

void MainWindow::on_activerSonButton_clicked()
{
    for(unsigned int i = 0; i < listeEditEleve.size(); i++){
        prof->desactiverSonStudent(listeEditEleve[i]->getIP());
    }
}

void MainWindow::on_annulerButton_clicked()
{
    parametrageEleve = false;
    ui->ParametrageEleve->setVisible(false);
}

void MainWindow::loadInformationTable()
{
    // Crée une table de 12 lignes et 4 colonnes
    ui->TableauGroupe->setColumnCount(4);

    ui->TableauGroupe->setRowCount(listeRasp.size());
    TableauGroupe = ui->TableauGroupe;

    // Ajouter des en-têtes pour les colonnes
    TableauGroupe->setHorizontalHeaderLabels({"Nom", "Numéro de poste", "Adresse IP", "Ajoutez au groupe :"});
    TableauGroupe->setColumnWidth(1, 110);
    TableauGroupe->setColumnWidth(2, 130);
    TableauGroupe->setColumnWidth(3, 140);

    // Remplir les cellules avec des données
    for (unsigned int row = 0; row < listeParticipant.size(); ++row) {
        // Par exemple, on met des valeurs génériques comme "Donnée 1", "Donnée 2", etc.

        QTableWidgetItem *itemNom ;
        if(listeParticipant[row] == eleveActuellementParametre)
        {
            itemNom = new QTableWidgetItem(eleveActuellementParametre->getNom());
        }
        else itemNom = new QTableWidgetItem(listeParticipant[row]->getNom());
        itemNom->setTextAlignment(Qt::AlignCenter);
        TableauGroupe->setItem(row, 0, itemNom);


        QTableWidgetItem *itemID = new QTableWidgetItem(QString::number(listeParticipant[row]->getID()));
        itemID->setTextAlignment(Qt::AlignCenter);
        itemID->setFlags(itemID->flags() & ~Qt::ItemIsEditable);    // Désactiver l'édition de cette cellule
        TableauGroupe->setItem(row, 1, itemID);

        QTableWidgetItem *itemIP = new QTableWidgetItem(listeParticipant[row]->getIP());
        itemIP->setTextAlignment(Qt::AlignCenter);
        itemIP->setFlags(itemIP->flags() & ~Qt::ItemIsEditable);    // Désactiver l'édition de cette cellule
        TableauGroupe->setItem(row, 2, itemIP);

        QPushButton *itemBoutonAjouterGroupe = new QPushButton();
        itemBoutonAjouterGroupe->setText("Insérer au groupe");
        ui->TableauGroupe->setCellWidget(row, 3, itemBoutonAjouterGroupe);

    }
    connect(TableauGroupe, &QTableWidget::itemChanged, this, &MainWindow::changeNameTable);

    // Afficher le tableau

}

void MainWindow::on_creerGroupeButton_clicked()
{
    ui->envoyerMessageGroupe->setVisible(false);
    ui->envoyerMessagePersonne->setVisible(false);
    ui->envoyerMessageTextEdit->setVisible(false);
    ui->TableauGroupe->setVisible(true);
    qDebug() << "Actualisation du tableau";

    loadInformationTable();

    TableauGroupe->show();
}

void MainWindow::on_Communication_clicked()
{
    ui->envoyerMessageGroupe->setVisible(true);
    ui->envoyerMessagePersonne->setVisible(true);
    ui->envoyerMessageTextEdit->setVisible(true);
    ui->TableauGroupe->setVisible(false);
}

void MainWindow::on_nomEleveLineEdit_editingFinished()
{
    prof->sendCommandToStudent(eleveActuellementParametre->getIP(), 5560, "{\"nomEleve\" :\"" + ui->nomEleveLineEdit->text() + "\"}");
    changeNameGroup(eleveActuellementParametre, ui->nomEleveLineEdit->text());
}

void MainWindow::on_envoyerMessagePersonne_clicked()
{
    qDebug() << "Envoyer le message a :" << eleveActuellementParametre->getIP();
    //Code fonction
    qDebug() << "Le message à été envoyé";

    prof->sendCommandToStudent(eleveActuellementParametre->getIP(), 5559, ui->envoyerMessageTextEdit->toPlainText());

    QMessageBox::information(
        nullptr,
        "Message envoyé",
        "✔ Le message à bien été envoyé au poste séléctionné.\n"
    );
}

void MainWindow::on_envoyerMessageGroupe_clicked()
{
    qDebug() << "Envoyer le message au groupe de :" << eleveActuellementParametre->getIP();
    //Code fonction
    qDebug() << "Le message à été envoyé";



    QMessageBox::information(
        nullptr,
        "Message envoyé",
        "✔ Le message à bien été envoyé au groupe du poste séléctionné.\n"
    );
}


void MainWindow::on_modeClairButton_clicked()
{
    ui->ParametrageEleve->setStyleSheet("background-color: white;");
    ui->PlanClasse->setStyleSheet("background-color: white;");
    ui->ParametrageSession->setStyleSheet("background-color: white;");
    ui->PageStatut->setStyleSheet("background-color: white;");

    ui->centralwidget->setStyleSheet("background-color: gray;");

    ui->modeClairButton->setVisible(false);
    ui->modeSombreButton->setVisible(true);
}


void MainWindow::on_modeSombreButton_clicked()
{
    ui->PageStatut->setStyleSheet("background-color: rgb(160, 160, 160)");
    ui->ParametrageEleve->setStyleSheet("background-color: rgb(160, 160, 160)");
    ui->PlanClasse->setStyleSheet("background-color: rgb(160, 160, 160)");
    ui->ParametrageSession->setStyleSheet("background-color: rgb(160, 160, 160)");

    ui->centralwidget->setStyleSheet("background-color: black");

    ui->modeClairButton->setVisible(true);
    ui->modeSombreButton->setVisible(false);
}


void MainWindow::on_StatutButton_clicked()
{


    ui->ParametrageSession->setVisible(false);
    parametrageEleve = false;
    ui->ParametrageEleve->setVisible(false);
    ui->StatutTableauGroupe->setVisible(true);
    ui->PageStatut->setVisible(true);

    // Crée une table de 12 lignes et 4 colonnes
    ui->StatutTableauGroupe->setColumnCount(6);

    ui->StatutTableauGroupe->setRowCount(listeRasp.size());
    StatutTableauGroupe = ui->StatutTableauGroupe;

    // Ajouter des en-têtes pour les colonnes
    QStringList headers = {"Nom", "Numéro de poste", "Adresse IP", "Travail déposé", "Numéro de groupe", "Enregistrement"};

    if (ui->ChoixActivite->currentText() == "QCM") {
        headers << "QCM";  // Ajoute une colonne "QCM" si l'activité est un QCM
        StatutTableauGroupe->setColumnCount(7);  // 6 + 1 colonne pour QCM
    } else {
        StatutTableauGroupe->setColumnCount(6);
    }

    StatutTableauGroupe->setHorizontalHeaderLabels(headers);

    // Ajuste les largeurs des colonnes (modifie/ajoute selon besoin)
    StatutTableauGroupe->setColumnWidth(0, 150); // Nom
    StatutTableauGroupe->setColumnWidth(1, 100); // Numéro de poste
    StatutTableauGroupe->setColumnWidth(2, 120); // Adresse IP
    StatutTableauGroupe->setColumnWidth(3, 110); // Travail déposé
    StatutTableauGroupe->setColumnWidth(4, 130); // Numéro de groupe
    StatutTableauGroupe->setColumnWidth(5, 120); // Enregistrement

    if (ui->ChoixActivite->currentText() == "QCM") {
        StatutTableauGroupe->setColumnWidth(6, 80); // QCM
    }

    // Remplir les cellules avec des données
    for (unsigned int row = 0; row < listeParticipant.size(); ++row) {

        QTableWidgetItem *itemNom ;

        itemNom = new QTableWidgetItem(listeParticipant[row]->getNom());
        itemNom->setTextAlignment(Qt::AlignCenter);
        StatutTableauGroupe->setItem(row, 0, itemNom);

        QTableWidgetItem *itemID = new QTableWidgetItem(QString::number(listeParticipant[row]->getID()));
        itemID->setTextAlignment(Qt::AlignCenter);
        itemID->setFlags(itemID->flags() & ~Qt::ItemIsEditable);    // Désactiver l'édition de cette cellule
        StatutTableauGroupe->setItem(row, 1, itemID);

        QTableWidgetItem *itemIP = new QTableWidgetItem(listeParticipant[row]->getIP());
        itemIP->setTextAlignment(Qt::AlignCenter);
        itemIP->setFlags(itemIP->flags() & ~Qt::ItemIsEditable);    // Désactiver l'édition de cette cellule
        StatutTableauGroupe->setItem(row, 2, itemIP);

        QTableWidgetItem *itemTravailDepot = new QTableWidgetItem("❌");
        itemTravailDepot->setTextAlignment(Qt::AlignCenter);
        itemTravailDepot->setFlags(itemTravailDepot->flags() & ~Qt::ItemIsEditable);    // Désactiver l'édition de cette cellule
        StatutTableauGroupe->setItem(row, 3, itemTravailDepot);

        QPushButton *itemBoutonAjouterGroupe = new QPushButton();
        itemBoutonAjouterGroupe->setText("Ecouter");
        ui->StatutTableauGroupe->setCellWidget(row, 5, itemBoutonAjouterGroupe);

        if(ui->ChoixActivite->currentText() == "QCM")
        {
            QTableWidgetItem *statusQCM = new QTableWidgetItem(QString::number(listeParticipant[row]->getNumQCM()) + "/" + QString::number(qcm->getSize()));
            statusQCM->setTextAlignment(Qt::AlignCenter);
            statusQCM->setFlags(statusQCM->flags() & ~Qt::ItemIsEditable);    // Désactiver l'édition de cette cellule
            StatutTableauGroupe->setItem(row, 6, statusQCM);
        }
    }
    connect(StatutTableauGroupe, &QTableWidget::itemChanged, this, &MainWindow::changeNameTable);
    // Afficher le tableau
}


void MainWindow::on_cacheButton_clicked()
{
    ui->PageStatut->setStyleSheet("background-color: rgb(0, 255, 128)");
    ui->ParametrageEleve->setStyleSheet("background-color: rgb(0, 255, 128)");
    ui->PlanClasse->setStyleSheet("background-color: rgb(255, 204, 204)");
    ui->ParametrageSession->setStyleSheet("background-color: rgb(0, 255, 128)");

    ui->centralwidget->setStyleSheet("background-color: rgb(128,255,0)");

    ui->modeClairButton->setVisible(true);
    ui->modeSombreButton->setVisible(false);
}

