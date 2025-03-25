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
    //editStatusButton(ui->CreationButton, false);

    // Créer le layout principal avec les éléments disposés
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(8, 8, 15, 8);
    layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    // Ajout des sections dans le layout
    addHorizontalLayout(layout, ui->NameLabel, ui->NameLineEdit, ui->loadSession);
    addHorizontalLayout(layout, ui->ChoixActLabel, ui->ChoixActivite);
    addHorizontalLayout(layout, ui->DureeLabel, ui->DureeActivite);
    addHorizontalLayout(layout, ui->ClasseLabel, ui->ChoixClasse);
    addHorizontalLayout(layout, ui->ParticipantsLabel, ui->selectAll, ui->selectManuel);
    addHorizontalLayout(layout, ui->SourceLabel, ui->NameSourceLabel, ui->SourceButton);
    addHorizontalLayout(layout, ui->ConsigneLabel, ui->ConsigneTextEdit);
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(ui->errorLabel);
    layout->addLayout(hLayout);
    layout->addSpacing(10);
    addButtonRow(layout, ui->delButton, ui->echapButton, ui->validButton);

    // Appliquez le layout à Parametrage1
    ui->ParametrageSession->setLayout(layout);

    // Initialiser les ComboBoxes et charger les images depuis la base de données
    setupClassesComboBox();
    setupActivitiesComboBox();
    loadImagesFromDB();
}

MainWindow::~MainWindow()
{
    ui->PlanClasse->setScene(nullptr); // Déconnecter la scène avant de la supprimer
    delete scene;
    delete ui;
}

void MainWindow::openSettingEleve(CustomGraphicsItemGroup *group)
{
    ui->ParametrageEleve->setVisible(true);
}

void MainWindow::closeSettingEleve(CustomGraphicsItemGroup *group)
{
    ui->ParametrageEleve->setVisible(false);
}

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
        CustomGraphicsItemGroup *group = new CustomGraphicsItemGroup(id, ip, this);
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
        connect(group, &CustomGraphicsItemGroup::doubleClicked, this, &MainWindow::onImageGroupDoubleClicked);

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

void MainWindow::showCheckIconOnGroup(CustomGraphicsItemGroup *group)
{
    if (!group) return;

    // Récupérer l'icône check du groupe
    QGraphicsPixmapItem *checkItem = group->getCheckItem();

    if (checkItem) {
        checkItem->setVisible(!checkItem->isVisible());
    } else {
        qDebug() << "L'icône check est introuvable pour ce groupe.";
    }
}

bool MainWindow::connectToDatabase() {
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

void MainWindow::on_SessionButton_clicked()
{
    parametrageSession = !parametrageSession;
    ui->ParametrageSession->setVisible(!ui->ParametrageSession->isVisible());
    ui->PlanClasse->setVisible(true);

    if(listeParticipant.size() > 0) selectionParticipants = true;
    for(unsigned int i=0; i!=listeParticipant.size(); i++)
    {
        showCheckIconOnGroup(listeParticipant[i]);
    }

}

void MainWindow::onImageGroupDoubleClicked() {}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        close();  // Ferme l'application quand on appuie sur Échap
    }
}

void MainWindow::on_PlanButton_clicked()
{
    ui->PlanClasse->setVisible(!ui->PlanClasse->isVisible());
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

void MainWindow::addHorizontalLayout(QVBoxLayout *layout, QWidget *widget1, QWidget *widget2)
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(widget1);
    hLayout->addWidget(widget2);
    layout->addLayout(hLayout);
    layout->addSpacing(15);
}

void MainWindow::addHorizontalLayout(QVBoxLayout *layout, QWidget *widget1, QWidget *widget2, QWidget *widget3)
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(widget1);
    hLayout->addWidget(widget2);
    hLayout->addWidget(widget3);
    layout->addLayout(hLayout);
    layout->addSpacing(15);
}

void MainWindow::addButtonRow(QVBoxLayout *layout, QWidget *button1, QWidget *button2, QWidget *button3)
{
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(button1);
    hLayout->addWidget(button2);
    hLayout->addWidget(button3);
    layout->addLayout(hLayout);
    layout->addSpacing(15);
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
        return;
    }
    if (ui->ChoixActivite->currentText().isEmpty()) {
        ui->errorLabel->setText("Veuillez indiquer une activité!");
        return;
    }
    if (ui->DureeActivite->time().isNull()) {
        ui->errorLabel->setText("Veuillez indiquer une durée!");
        return;
    }
    if (ui->ChoixClasse->currentText().isEmpty()) {
        ui->errorLabel->setText("Veuillez indiquer une classe!");
        return;
    }
    if (listeParticipant.empty()) {
        ui->errorLabel->setText("Veuillez indiquer des participants!");
        return;
    }

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
        int idRaspberry = participant->getId();
        query.prepare("INSERT INTO SessionEleve (Date_Session, Id_Raspberry, Id_Classe) VALUES (:date, :raspberry, :classe)");
        query.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":raspberry", idRaspberry);
        query.bindValue(":classe", idClasse);
        if (!query.exec()) {
            qDebug() << "Erreur insertion participant" << idRaspberry << ":" << query.lastError();
        }
        participant->getMicro()->setVisible(true);
    }

    // Activation des boutons
    editStatusButton(ui->PlanButton, true);
    editStatusButton(ui->PresenceButton, true);
    editStatusButton(ui->EnregistrementButton, true);
    editStatusButton(ui->AppelButton, true);
    editStatusButton(ui->StatutButton, true);

    // Sauvegarde des fichiers
    saveSessionData(true);

    // Mettre à jour l'interface
    on_echapButton_clicked();
    ui->SessionButton->setText("Session \nen cours");
    ui->delButton->setText("Fin session");
    runningSession = true;
}

void MainWindow::on_delButton_clicked()
{
    if (!runningSession){
        resetSession();
    }

    for (auto rasp : listeRasp) {
        if (rasp) rasp->getCheckItem()->setVisible(false);
    }
}

/**
 * Fonction pour sauvegarder la session sur le partage SMB
 * @param isNewSession : true si nouvelle session, false si suppression
 */
void MainWindow::saveSessionData(bool isNewSession)
{
    QString sanitizedName = nomProf;
    sanitizedName.replace(" ", "_").remove(QRegularExpression("[^a-zA-Z0-9_-]"));

    QString networkPath = "\\\\CIEL-T171-05\\Activites\\"; //Dossier du partage SMB
    sessionFolder = (nomProf != "" ? networkPath + sanitizedName + "_" + QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm"): "");
    qDebug() << sessionFolder;

    // Créer le dossier pour la session
    QDir dir;
    if (!dir.exists(sessionFolder) && !dir.mkpath(sessionFolder)) {
        qDebug() << "❌ Erreur : Impossible de créer le dossier de la session sur le partage SMB.";
        return;
    }

    // FICHIER 1 : `generalConfig.laboconfig` (DANS LE DOSSIER PRINCIPAL DU PARTAGE)
    QString generalConfigPath = networkPath + "/generalConfig.laboconfig";
    QJsonObject generalConfig;
    generalConfig["nomProf"] = nomProf;
    generalConfig["idTypeActivite"] = idTypeActivite;
    generalConfig["idClasse"] = idClasse;
    generalConfig["fichier"] = sessionFolder;  // 🔹 Stocke l'emplacement du dossier de session

    QJsonDocument generalConfigDoc(generalConfig);
    QFile generalConfigFile(generalConfigPath);
    if (generalConfigFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        generalConfigFile.write(generalConfigDoc.toJson(QJsonDocument::Indented));
        generalConfigFile.close();
    } else {
        qDebug() << "❌ Erreur lors de l'écriture de `generalConfig.laboconfig` :" << generalConfigFile.errorString();
    }

    // FICHIER 2 : `config.labo` (DANS LE DOSSIER DE SESSION)
    QString configPath = sessionFolder + "/config.labo";
    QJsonObject sessionConfig;
    sessionConfig["nomProf"] = nomProf;
    sessionConfig["idTypeActivite"] = idTypeActivite;
    sessionConfig["idClasse"] = idClasse;
    sessionConfig["consigne"] = ui->ConsigneTextEdit->toPlainText();

    QJsonArray participantsArray;
    for (auto participant : listeParticipant) {
        if (participant) participantsArray.append(participant->getId());
    }
    sessionConfig["participants"] = participantsArray;

    QJsonDocument sessionConfigDoc(sessionConfig);
    QFile sessionConfigFile(configPath);
    if (sessionConfigFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        sessionConfigFile.write(sessionConfigDoc.toJson(QJsonDocument::Indented));
        sessionConfigFile.close();
    } else {
        qDebug() << "❌ Erreur lors de l'écriture de `config.labo` :" << sessionConfigFile.errorString();
    }

    // FICHIER 3 : `bilan.txt` (DANS LE DOSSIER DE SESSION)
    QString bilanPath = sessionFolder + "/bilan.txt";
    QFile bilanFile(bilanPath);
    if (bilanFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&bilanFile);
        stream << "Session créée par " << nomProf << "\n"
               << "Classe : " << ui->ChoixClasse->itemText(idClasse - 1) << "\n"
               << "Date : " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "\n"
               << "Id Prof: " << idProf << "\n"
               << "Activité : " << nomTypeActivite << "\n"
               << "Source : " << source << "\n"
               << "Consigne : " << ui->ConsigneTextEdit->toPlainText() << "\n"
               << "Durée : " << duree << "\n"
               << "Participants : " << listeParticipant.size() << "\n";
        bilanFile.close();
    } else {
        qDebug() << "❌ Erreur lors de l'écriture de `bilan.txt` :" << bilanFile.errorString();
    }
}


void MainWindow::on_echapButton_clicked()
{
    on_delButton_clicked();
    ui->ParametrageSession->setVisible(false);
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

    //Réinitialisation des chaînes de caractères
    source.clear();
    nomProf.clear();
    duree.clear();
    nomTypeActivite.clear();

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
    qcmWindow->show();
}

