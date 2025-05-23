#include "mainwindow.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
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
    addHorizontalLayout(layoutParametrageSession, {ui->NomProfLabel, ui->NomProfLineEdit, ui->loadSession});
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
    addHorizontalLayout(layoutParametrageEleve, {ui->microSonButton, ui->casqueSonButton});
    addHorizontalLayout(layoutParametrageEleve, {ui->creerGroupeButton, ui->annulerButton});
    addHorizontalLayout(layoutParametrageEleve, {ui->AppelerButton, ui->redemarrerButton});
    addHorizontalLayout(layoutParametrageEleve, {ui->nomCreationGroupeLabel, ui->nomGroupeLineEdit});
    addHorizontalLayout(layoutParametrageEleve, {ui->alignerTableau, ui->TableauGroupe, ui->envoyerMessageTextEdit});
    addHorizontalLayout(layoutParametrageEleve, {ui->envoyerMessagePersonne, ui->envoyerMessageGroupe});
    layoutParametrageEleve->addSpacing(10);   
    // Changement des couleurs des boutons de la page
    ui->casqueSonButton->setStyleSheet("background-color: rgb(255, 0, 0)");
    ui->microSonButton->setStyleSheet("background-color: rgb(255, 0, 0)");
    ui->Communication->setStyleSheet("background-color: gray;");
    ui->creerGroupeButton->setStyleSheet("background-color: gray;");
    ui->redemarrerButton->setStyleSheet("background-color: orange;");
    ui->AppelerButton->setStyleSheet("background-color: #28a745;");
    ui->annulerButton->setStyleSheet("background-color: gray");
    // Cacher les boutons de la page
    ui->nomCreationGroupeLabel->setVisible(false);
    ui->nomGroupeLineEdit->setVisible(false);
    ui->envoyerMessageGroupe->setVisible(false);
    ui->envoyerMessagePersonne->setVisible(false);
    ui->envoyerMessageTextEdit->setVisible(false);
    ui->TableauGroupe->setVisible(false);
    ui->chronoLabel->setVisible(false);
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

    QPixmap clairPixmap(":/img/clair.png");
    QPixmap sombrePixmap(":/img/sombre.png");
    QPixmap cadenasOpen(":/img/cadenasOpen.png");
    QPixmap cadenasClose(":/img/cadenasClose.png");

    ui->cadenaCloseButton->setIcon(cadenasClose);
    ui->cadenaCloseButton->setIconSize(QSize(45, 45));
    ui->cadenaOpenButton->setIcon(cadenasOpen);
    ui->cadenaOpenButton->setIconSize(QSize(45, 45));
    ui->cadenaOpenButton->setVisible(false);

    ui->modeSombreButton->setIcon(sombrePixmap);
    ui->modeSombreButton->setIconSize(QSize(45, 45));
    ui->modeClairButton->setIcon(clairPixmap);
    ui->modeClairButton->setIconSize(QSize(45, 45));

    ui->modeClairButton->setVisible(true);
    ui->modeSombreButton->setVisible(false);

    ui->PageStatut->setStyleSheet("background-color: rgb(160, 160, 160)");
    ui->ParametrageEleve->setStyleSheet("background-color: rgb(160, 160, 160)");
    ui->PlanClasse->setStyleSheet("background-color: rgb(160, 160, 160)");
    ui->ParametrageSession->setStyleSheet("background-color: rgb(160, 160, 160)");

    ui->centralwidget->setStyleSheet("background-color: black;");

    chronoTimer = new QTimer(this);
    connect(chronoTimer, &QTimer::timeout, this, &MainWindow::updateChronoLabel);
    clignotementTimer = new QTimer(this);
    connect(clignotementTimer, &QTimer::timeout, this, &MainWindow::faireClignoterLabel);
}

void MainWindow::faireClignoterLabel()
{
    clignotementEtat = !clignotementEtat;
    if (clignotementEtat)
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: red; border: 2px solid red; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
    else
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: white; border: 2px solid white; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
}

void MainWindow::updateChronoLabel()
{
    remainingTime = remainingTime.addSecs(-1);

    ui->chronoLabel->setText(remainingTime.toString("mm:ss"));

    if (remainingTime.minute() == 0 && remainingTime.second() < 31) {
        if (!clignotementTimer->isActive())
            clignotementTimer->start(500); // clignote toutes les 500 ms
    }

    if (remainingTime == QTime(0, 0)) {
        chronoTimer->stop();
        ui->chronoLabel->setText("00:00");
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: red; border: 2px solid red; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
        QMessageBox::information(this, "Fin de l'activité", "Pensez à mettre fin à l'activité en cours !");
    }
}


MainWindow::~MainWindow()
{
    ui->PlanClasse->setScene(nullptr); // Déconnecter la scène avant de la supprimer
    delete scene;
    delete ui;
}

// Ouverture page paramétrage Eleve
void MainWindow::toggleSettingEleve(iconEleveGroup *group, bool open){
    ui->Communication->setVisible(true);
    ui->PageStatut->setVisible(false);
    ui->ParametrageSession->setVisible(false);
    parametrageEleve = open;
    ui->ParametrageEleve->setVisible(open);
    if (open && group != nullptr){
        ui->nomEleveLineEdit->setText(QString(group->getNom()));
        changerStatusCasque(eleveActuellementParametre->getStatusCasque());
        changerStatusMicro(eleveActuellementParametre->getStatusMicro());
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
    for(unsigned int i=0; i!=listeParticipant.size();i++) prof->sendCommandToStudent(listeParticipant[i]->getIP(), 5557, "END");
    // === Réinitialisation des IDs et variables de base ===
    idTypeActivite = -1;
    idClasse = -1;
    idProf = -1;

    // === Réinitialisation des listes d'élèves et groupes ===
    listeRasp.clear();
    listeParticipant.clear();
    listeEleveParticipant.clear();
    listeEditEleve.clear();
    listeGroup.clear();
    couleursGroup.clear();

    // === Réinitialisation des variables d'état ===
    runningSession = false;
    parametrageSession = false;
    selectionParticipants = false;
    selectAllParticipants = false;
    parametrageEleve = false;
    eleveActuellementParametre = nullptr;
    interfaceQCMOpen = false;

    // === Réinitialisation des chaînes de caractères ===
    source.clear();
    nomProf.clear();
    duree.clear();
    nomTypeActivite.clear();
    ui->errorLabel->clear();

    // === Réinitialisation de l'interface utilisateur ===
    ui->NomProfLineEdit->clear();
    ui->ConsigneTextEdit->clear();
    ui->DureeActivite->setTime(QTime(0, 0, 0));
    ui->ChoixActivite->setCurrentIndex(0);
    ui->ChoixClasse->setCurrentIndex(0);
    ui->ParametrageSession->setVisible(false);
    ui->cadenaCloseButton->setVisible(true);
    ui->cadenaOpenButton->setVisible(false);
    ui->chronoLabel->setVisible(false);
    ui->envoyerMessageTextEdit->clear();
    ui->TableauGroupe->setVisible(false);

    // === Réinitialisation des boutons ===
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

    // === Réinitialisation des tableaux s'ils existent ===
    if (TableauGroupe) TableauGroupe->clearContents();

    if (StatutTableauGroupe) StatutTableauGroupe->clearContents();

    // === Réinitialisation de la scène graphique ===
    if (scene) {
        scene->clear();
        loadImagesFromDB();  // Recharge les images depuis la base (avatars, etc.)
    }

    // === Nettoyage AudioCommunicator / réseau si actif ===
    if (udpSocketPATH) {
        udpSocketPATH->close();
        delete udpSocketPATH;
        udpSocketPATH = nullptr;
    }

    if (udpSocketQCM) {
        udpSocketQCM->close();
        delete udpSocketQCM;
        udpSocketQCM = nullptr;
    }
}


void MainWindow::updateEleveNom(iconEleveGroup* eleve, const QString& newName) {
    // 1. Met à jour l'objet élève
    eleve->setTextItem(newName);
    eleve->setNom(newName);

    // 2. Met à jour la base de données
    updateNomDansBDD(eleve->getIDEleve(), newName);

    // 3. Debug
    qDebug() << "Nom mis à jour pour le participant :" << newName;
}

void MainWindow::updateNomDansBDD(int idEleve, const QString& nouveauNom) {
    QSqlQuery query;
    query.prepare("UPDATE SessionEleve SET nom = :nom WHERE Id_Eleve = :id");
    query.bindValue(":nom", nouveauNom);
    query.bindValue(":id", idEleve);

    if (!query.exec()) {
        qWarning() << "Échec de la mise à jour du nom dans la BDD :" << query.lastError().text();
    }
}

bool MainWindow::errorBdd(QSqlQuery &query)
{
    if (!query.exec()) {
        qDebug() << "[❌ SQL ERROR]";
        qDebug() << "    ➤ Requête : " << query.lastQuery();
        qDebug() << "    ➤ Erreur  : " << query.lastError().text();
        return false;
    }
    return true;
}


/**
 * Fonctions lié aux icons de raspberry (icons)
 */
void MainWindow::loadImagesFromDB()
{
    if (!connectToDatabase()) {
        qDebug() << "❌ Erreur de connexion à la base de données.";
        return;
    }

    QSqlQuery query("SELECT IP, X, Y, Id_Raspberry FROM Raspberry");

    if (!errorBdd(query)) return;

    if (!query.first()) {
        qDebug() << "Aucun Raspberry trouvé dans la base de données.";
        return;
    }

    // Charger les images
    QPixmap personPixmap(":/img/person.png");
    QPixmap checkPixmap(":/img/check.png");
    QPixmap microActiverPixmap(":/img/micro.png");
    QPixmap microDesactiverPixmap(":/img/mute.png");
    QPixmap casqueActiverPixmap(":/img/earGreen.png");
    QPixmap casqueDesactiverPixmap(":/img/earRed.png");
    QPixmap leveLaMainPixmap(":/img/remettre.png");

    if (personPixmap.isNull() || checkPixmap.isNull() || microActiverPixmap.isNull()) {
        qWarning("❌ Une ou plusieurs images n'ont pas pu être chargées. Vérifiez les chemins.");
        return;
    }

    int column = 0;
    int row = 0;
    const int spacing = 10;
    const int maxPerRow = 7;
    const int imageWidth = personPixmap.width();
    const int imageHeight = personPixmap.height();

    int id = 1;

    do {
        QString ip = query.value(0).toString();
        int x = query.value(1).isNull() ? column * (imageWidth + spacing) : query.value(1).toInt();
        int y = query.value(2).isNull() ? row * (imageHeight + spacing + 10) : query.value(2).toInt();
        id = query.value(3).toInt();

        // Créer l'élément élève
        QGraphicsPixmapItem *imageItem = new QGraphicsPixmapItem(personPixmap);
        imageItem->setFlag(QGraphicsItem::ItemIsMovable);

        QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::number(id));
        textItem->setDefaultTextColor(Qt::black);
        textItem->setPos(18, personPixmap.height());

        iconEleveGroup *group = new iconEleveGroup(id, ip, textItem, this);
        group->addToGroup(imageItem);
        group->addToGroup(textItem);
        group->setFlag(QGraphicsItem::ItemIsMovable);

        // Ajouter les icônes
        auto makeIcon = [&](const QPixmap& pix, int dx, int dy) -> QGraphicsPixmapItem* {
            auto *item = new QGraphicsPixmapItem(pix);
            item->setPos(imageItem->boundingRect().left() + dx, imageItem->boundingRect().top() + dy);
            item->setVisible(false);
            group->addToGroup(item);
            return item;
        };

        QGraphicsPixmapItem* checkItem           = makeIcon(checkPixmap, 0, 0);
        QGraphicsPixmapItem* microActiver        = makeIcon(microActiverPixmap, -7, 0);
        QGraphicsPixmapItem* microDesactiver     = makeIcon(microDesactiverPixmap, -7, 0);
        QGraphicsPixmapItem* casqueActiver       = makeIcon(casqueActiverPixmap, 42, 0);
        QGraphicsPixmapItem* casqueDesactiver    = makeIcon(casqueDesactiverPixmap, 42, 0);
        QGraphicsPixmapItem* leveLaMain          = makeIcon(leveLaMainPixmap, 19, -10);

        group->setCheckItem(checkItem);
        group->setMicroActiver(microActiver);
        group->setMicroDesactiver(microDesactiver);
        group->setCasqueActiver(casqueActiver);
        group->setCasqueDesactiver(casqueDesactiver);
        group->setLeveLaMain(leveLaMain);

        // === Ajout du rond d'état (pastille) ===
        QGraphicsEllipseItem* groupEtat = new QGraphicsEllipseItem(0, 0, 15, 15); // taille de la pastille
        groupEtat->setBrush(Qt::gray);
        groupEtat->setPen(Qt::NoPen);
        groupEtat->setVisible(false);

        // Positionner à droite de l'image, centré verticalement
        QRectF imageRect = imageItem->boundingRect();
        qreal pastilleW = 15;
        groupEtat->setPos(
            -pastilleW + 50, // 5 pixels à gauche de l'image
            (imageRect.height() - pastilleW) / 2 // centré verticalement
            );


        group->addToGroup(groupEtat);
        group->setgroupColor(groupEtat);

        // Positionner et ajouter à la scène
        group->setX(x);
        group->setY(y);
        group->setPos(x, y);
        listeRasp.push_back(group);
        scene->addItem(group);

        connect(group, &iconEleveGroup::doubleClicked, this, &MainWindow::onImageGroupDoubleClicked);

        column++;
        if (column >= maxPerRow) {
            column = 0;
            row++;
        }
        id++;

    } while (query.next());

    ui->PlanClasse->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}


void MainWindow::mettreAJourAudioPourGroupe(const QString& groupe)
{
    if (!listeGroup.contains(groupe)) return;

    std::vector<iconEleveGroup*>& membres = listeGroup[groupe];

    for (iconEleveGroup* membre : membres) {
        QStringList autresIPs;
        for (iconEleveGroup* autre : membres) {
            if (membre != autre && !autre->getIP().isEmpty()) {
                autresIPs << autre->getIP();
            }
        }

        QJsonObject payload;
        payload["groupAudio"] = QJsonArray::fromStringList(autresIPs);
        QJsonDocument doc(payload);
        QString message = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));

        prof->sendCommandToStudent(membre->getIP(), 5559, message);
        qDebug() << "🔁 Groupe " << groupe << " → envoyé à " << membre->getNom() << ":" << autresIPs;
    }
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
    db.setHostName("localhost");
    db.setDatabaseName("LaboLangue");
    db.setPort(3306);
    db.setUserName("prof"); // Remplacez par votre nom d'utilisateur
    db.setPassword("okokok"); // Remplacez par votre mot de passe
    db.setConnectOptions("UNIX_SOCKET=/opt/lampp/var/mysql/mysql.sock");        //Pour dev avec Base sous linux

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
    QString networkPath = QString(R"(\\%1\Activites\)").arg("CIEL-T171-05");
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
        {"Durée", duree},
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

void MainWindow::on_loadSession_clicked()
{

    choixSession choix(this);
    if (choix.exec() != QDialog::Accepted) {
        return;  // L'utilisateur a fermé sans valider, on arrête
    }

    loadSession();
}

void MainWindow::loadSession(){

    QFile file(source);  // `source` contient le chemin sélectionné par QFileDialog

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

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
    idTypeActivite = obj["idTypeActivite"].toInt();
    idClasse = obj["idClasse"].toInt();
    QString consigne = obj["consigne"].toString();

    ui->NomProfLineEdit->setText(nomProf);
    ui->ChoixActivite->setCurrentIndex(idTypeActivite);
    ui->ChoixClasse->setCurrentIndex(idClasse);
    ui->ConsigneTextEdit->setText(consigne);

    QJsonArray participants = obj["participants"].toArray();
    QList<int> listeParticipants;

    for (const QJsonValue &val : participants) {
        int id = val.toInt();

        for (iconEleveGroup* group : listeRasp) {
            if (group->getID() == id) {
                if (!group->getCheckItem()->isVisible()) {
                    showCheckIconOnGroup(group);  // Affiche l’icône
                }
                listeParticipant.push_back(group);  // Ajoute à la sélection
                break;
            }
        }
    }
}

void MainWindow::afficherEtatEleves()
{
    // Cacher toutes les pages
    ui->PageStatut->setVisible(false);
    ui->ParametrageEleve->setVisible(false);
    ui->ParametrageSession->setVisible(false);

    // Réinitialiser les états
    parametrageEleve = false;
    parametrageSession = false;
    selectionParticipants = false;

    // Afficher le plan
    ui->PlanClasse->setVisible(true);

    // Remettre les icônes selon le statut de chaque élève
    for (iconEleveGroup* eleve : listeRasp)
    {
        if (eleve->getCheckItem())
            eleve->getCheckItem()->setVisible(false);

        bool microActif = eleve->getStatusMicro();   // Tu dois avoir ces méthodes dans iconEleveGroup
        bool casqueActif = eleve->getStatusCasque();

        if(runningSession)
        {
            eleve->getMicroActiver()->setVisible(microActif);
            eleve->getMicroDesactiver()->setVisible(!microActif);
            eleve->getCasqueActiver()->setVisible(casqueActif);
            eleve->getCasqueDesactiver()->setVisible(!casqueActif);
        }
    }
}

void MainWindow::mettreAJourEtatsAudioEleves()
{
    for (iconEleveGroup* eleve : listeRasp)
    {
        bool microActif = eleve->getStatusMicro();
        bool casqueActif = eleve->getStatusCasque();

        if (eleve->getMicroActiver()) eleve->getMicroActiver()->setVisible(microActif);
        if (eleve->getMicroDesactiver()) eleve->getMicroDesactiver()->setVisible(!microActif);
        if (eleve->getCasqueActiver()) eleve->getCasqueActiver()->setVisible(casqueActif);
        if (eleve->getCasqueDesactiver()) eleve->getCasqueDesactiver()->setVisible(!casqueActif);
    }
}



void MainWindow::on_SessionButton_clicked()
{
    bool show = !ui->ParametrageSession->isVisible();

    if (show) {
        // Affichage du paramétrage session
        afficherEtatEleves(); // Cache tout proprement avant
        ui->ParametrageSession->setVisible(true);
        parametrageSession = true;

        if (!listeParticipant.empty())
            selectionParticipants = true;

        for (iconEleveGroup* eleve : listeRasp) {
            if (std::find(listeParticipant.begin(), listeParticipant.end(), eleve) != listeParticipant.end()) {
                showCheckIconOnGroup(eleve); // Affiche l’icône de check
            }
            eleve->getCasqueActiver()->setVisible(false);
            eleve->getCasqueDesactiver()->setVisible(false);
            eleve->getMicroDesactiver()->setVisible(false);
            eleve->getMicroActiver()->setVisible(false);
        }

    } else {
        // Fermeture du paramétrage session → retour à l'état normal
        afficherEtatEleves();
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
    idTypeActivite = index;
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
        "Sélectionner un fichier source",
        documentsPath,  // Définit "Documents" comme dossier par défaut
        "Audio Files (*.mp3 *.wav *.ogg *.flac *.aac);;Vidéos (*.mp4 *.avi *.mkv *.mov *.wmv)"        // Filtre uniquement les fichiers audio
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
    if (ui->NomProfLineEdit->text().isEmpty()) {
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
    if (!ui->errorLabel->text().isEmpty()) return;

    // Récupération des IDs de la base de données
    QSqlQuery query;
    query.prepare("SELECT Id_TypeActivite FROM TypeActivite WHERE Nom = :nom");
    query.bindValue(":nom", ui->ChoixActivite->currentText());
    idTypeActivite = query.exec() && query.next() ? query.value(0).toInt() : -1;

    query.prepare("SELECT Id_Classe FROM Classe WHERE Nom = :nom");
    query.bindValue(":nom", ui->ChoixClasse->currentText());
    idClasse = query.exec() && query.next() ? query.value(0).toInt() : -1;

    query.prepare("SELECT Id_Prof FROM Prof WHERE Nom = :nom");
    query.bindValue(":nom", ui->NomProfLineEdit->text());
    nomProf = ui->NomProfLineEdit->text();

    if (query.exec() && query.next()) {
        idProf = query.value(0).toInt();
    } else {
        // 🔹 Ajouter le prof s'il n'existe pas
        query.prepare("INSERT INTO SessionProf (Nom, Date_Session) VALUES (:nom, :date)");
        query.bindValue(":nom", ui->NomProfLineEdit->text());
        query.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        if (query.exec()) {
            idProf = query.lastInsertId().toInt();
        } else {
            qDebug() << "Erreur insertion Prof :" << query.lastError().text();
            return;
        }
    }

    if (idTypeActivite == -1 || idClasse == -1 || idProf == -1) {
        qDebug() << "Erreur : Impossible de récupérer tous les identifiants nécessaires.";
        return;
    }

    duree = ui->DureeActivite->time().toString("mm:ss");

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
        int idEleve = query.lastInsertId().toInt();
        listeEleveParticipant.push_back(idEleve);
        participant->setIDELeve(idEleve);
        participant->getCheckItem()->setVisible(false);
        participant->getMicroActiver()->setVisible(true);
        participant->getCasqueActiver()->setVisible(true);
    }

    prof = new Professeur(this);

    saveSessionData(!runningSession);

    // Interface : lancement spécifique pour QCM
    if (ui->ChoixActivite->currentText() == "QCM") {
        editStatusButton(ui->CreationButton, true);
        on_CreationButton_clicked();

        udpSocketQCM = new QUdpSocket(this);
        udpSocketQCM->bind(45454, QUdpSocket::ShareAddress);
        connect(udpSocketQCM, &QUdpSocket::readyRead, this, &MainWindow::majStatusQCM);

        QCM *qcmWindow = new QCM(this, this);

        if (!interfaceQCMOpen) {
            qcmWindow->show();
            interfaceQCMOpen = true;
        }
        // On attend la fermeture du QCM
        return;
    }


    continuerCreationSession();
}

void MainWindow::continuerCreationSession()
{

    unsigned int i = 1;
    for (auto *eleve : listeRasp) {
        if (std::find(listeParticipant.begin(), listeParticipant.end(), eleve) == listeParticipant.end()) {
            eleve->setVisible(false);
        } else {
            QString nomAuto = QString("Élève %1").arg(i++);
            updateEleveNom(eleve, nomAuto);

            QMap<int, QString> activite;
            activite[1] = "QCM";
            activite[2] = "ecoute";
            activite[3] = "ecoute_co";
            activite[4] = "video";
            activite[5] = "video_co";
            activite[6] = "enregistrement";

            if(duree != nullptr || duree != "00:00") prof->sendCommandToStudent(eleve->getIP(), 5558, QString("chrono,%1").arg(duree));
            prof->sendCommandToStudent(eleve->getIP(), 5561, QString(sessionFolder));
            prof->sendCommandToStudent(eleve->getIP(), 5560, activite[idTypeActivite]);
        }
    }

    editStatusButton(ui->PlanButton, true);
    editStatusButton(ui->PresenceButton, true);
    editStatusButton(ui->EnregistrementButton, true);
    editStatusButton(ui->AppelButton, true);
    editStatusButton(ui->StatutButton, true);
    editStatusButton(ui->selectAll, false);
    editStatusButton(ui->selectManuel, false);

    selectionParticipants = false;
    selectAllParticipants = false;
    parametrageSession = false;
    on_echapButton_clicked();

    if (!runningSession) {
        ui->SessionButton->setText("Session \nen cours");
        ui->delButton->setText("Fin session");
    }
    runningSession = true;

    QString sessionSave = sessionFolder + "\\";

    if (!source.isEmpty()) {
        QFileInfo fileInfo(source);
        QDir dir;
        if (!dir.exists(sessionSave)) dir.mkpath(sessionSave);
        QString destPath = sessionSave + fileInfo.fileName();

        if (QFile::copy(source, destPath)) {
            QMessageBox::critical(nullptr, "Fichier enregistré avec succès",
                                  "✅ Fichier bien enregistré \nLe fichier audio/vidéo a été enregistré dans " + destPath);
        } else {
            QMessageBox::critical(nullptr, "Fichier non enregistré",
                                  "❌ Aucun fichier n'a été enregistré\n"
                                  "Veuillez le mettre manuellement dans " + destPath + ".");
        }

    }
    QFile(sessionSave).close();

    remainingTime = ui->DureeActivite->time();

    clignotementEtat = false;
    clignotementTimer->stop();
    ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: white; border: 2px solid white; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");

    if(remainingTime != QTime(0, 0))
    {
        ui->chronoLabel->setVisible(true);
        ui->chronoLabel->setText(remainingTime.toString("mm:ss"));
        chronoTimer->start(1000); // met à jour toutes les secondes
    }
}

void MainWindow::on_echapButton_clicked()
{
    ui->ParametrageSession->setVisible(false);
}

void MainWindow::on_CreationButton_clicked()
{
    QCM *qcmWindow = new QCM(this, this);
    if(!interfaceQCMOpen) qcmWindow->show();
    interfaceQCMOpen = true;
}

// Bouton de l'interface de ParametrageEleve


void MainWindow::on_casqueSonButton_clicked() {
    bool isCurrentlyOn = eleveActuellementParametre->getStatusCasque();
    bool newStatus = !isCurrentlyOn;

    if (!newStatus) {
        prof->desactiverSonStudent(eleveActuellementParametre->getIP());
    } else {
        prof->activerSonStudent(eleveActuellementParametre->getIP());
    }

    changerStatusCasque(newStatus);
}

void MainWindow::on_microSonButton_clicked() {
    bool isCurrentlyOn = eleveActuellementParametre->getStatusMicro();
    bool newStatus = !isCurrentlyOn;

    if (!newStatus) {
        prof->muteStudent(eleveActuellementParametre->getIP());
    } else {
        prof->unmuteStudent(eleveActuellementParametre->getIP());
    }

    changerStatusMicro(newStatus);
}

void MainWindow::changerStatusMicro(bool statusMicro) {
    ui->microSonButton->setText(statusMicro ? "Couper le micro" : "Activer le micro");
    eleveActuellementParametre->getMicroActiver()->setVisible(statusMicro);
    eleveActuellementParametre->getMicroDesactiver()->setVisible(!statusMicro);
    ui->microSonButton->setStyleSheet(statusMicro
                                          ? "background-color: rgb(255, 0, 0);"
                                          : "background-color: #28a745;");
    eleveActuellementParametre->setStatusMicro(statusMicro); // On applique tel quel
}

void MainWindow::changerStatusCasque(bool statusCasque) {
    ui->casqueSonButton->setText(statusCasque ? "Couper le son" : "Activer le son");
    eleveActuellementParametre->getCasqueActiver()->setVisible(statusCasque);
    eleveActuellementParametre->getCasqueDesactiver()->setVisible(!statusCasque);
    ui->casqueSonButton->setStyleSheet(statusCasque
                                           ? "background-color: rgb(255, 0, 0);"
                                           : "background-color: #28a745;");
    eleveActuellementParametre->setStatusCasque(statusCasque); // On applique tel quel
}


void MainWindow::on_redemarrerButton_clicked()
{
    prof->sendCommandToStudent(eleveActuellementParametre->getIP(), 5557, "RESTART");
    qDebug() << "ip:" << eleveActuellementParametre->getIP() << ":RESTART";
}

void MainWindow::on_annulerButton_clicked()
{
    parametrageEleve = false;
    ui->ParametrageEleve->setVisible(false);
}

void MainWindow::changeNameTable(QTableWidgetItem* item) {
    if (item->column() != 0) return; // Ne gérer que la colonne "Nom"

    unsigned int row = item->row();
    QString nouveauNom = item->text();

    if (row >= 0 && row < listeParticipant.size()) {
        iconEleveGroup* eleve = listeParticipant[row];
        updateEleveNom(eleve, nouveauNom); // MAJ interface + BDD
    }
}


void MainWindow::loadInformationTable()
{
    // Crée une table de 12 lignes et 4 colonnes
    ui->TableauGroupe->setColumnCount(5);

    ui->TableauGroupe->setRowCount(listeRasp.size());
    TableauGroupe = ui->TableauGroupe;

    // Ajouter des en-têtes pour les colonnes
    TableauGroupe->setHorizontalHeaderLabels({"Nom", "Numéro de poste", "Ajoutez au groupe", "Nom du groupe", "Adresse IP"});
    TableauGroupe->setColumnWidth(0, 110); // Nom
    TableauGroupe->setColumnWidth(1, 100); // Numéro de poste
    TableauGroupe->setColumnWidth(2, 130); // Ajoutez au groupe
    TableauGroupe->setColumnWidth(4, 120); // Nom du groupe
    TableauGroupe->setColumnWidth(5, 80); // Adresse IP

    // Remplir les cellules avec des données
    for (unsigned int row = 0; row < listeParticipant.size(); ++row) {

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

        if(listeParticipant[row]->getNomGroupe() == "")
        {
            QPushButton *itemBoutonAjouterGroupe = new QPushButton();
            itemBoutonAjouterGroupe->setText("Insérer au groupe");
            itemBoutonAjouterGroupe->setStyleSheet("background-color: #28a745");
            ui->TableauGroupe->setCellWidget(row, 2, itemBoutonAjouterGroupe);
            connect(itemBoutonAjouterGroupe, &QPushButton::clicked, this, [this, row]() {
                MainWindow::onClicked_itemBoutonAjouterGroupe(listeParticipant[row]);
            });
        }
        else{
            QPushButton *itemBoutonSupprimerGroupe = new QPushButton();
            itemBoutonSupprimerGroupe->setText("Supprimer du groupe");
            itemBoutonSupprimerGroupe->setStyleSheet("background-color: rgb(255, 0, 0)");
            ui->TableauGroupe->setCellWidget(row, 2, itemBoutonSupprimerGroupe);
            connect(itemBoutonSupprimerGroupe, &QPushButton::clicked, this, [this, row]() {
                MainWindow::onClicked_itemBoutonSupprimerGroupe(listeParticipant[row]);
            });
        }
        QTableWidgetItem *nomGroupe = new QTableWidgetItem(listeParticipant[row]->getNomGroupe());
        nomGroupe->setTextAlignment(Qt::AlignCenter);
        nomGroupe->setFlags(nomGroupe->flags() & ~Qt::ItemIsEditable);    // Désactiver l'édition de cette cellule
        TableauGroupe->setItem(row, 3, nomGroupe);

        QTableWidgetItem *itemIP = new QTableWidgetItem(listeParticipant[row]->getIP());
        itemIP->setTextAlignment(Qt::AlignCenter);
        itemIP->setFlags(itemIP->flags() & ~Qt::ItemIsEditable);    // Désactiver l'édition de cette cellule
        TableauGroupe->setItem(row, 4, itemIP);
    }
    connect(TableauGroupe, &QTableWidget::itemChanged, this, &MainWindow::changeNameTable);
    // Afficher le tableau
    ui->TableauGroupe->setVisible(true);
}

void MainWindow::on_creerGroupeButton_clicked()
{
    if (TableauGroupe != nullptr) {
        qDebug() << "Nettoyage du tableau de groupe existant...";
        TableauGroupe->clearContents(); // vide les cellules sans supprimer le widget
        TableauGroupe->setRowCount(0);  // remet à zéro le nombre de lignes
        // Ne surtout pas faire `delete TableauGroupe;` c'est un truc QT en ui donc impossible
    }

    // Masquer les éléments liés à l'envoi de messages
    ui->envoyerMessageGroupe->setVisible(false);
    ui->envoyerMessagePersonne->setVisible(false);
    ui->envoyerMessageTextEdit->setVisible(false);

    // Afficher les éléments nécessaires pour la création de groupe
    ui->nomCreationGroupeLabel->setVisible(true);
    ui->nomGroupeLineEdit->setVisible(true);

    qDebug() << "Actualisation du tableau de groupe...";
    loadInformationTable();
}


void MainWindow::on_Communication_clicked()
{
    ui->envoyerMessageGroupe->setVisible(true);
    ui->envoyerMessagePersonne->setVisible(true);
    ui->envoyerMessageTextEdit->setVisible(true);
    ui->TableauGroupe->setVisible(false);
    ui->nomCreationGroupeLabel->setVisible(false);
    ui->nomGroupeLineEdit->setVisible(false);
}

void MainWindow::on_nomEleveLineEdit_editingFinished()
{
    prof->sendCommandToStudent(eleveActuellementParametre->getIP(), 5560, "{\"nomEleve\" :\"" + ui->nomEleveLineEdit->text() + "\"}");
    qDebug() << "nomEleve line esdit";
    updateEleveNom(eleveActuellementParametre, ui->nomEleveLineEdit->text());
}

void MainWindow::on_envoyerMessagePersonne_clicked()
{
    if(ui->envoyerMessageTextEdit->toPlainText() == ""){
        qDebug() << "Le message est vide !";
        QMessageBox::critical(
            nullptr,
            "Le message n'a pas pu être envoyé",
            "Le message est vide est n'a donc pas pu être envoyé.\n"
            );
        return;
    }

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
    if(ui->envoyerMessageTextEdit->toPlainText() == ""){
        qDebug() << "Le message est vide !";
        QMessageBox::critical(
            nullptr,
            "Le message n'a pas pu être envoyé",
            "Le message est vide est n'a donc pas pu être envoyé.\n"
            );
        return;
    }

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
    modeSombre = false;
    ui->ParametrageEleve->setStyleSheet("background-color: white;");
    ui->PlanClasse->setStyleSheet("background-color: white;");
    ui->ParametrageSession->setStyleSheet("background-color: white;");
    ui->PageStatut->setStyleSheet("background-color: white;");

    ui->centralwidget->setStyleSheet("background-color: gray; color: black;");

    ui->modeClairButton->setVisible(false);
    ui->modeSombreButton->setVisible(true);
}


void MainWindow::on_modeSombreButton_clicked()
{
    modeSombre = true;
    ui->PageStatut->setStyleSheet("background-color: rgb(100, 100, 100)");
    ui->ParametrageEleve->setStyleSheet("background-color: rgb(100, 100, 100)");
    ui->PlanClasse->setStyleSheet("background-color: rgb(100, 100, 100)");
    ui->ParametrageSession->setStyleSheet("background-color: rgb(100, 100, 100)");

    ui->centralwidget->setStyleSheet("background-color: black; color: white;");

    ui->modeClairButton->setVisible(true);
    ui->modeSombreButton->setVisible(false);
}

void MainWindow::on_StatutButton_clicked()
{
    // Masquer les autres sections
    ui->ParametrageSession->setVisible(false);
    parametrageEleve = false;
    ui->ParametrageEleve->setVisible(false);

    // Afficher les sections de statut
    ui->StatutTableauGroupe->setVisible(true);
    ui->PageStatut->setVisible(true);

    // Préparer le tableau
    StatutTableauGroupe = ui->StatutTableauGroupe;
    StatutTableauGroupe->clear(); // Nettoyer l'ancien contenu

    // Déterminer le nombre de colonnes
    bool isQCM = (ui->ChoixActivite->currentText() == "QCM");
    QStringList headers = { "Nom", "Numéro de poste", "Travail déposé", "Enregistrement", "Nom de groupe", "Adresse IP" };
    if (isQCM) {
        headers << "QCM";
        StatutTableauGroupe->setColumnCount(7);
    } else {
        StatutTableauGroupe->setColumnCount(6);
    }

    StatutTableauGroupe->setHorizontalHeaderLabels(headers);

    // Définir le nombre de lignes (à adapter selon votre logique)
    StatutTableauGroupe->setRowCount(listeParticipant.size());

    // Largeurs des colonnes
    StatutTableauGroupe->setColumnWidth(0, 150); // Nom
    StatutTableauGroupe->setColumnWidth(1, 100); // Numéro de poste
    StatutTableauGroupe->setColumnWidth(2, 105); // Travail déposé
    StatutTableauGroupe->setColumnWidth(3, 120); // Enregistrement
    StatutTableauGroupe->setColumnWidth(4, 130); // Numéro de groupe
    StatutTableauGroupe->setColumnWidth(5, 120); // Adresse IP
    if (isQCM) {
        StatutTableauGroupe->setColumnWidth(6, 80); // QCM
    }

    // Remplir les lignes
    for (int row = 0; row < static_cast<int>(listeParticipant.size()); ++row) {
        auto participant = listeParticipant[row];

        QTableWidgetItem *itemNom = new QTableWidgetItem(participant->getNom());
        itemNom->setTextAlignment(Qt::AlignCenter);
        StatutTableauGroupe->setItem(row, 0, itemNom);

        QTableWidgetItem *itemID = new QTableWidgetItem(QString::number(participant->getID()));
        itemID->setTextAlignment(Qt::AlignCenter);
        itemID->setFlags(itemID->flags() & ~Qt::ItemIsEditable);
        StatutTableauGroupe->setItem(row, 1, itemID);

        QTableWidgetItem *itemTravailDepot = new QTableWidgetItem("❌");
        itemTravailDepot->setTextAlignment(Qt::AlignCenter);
        itemTravailDepot->setFlags(itemTravailDepot->flags() & ~Qt::ItemIsEditable);
        StatutTableauGroupe->setItem(row, 2, itemTravailDepot);

        QPushButton *boutonEcouter = new QPushButton("Écouter");
        boutonEcouter->setStyleSheet("background-color: gray;");
        StatutTableauGroupe->setCellWidget(row, 3, boutonEcouter);

        QTableWidgetItem *itemGroupe = new QTableWidgetItem(participant->getNomGroupe());
        itemGroupe->setTextAlignment(Qt::AlignCenter);
        itemGroupe->setFlags(itemGroupe->flags() & ~Qt::ItemIsEditable);
        StatutTableauGroupe->setItem(row, 4, itemGroupe);

        QTableWidgetItem *itemIP = new QTableWidgetItem(participant->getIP());
        itemIP->setTextAlignment(Qt::AlignCenter);
        itemIP->setFlags(itemIP->flags() & ~Qt::ItemIsEditable);
        StatutTableauGroupe->setItem(row, 5, itemIP);

        if (isQCM && qcm != nullptr) {
            QString qcmStatut = QString("%1/%2").arg(participant->getNumQCM()).arg(qcm->getSize());
            QTableWidgetItem *itemQCM = new QTableWidgetItem(qcmStatut);
            itemQCM->setTextAlignment(Qt::AlignCenter);
            itemQCM->setFlags(itemQCM->flags() & ~Qt::ItemIsEditable);
            StatutTableauGroupe->setItem(row, 6, itemQCM);
        }
    }
    // Connecter une fois (éviter les multiples connexions)
    disconnect(StatutTableauGroupe, &QTableWidget::itemChanged, this, &MainWindow::changeNameTable); // au cas où
    connect(StatutTableauGroupe, &QTableWidget::itemChanged, this, &MainWindow::changeNameTable);
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

void MainWindow::onClicked_itemBoutonAjouterGroupe(iconEleveGroup* eleve)
{
    if (!eleve || !eleveActuellementParametre)
        return;

    QString groupe = eleveActuellementParametre->getNomGroupe();

    // Si le créateur n'a pas encore de groupe assigné
    if (groupe.isEmpty()) {
        // Prendre la saisie ou générer un nom
        if (!ui->nomGroupeLineEdit->text().isEmpty()) {
            groupe = ui->nomGroupeLineEdit->text().trimmed();
        } else {
            groupe = "Groupe " + eleveActuellementParametre->getNom();
        }

        // Affecter ce groupe au créateur
        eleveActuellementParametre->setNomGroupe(groupe);

        // Ajouter le créateur dans la liste du groupe
        listeGroup[groupe].push_back(eleveActuellementParametre);

        // Si nouveau groupe, créer une couleur et allouer un port audio
        if (!couleursGroup.contains(groupe)) {
            QColor couleur = couleurDisponible();  // ta fonction pour couleur libre
            couleursGroup[groupe] = couleur;
        }

        if (!portsAudioGroupes.contains(groupe)) {
            portsAudioGroupes[groupe] = prochainPortAudioDisponible++;
        }

        // Créer le groupe audio côté serveur professeur s'il n'existe pas
        if (prof && !prof->audioGroupExists(groupe)) {
            prof->addAudioGroup(groupe, portsAudioGroupes[groupe]);
        }
    }

    // Affecter le groupe à l'élève cliqué
    eleve->setNomGroupe(groupe);

    // Récupérer la liste des membres
    std::vector<iconEleveGroup*>& membres = listeGroup[groupe];

    // Ajouter l'élève s'il n'est pas déjà membre
    if (std::find(membres.begin(), membres.end(), eleve) == membres.end()) {
        membres.push_back(eleve);
    }

    int portAudio = portsAudioGroupes[groupe];
    QString commande = "portGroup," + QString::number(portAudio);

    // Mettre à jour la liste des affiliés (membres du groupe) et pastille couleur
    for (iconEleveGroup* membre : membres) {
        // Nettoyer affiliés actuels
        membre->getAffiliate().clear();

        // Ajouter les autres membres en affiliés
        for (iconEleveGroup* autre : membres) {
            if (membre != autre) {
                membre->getAffiliate().push_back(autre);
            }
        }

        // Appliquer couleur de groupe à la pastille et positionner à droite
        if (membre->getgroupColor()) {
            membre->getgroupColor()->setVisible(true);
            membre->getgroupColor()->setBrush(couleursGroup[groupe]);

            QRectF rect = membre->sceneBoundingRect();
            membre->getgroupColor()->setPos(
                rect.width() + 5,  // décallage à droite
                (rect.height() - membre->getgroupColor()->rect().height()) / 2  // centré verticalement
                );
        }

        // Envoi commande UDP au client pour changer de port audio groupe
        if (prof) {
            prof->sendCommandToStudent(membre->getIP(), 5558, commande);
            qDebug() << "[MainWindow] Commande envoyée à " << membre->getIP() << ":" << commande;
        }
    }

    loadInformationTable(); // Rafraîchir affichage
}



void MainWindow::on_nomGroupeLineEdit_returnPressed()
{
    eleveActuellementParametre->setNomGroupe(ui->nomGroupeLineEdit->text());

    listeGroup[eleveActuellementParametre->getNomGroupe()].push_back(eleveActuellementParametre);

    qDebug() << "Nom du groupe :" << ui->nomGroupeLineEdit->text();
    qDebug() << eleveActuellementParametre->getNom() << " : " << eleveActuellementParametre->getNomGroupe();
    on_creerGroupeButton_clicked();
}

void MainWindow::onClicked_itemBoutonSupprimerGroupe(iconEleveGroup* eleve)
{
    if (!eleve) return;

    QString groupe = eleve->getNomGroupe();

    if (groupe.isEmpty() || !listeGroup.contains(groupe)) return;

    std::vector<iconEleveGroup*>& membres = listeGroup[groupe];

    // Retirer l'élève du groupe
    auto it = std::remove(membres.begin(), membres.end(), eleve);
    if (it != membres.end()) {
        membres.erase(it, membres.end());
    }

    // Vider ses affiliates et son groupe
    eleve->getAffiliate().clear();
    eleve->setNomGroupe("");

    // Mettre à jour les affiliates des autres membres
    for (iconEleveGroup* membre : membres) {
        std::vector<iconEleveGroup*> autres;
        for (iconEleveGroup* autre : membres) {
            if (membre != autre) {
                membre->getAffiliate().push_back(autre);
            }
        }

        qDebug() << membre->getNom() << " → Affiliates count après suppression:" << membre->getAffiliate().size();
    }

    loadInformationTable(); // Actualiser le tableau
}

void MainWindow::on_AideButton_clicked()
{
    HelpWindow help(this);

    if (help.exec() != QDialog::Accepted) {
        return;  // L'utilisateur a fermé sans valider, on arrête
    }
}

void MainWindow::on_cadenaCloseButton_clicked()
{
    movable = true;

    ui->cadenaCloseButton->setVisible(false);
    ui->cadenaOpenButton->setVisible(true);
}

void MainWindow::on_cadenaOpenButton_clicked()
{
    movable = false;

    ui->cadenaCloseButton->setVisible(true);
    ui->cadenaOpenButton->setVisible(false);
}

QList<QColor> MainWindow::listeCouleursDisponibles() {
    return {
        QColor("#e6194b"), // Rouge
        QColor("#3cb44b"), // Vert
        QColor("#ffe119"), // Jaune
        QColor("#0082c8"), // Bleu
        QColor("#f58231"), // Orange
        QColor("#911eb4"), // Violet
        QColor("#46f0f0"), // Cyan
        QColor("#f032e6"), // Magenta
        QColor("#d2f53c"), // Citron vert
        QColor("#fabebe"), // Rose
        QColor("#008080"), // Turquoise
        QColor("#e6beff"), // Lavande
        QColor("#aa6e28"), // Marron
        QColor("#fffac8"), // Beige
        QColor("#800000"), // Bordeaux
    };
}

QColor MainWindow::couleurDisponible() {
    QList<QColor> toutes = listeCouleursDisponibles();

    // Retirer les couleurs déjà utilisées
    for (const QColor& utilisée : couleursGroup.values()) {
        toutes.removeAll(utilisée);
    }

    // Si toutes sont prises, reprendre aléatoirement dans la liste
    return toutes.isEmpty() ? QColor::fromHsv(rand() % 360, 255, 200) : toutes.first();
}

void MainWindow::on_reloadButton_clicked()
{
    if (scene) {
        scene->clear();
        loadImagesFromDB();  // Recharge les images depuis la base (avatars, etc.)
    }
}

