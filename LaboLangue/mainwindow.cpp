#include "mainwindow.h"
#include "helpwindow.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "ui_mainwindow.h"

// CONSTRUCTEUR
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);  // Supprime la barre de titre et les boutons
    //showFullScreen();
    connectToDatabase();

    gestion_Session = new gestionSession(this, QSqlDatabase::database());

    QString ip;

    const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    for (const QNetworkInterface &interface : interfaces) {
        QString name = interface.humanReadableName().toLower();
        QString systemName = interface.name().toLower();

        // On filtre les interfaces virtuelles ou inutiles
        if (interface.flags().testFlag(QNetworkInterface::IsUp) &&
            interface.flags().testFlag(QNetworkInterface::IsRunning) &&
            !interface.flags().testFlag(QNetworkInterface::IsLoopBack) &&
            !name.contains("virtual") &&
            !name.contains("vmware") &&
            !name.contains("tunnel") &&
            !name.contains("vbox") &&
            !name.contains("loopback") &&
            !name.contains("docker") &&
            !systemName.contains("vmnet") &&
            !systemName.contains("npf") &&
            !systemName.contains("vnic")) {

            // On récupère l'adresse IPv4
            for (const QNetworkAddressEntry &entry : interface.addressEntries()) {
                QHostAddress address = entry.ip();
                if (address.protocol() == QAbstractSocket::IPv4Protocol) {
                    ip = address.toString();
                    qDebug() << "Interface réseau :" << interface.humanReadableName();
                    qDebug() << "Adresse IP physique trouvée :" << ip;
                    break; // On sort dès qu'on a trouvé
                }
            }
        }
    }
    qDebug() << "Adresse IP physique trouvée :" << ip;


    if (ip.isEmpty())
        qDebug() << "Aucune adresse IP valide trouvée.";

    // Création de la scène
    scene = new QGraphicsScene(0, 0, 631, 681, this);
    ui->PlanClasse->setScene(scene);


    ui->ParametrageEleve->setVisible(false);

    // Désactivation des boutons
    editStatusButton(ui->PresenceButton, false);
    editStatusButton(ui->EnregistrementButton, false);
    editStatusButton(ui->AppelButton, false);
    editStatusButton(ui->StatutButton, false);
    editStatusButton(ui->CreationButton, false);

    ui->chronoLabel->setVisible(false);
    ui->enleveTemps->setVisible(false);
    ui->ajouterTemps->setVisible(false);
    ui->tempsChronoLineEdit->setVisible(false);

    ui->tempsChronoLineEdit->setPlaceholderText("00:00");

    // Créer le layout principal pour la gestion audio des élèves et des groupes avec les éléments disposés
    QVBoxLayout *layoutParametrageEleve = new QVBoxLayout();
    layoutParametrageEleve->setContentsMargins(8, 8, 15, 8);
    layoutParametrageEleve->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    // Ajout des sections dans le layoutParametrageEleve
    addHorizontalLayout(layoutParametrageEleve, {ui->nomGroupeLabel, ui->nomEleveLineEdit, ui->Communication});
    addHorizontalLayout(layoutParametrageEleve, {ui->microSonButton, ui->casqueSonButton});
    addHorizontalLayout(layoutParametrageEleve, {ui->creerGroupeButton, ui->pauseButton, ui->lectureButton});
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
    ui->pauseButton->setStyleSheet("background-color: rgb(255, 0, 0)");
    ui->lectureButton->setStyleSheet("background-color: #28a745;");
    // Cacher les boutons de la page
    ui->lectureButton->setVisible(false);
    ui->nomCreationGroupeLabel->setVisible(false);
    ui->nomGroupeLineEdit->setVisible(false);
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
    layoutPageStatut->addWidget(ui->RunningActivite);
    addHorizontalLayout(layoutPageStatut, {ui->LectureStatutButton, ui->PauseStatutButton});
    addHorizontalLayout(layoutPageStatut, {ui->alignerTableau_2, ui->StatutTableauGroupe});
    layoutPageStatut->addSpacing(10);
    // Appliquez le layout à PageStatut
    ui->PageStatut->setLayout(layoutPageStatut);
    ui->alignerTableau_2->setVisible(false);
    ui->PageStatut->setVisible(false);

    ui->LectureStatutButton->setVisible(false);
    ui->PauseStatutButton->setVisible(false);

    ui->LectureStatutButton->setIcon(QIcon(QPixmap(":/img/play.png")));
    ui->PauseStatutButton->setIcon(QIcon(QPixmap(":/img/pause.png")));

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

    udpSocketAppel = new QUdpSocket(this);
    connect(udpSocketAppel, &QUdpSocket::readyRead, this, &MainWindow::demandeAide);
}

void MainWindow::demandeAide()
{

    while (udpSocketAppel->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketAppel->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocketAppel->readDatagram(datagram.data(),
                                       datagram.size(),
                                       &sender,
                                       &senderPort);
        QString cmd = QString::fromUtf8(datagram).trimmed().toUtf8();
        qDebug() << "📢 RECV:" << cmd << "depuis" << sender.toString();

        if (cmd == "help") {
            qDebug() << "🔇 Commande MUTE reçue";
            for(unsigned int i=0; i!=listeParticipant.size(); i++)
            {
                if(listeParticipant[i]->getIP() == sender.toString())
                {
                    listeParticipant[i]->getLeveMain()->setVisible(true);
                }
            }
        }
    }
}

// DESTRUCTEUR
MainWindow::~MainWindow()
{
    ui->PlanClasse->setScene(nullptr); // Déconnecter la scène avant de la supprimer
    delete scene;
    delete ui;
}

// GESTIONSESSION
    // Le professeur choisis le type d'activité
    void MainWindow::setupActivitiesComboBox(){
        QStringList activites = gestion_Session->getActivites();
        ui->ChoixActivite->addItems(activites);
    }
    // Le professeur entre le nom de la classe
    void MainWindow::setupClassesComboBox(){
        QStringList classes = gestion_Session->getClasses();
        ui->ChoixClasse->addItems(classes);
    }
    // Le professeur valide la session
    void MainWindow::on_validButton_clicked()
    {
        if (ui->NomProfLineEdit->text().isEmpty() ||
            ui->ChoixActivite->currentText().isEmpty() ||
            ui->DureeActivite->time().isNull() ||
            ui->ChoixClasse->currentText().isEmpty() ||
            listeParticipant.empty()) {
            ui->errorLabel->setText("Veuillez remplir tous les champs !");
            return;
        }
        if ((nomTypeActivite.contains("video") || nomTypeActivite.contains("ecoute")) && source == nullptr)
        {
            ui->errorLabel->setText("Veuillez indiquer un fichier audio ou video.");
            return;
        }
        listeEleveParticipant.clear();
        int idProf = -1;
        bool ok = gestion_Session->validerEtEnregistrerSession(
            ui->NomProfLineEdit->text(),
            ui->ChoixActivite->currentText(),
            ui->ChoixClasse->currentText(),
            ui->DureeActivite->time(),
            ui->ConsigneTextEdit->toPlainText(),
            source,
            listeParticipant,
            listeEleveParticipant,
            idProf,
            runningSession
            );
        if (!ok) {
            ui->errorLabel->setText("Erreur lors de l'enregistrement de la session.");
            return;
        }
        prof = new Professeur(this);
        saveSessionData(!runningSession);
        // Si activité QCM
        if (ui->ChoixActivite->currentText() == "QCM") {
            editStatusButton(ui->CreationButton, true);
            on_CreationButton_clicked();
            udpSocketQCM = new QUdpSocket(this);
            udpSocketQCM->bind(45454, QUdpSocket::ShareAddress);
            connect(udpSocketQCM, &QUdpSocket::readyRead, this, &MainWindow::majStatusQCM);
            if (!interfaceQCMOpen) {
                qcm = new QCM(this, this);
                qcm->show();
                interfaceQCMOpen = true;
            }
            return;
        }
        gestion_Session->continuerCreationSession(runningSession);
    }

    void MainWindow::on_loadSession_clicked()
    {

        choixSession choix(this);
        if (choix.exec() != QDialog::Accepted) {
            return;  // L'utilisateur a fermé sans valider, on arrête
        }

        gestion_Session->loadSession();
    }

    void MainWindow::on_SourceButton_clicked()
    {
        gestion_Session->on_SourceButton_clicked();
    }

    void MainWindow::saveSessionData(bool isNewSession)
    {
        if (ui->NomProfLineEdit->text() == "") {
            qDebug() << "❌ Erreur : nomProf est vide.";
            return;
        }

        // Préparation des chemins
        QString sanitizedName = ui->NomProfLineEdit->text();
        sanitizedName.replace(" ", "_").remove(QRegularExpression("[^a-zA-Z0-9_-]"));

        QString hostName = QHostInfo::localHostName();
        QString networkPath = QString(R"(\\%1\Activites\)").arg("CIEL-T171-05");
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm");
        sessionFolder = sanitizedName + "_" + timestamp;
        sessionPATH = networkPath + sanitizedName + "_" + timestamp;
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

    void MainWindow::resetSession(){ gestion_Session->reset();}


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

void MainWindow::setNomEtudiantLineEdit(QString nom)
{
    ui->nomEleveLineEdit->setText(nom);
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
    db.setHostName("192.168.64.1");
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
 * Fonctions lié aux boutons de l'IHM (Boutton)
 */

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
    nomTypeActivite = ui->ChoixActivite->currentText();
    if(nomTypeActivite == "QCM") ui->SourceButton->setDisabled(true);
    else ui->SourceButton->setEnabled(true);
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

void MainWindow::on_echapButton_clicked()
{
    ui->ParametrageSession->setVisible(false);
}

void MainWindow::on_CreationButton_clicked()
{
    qcm = new QCM(this, this);
    if(!interfaceQCMOpen) qcm->show();
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

void MainWindow::on_pauseButton_clicked()
{
    ui->pauseButton->setVisible(false);
    ui->lectureButton->setVisible(true);
    prof->sendCommandToStudent(eleveActuellementParametre->getIP(), 5557, "pause");
}

void MainWindow::on_lectureButton_clicked()
{
    ui->lectureButton->setVisible(false);
    ui->pauseButton->setVisible(true);
    prof->sendCommandToStudent(eleveActuellementParametre->getIP(), 5557, "lecture");
}


void MainWindow::changeNameTable(QTableWidgetItem* item) {
    if (item->column() != 0) return; // Ne gérer que la colonne "Nom"

    unsigned int row = item->row();
    QString nouveauNom = item->text();

    if (row >= 0 && row < listeParticipant.size()) {
        iconEleveGroup* eleve = listeParticipant[row];
        QString ancienNom = eleve->getNom();

        if (nouveauNom != ancienNom) {
            updateEleveNom(eleve, nouveauNom); // MAJ interface + BDD
        }
    }
}



void MainWindow::loadInformationTable()
{
    // Crée une table de 12 lignes et 4 colonnes
    ui->TableauGroupe->setColumnCount(4);

    ui->TableauGroupe->setRowCount(listeRasp.size());
    TableauGroupe = ui->TableauGroupe;

    // Ajouter des en-têtes pour les colonnes
    TableauGroupe->setHorizontalHeaderLabels({"Nom", "Numéro de poste", "Ajoutez au groupe", "Nom du groupe", "Adresse IP"});
    TableauGroupe->setColumnWidth(0, 110); // Nom
    TableauGroupe->setColumnWidth(1, 100); // Numéro de poste
    TableauGroupe->setColumnWidth(2, 130); // Ajoutez au groupe
    TableauGroupe->setColumnWidth(4, 120); // Nom du groupe


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
    prof->sendCommandToStudent(eleveActuellementParametre->getIP(), 5560, "nomEleve," + ui->nomEleveLineEdit->text());
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
    ui->tempsChronoLineEdit->setStyleSheet("color-text: white;");

    ui->modeClairButton->setVisible(true);
    ui->modeSombreButton->setVisible(false);
}

void MainWindow::on_StatutButton_clicked()
{
    ui->RunningActivite->setText("Activitée en cours :\t"+ui->ChoixActivite->currentText());
    // Masquer les autres sections
    ui->ParametrageSession->setVisible(false);
    parametrageEleve = false;
    ui->ParametrageEleve->setVisible(false);

    // Afficher les sections de statut
    ui->StatutTableauGroupe->setVisible(true);
    ui->PageStatut->setVisible(true);

    if(ui->ChoixActivite->currentText() == "QCM"){
        ui->LectureStatutButton->setVisible(false);
        ui->PauseStatutButton->setVisible(false);
    }
    else{
        ui->LectureStatutButton->setVisible(true);
        ui->PauseStatutButton->setVisible(true);
    }

    // Préparer le tableau
    StatutTableauGroupe = ui->StatutTableauGroupe;
    StatutTableauGroupe->clear(); // Nettoyer l'ancien contenu

    // Déterminer le nombre de colonnes
    bool isQCM = (ui->ChoixActivite->currentText() == "QCM");
    bool isEnregistremnt = (ui->ChoixActivite->currentText() == "Enregistrement");
    QStringList headers = { "Nom", "Numéro de poste", "Travail déposé"};
    if (isQCM) {
        headers << "Avancement";
    }
    else if(isEnregistremnt)
    {
        headers << "Enregistrement";
    }
    else headers << "Travail en cours";

    headers << "Nom de groupe" << "Adresse IP";
    StatutTableauGroupe->setColumnCount(5);

    StatutTableauGroupe->setHorizontalHeaderLabels(headers);

    // Définir le nombre de lignes (à adapter selon votre logique)
    StatutTableauGroupe->setRowCount(listeParticipant.size());

    // Largeurs des colonnes
    StatutTableauGroupe->setColumnWidth(0, 150); // Nom
    StatutTableauGroupe->setColumnWidth(1, 100); // Numéro de poste
    StatutTableauGroupe->setColumnWidth(2, 105); // Travail déposé
    StatutTableauGroupe->setColumnWidth(3, 120); // Enregistrement
    StatutTableauGroupe->setColumnWidth(4, 130); // Numéro de groupe

    qDebug() << isQCM;

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

        QTableWidgetItem *itemGroupe = new QTableWidgetItem(participant->getNomGroupe());
        itemGroupe->setTextAlignment(Qt::AlignCenter);
        itemGroupe->setFlags(itemGroupe->flags() & ~Qt::ItemIsEditable);
        StatutTableauGroupe->setItem(row, 4, itemGroupe);

        if (isQCM) {
            int numQCM = participant->getNumQCM();
            int totalQCM = (qcm != nullptr) ? qcm->getSize() : 0;
            QString qcmStatut = QString("%1/%2").arg(numQCM).arg(totalQCM);
            QTableWidgetItem *itemQCM = new QTableWidgetItem(qcmStatut);
            itemQCM->setTextAlignment(Qt::AlignCenter);
            itemQCM->setFlags(itemQCM->flags() & ~Qt::ItemIsEditable);
            StatutTableauGroupe->setItem(row, 3, itemQCM);
        }
        else {
            QPushButton *boutonEcouter = new QPushButton("Écouter");
            boutonEcouter->setStyleSheet("background-color: gray;");
            StatutTableauGroupe->setCellWidget(row, 3, boutonEcouter);
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

    // ======= Sauvegarder les membres avant modification ========
    std::vector<iconEleveGroup*> anciensMembres = listeGroup[groupe];

    // Affecter le groupe à l'élève cliqué
    eleve->setNomGroupe(groupe);

    // Ajouter l'élève s'il n'est pas déjà membre
    std::vector<iconEleveGroup*>& membres = listeGroup[groupe];
    if (std::find(membres.begin(), membres.end(), eleve) == membres.end()) {
        membres.push_back(eleve);
    }

    int portAudio = portsAudioGroupes[groupe];
    QString commande = "portGroup," + QString::number(portAudio);

    // Mettre à jour la liste des affiliés et couleur
    for (iconEleveGroup* membre : membres) {
        membre->getAffiliate().clear();
        for (iconEleveGroup* autre : membres) {
            if (membre != autre) {
                membre->getAffiliate().push_back(autre);
            }
        }

        if (membre->getgroupColor()) {
            membre->getgroupColor()->setVisible(true);
            membre->getgroupColor()->setBrush(couleursGroup[groupe]);

            QRectF rect = membre->sceneBoundingRect();
            membre->getgroupColor()->setPos(
                rect.width() + 5,
                (rect.height() - membre->getgroupColor()->rect().height()) / 2
                );
        }

        // ======= N'envoyer la commande qu'aux nouveaux membres ========
        if (prof && std::find(anciensMembres.begin(), anciensMembres.end(), membre) == anciensMembres.end()) {
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
    eleve->getgroupColor()->setVisible(false);
    eleve->getgroupColor()->setBrush(QBrush());

    // Couper la communication audio avec cet élève
    prof->muteStudent(eleve->getIP());  // <-- Assure-toi que cette méthode existe dans iconEleveGroup

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


void MainWindow::on_AideButton_clicked(){
    HelpWindow help(this);

    if (help.exec() != QDialog::Accepted) {
        return;  // L'utilisateur a fermé sans valider, on arrête
    }
}

void MainWindow::on_cadenaCloseButton_clicked(){
    movable = true;
    ui->cadenaCloseButton->setVisible(false);
    ui->cadenaOpenButton->setVisible(true);
}

void MainWindow::on_cadenaOpenButton_clicked(){
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
        loadImagesFromDB();
    }
}

void MainWindow::on_LectureStatutButton_clicked()
{
    for(unsigned int i=0; i!=listeParticipant.size(); i++)
    {
        prof->sendCommandToStudent(listeParticipant[i]->getIP(), 5557, "lecture");
    }
}

void MainWindow::on_PauseStatutButton_clicked()
{
    for(unsigned int i=0; i!=listeParticipant.size(); i++)
    {
        prof->sendCommandToStudent(listeParticipant[i]->getIP(), 5557, "pause");
    }
}

void MainWindow::on_AppelButton_clicked()
{
    prof->setBroadcastEnabled(!prof->getBroadcastEnabled());
}


void MainWindow::on_ajouterTemps_clicked()
{
    QTime tempsAjouter = QTime::fromString(ui->tempsChronoLineEdit->text(), "mm:ss");
    if (!tempsAjouter.isValid()) return;

    int secondesModif = QTime(0, 0).secsTo(tempsAjouter);

    // Mettre à jour remainingTime directement
    int secondesActuelles = QTime(0, 0).secsTo(remainingTime);
    int total = secondesActuelles + secondesModif;
    if (total > 3600) {
        QMessageBox::warning(this, "Erreur", "Impossible de dépasser une heure !");
        return;
    }
    remainingTime = QTime(0, 0).addSecs(total);

    // Met à jour le label
    ui->chronoLabel->setText(remainingTime.toString("mm:ss"));
    for (auto *eleve : listeRasp) {
        getProf()->sendCommandToStudent(eleve->getIP(), 5558, QString("chrono,%1").arg(remainingTime.toString("mm:ss")));
    }
}

void MainWindow::on_enleveTemps_clicked()
{

    QTime tempsRetirer = QTime::fromString(ui->tempsChronoLineEdit->text(), "mm:ss");
    if (!tempsRetirer.isValid()) return;

    int secondesModif = QTime(0, 0).secsTo(tempsRetirer);

    // Mettre à jour remainingTime directement
    int secondesActuelles = QTime(0, 0).secsTo(remainingTime);
    int total = secondesActuelles - secondesModif;
    if (secondesModif > secondesActuelles) {
        QMessageBox::warning(this, "Erreur", "Impossible de retirer plus de temps qu’il n’en reste !");
        return;
    }
    remainingTime = QTime(0, 0).addSecs(total);

    // Met à jour le label
    ui->chronoLabel->setText(remainingTime.toString("mm:ss"));
    for (auto *eleve : listeRasp) {
        getProf()->sendCommandToStudent(eleve->getIP(), 5558, QString("chrono,%1").arg(remainingTime.toString("mm:ss")));
    }
}

