#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);  // Supprime la barre de titre et les boutons
    showFullScreen();
    connectToDatabase();

    // Création de la scène
    scene = new QGraphicsScene(0, 0, 381, 361, this);
    ui->PlanClasse->setScene(scene);

    ui->ParametrageSession->setVisible(false);
    ui->ParametrageEleve->setVisible(false);

    // Désactivation des boutons
    editStatusButton(ui->PlanButton, false);
    editStatusButton(ui->PresenceButton, false);
    editStatusButton(ui->EnregistrementButton, false);
    editStatusButton(ui->AppelButton, false);
    editStatusButton(ui->StatutButton, false);

    // Créer le layout principal avec les éléments disposés
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(10, 10, 20, 10);
    layout->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    // Ajout des sections dans le layout
    addHorizontalLayout(layout, ui->NameLabel, ui->NameLineEdit);
    addHorizontalLayout(layout, ui->ChoixActLabel, ui->ChoixActivite);
    addHorizontalLayout(layout, ui->DureeLabel, ui->DureeActivite);
    addHorizontalLayout(layout, ui->ClasseLabel, ui->ChoixClasse);
    addHorizontalLayout(layout, ui->ParticipantsLabel, ui->selectAll, ui->selectManuel);
    addHorizontalLayout(layout, ui->SourceLabel, ui->SourceButton);
    addHorizontalLayout(layout, ui->ConsigneLabel, ui->ConsigneTextEdit);
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(ui->errorLabel);
    layout->addLayout(hLayout);
    layout->addSpacing(15);
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

    if (personPixmap.isNull() || checkPixmap.isNull()) {
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
        textItem->setPos(16, personPixmap.height());

        // Création du groupe personnalisé
        CustomGraphicsItemGroup *group = new CustomGraphicsItemGroup(id, ip, this);
        group->addToGroup(imageItem);
        group->addToGroup(textItem);
        group->setFlag(QGraphicsItem::ItemIsMovable);

        // Création des icônes Check et Cross
        QGraphicsPixmapItem *checkItem = new QGraphicsPixmapItem(checkPixmap);
        checkItem->setPos(imageItem->boundingRect().right() - checkPixmap.width(), imageItem->boundingRect().top());
        checkItem->setVisible(false); // Caché par défaut

        // Ajout des icônes au groupe
        group->addToGroup(checkItem);

        // Sauvegarde des icônes dans l'objet pour pouvoir les modifier après
        group->setCheckItem(checkItem);

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
        checkItem->setVisible(true); // Afficher l'icône check
    } else {
        qDebug() << "L'icône check est introuvable pour ce groupe.";
    }
}



bool MainWindow::connectToDatabase() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        return true; // La connexion existe déjà
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("LaboLangue");
    db.setUserName("prof"); // Remplacez par votre nom d'utilisateur
    db.setPassword("okokok"); // Remplacez par votre mot de passe

    if (!db.open()) {
        qDebug() << "Impossible de se connecter à la base de données :" << db.lastError();
        return false;
    }
    return true;
}

void MainWindow::onImageGroupDoubleClicked() {
    qDebug() << "Slot onImageGroupDoubleClicked() exécuté !";

    // Ajoutez ici le code à exécuter lors du double-clic sur un groupe
}

void MainWindow::on_SessionButton_clicked()
{
    ui->ParametrageSession->setVisible(!ui->ParametrageSession->isVisible());
    ui->PlanClasse->setVisible(true);
}

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
    selectionParticipants = true;
}


void MainWindow::on_selectAll_clicked()
{

    for(unsigned int i=0; i!=listeRasp.size(); i++) {
        showCheckIconOnGroup(listeRasp[i]);
        listeParticipant.push_back(listeRasp[i]);
    }
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
}

void MainWindow::on_validButton_clicked()
{
    ui->errorLabel->clear();

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

    QSqlQuery query;

    // 🔹 Récupérer les IDs nécessaires en une seule requête par table
    int idTypeActivite = -1, idClasse = -1, idProf = -1;

    query.prepare("SELECT Id_TypeActivite FROM TypeActivite WHERE Nom = :nom");
    query.bindValue(":nom", ui->ChoixActivite->currentText());
    if (query.exec() && query.next()) {
        idTypeActivite = query.value(0).toInt();
    } else {
        qDebug() << "Erreur lors de la récupération de l'ID d'activité :" << query.lastError();
    }

    query.prepare("SELECT Id_Classe FROM Classe WHERE Nom = :nom");
    query.bindValue(":nom", ui->ChoixClasse->currentText());
    if (query.exec() && query.next()) {
        idClasse = query.value(0).toInt();
    } else {
        qDebug() << "Erreur lors de la récupération de l'ID de classe :" << query.lastError();
    }

    query.prepare("SELECT Id_Prof FROM Prof WHERE Nom = :nom");
    query.bindValue(":nom", ui->NameLineEdit->text());
    if (query.exec() && query.next()) {
        idProf = query.value(0).toInt();
    } else {
        QSqlQuery query;

        // Si le prof n'existe pas encore, on l'insère
        query.prepare("INSERT INTO SessionProf (Nom, Date_Session) VALUES (:nom, :date)");
        query.bindValue(":nom", ui->NameLineEdit->text());
        query.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

        if (query.exec()) {
            idProf = query.lastInsertId().toInt();  // Récupérer l'ID généré
        } else {
            qDebug() << "Erreur lors de l'insertion du professeur :" << query.lastError().text();
            return; // Stopper l'exécution si l'insertion échoue
        }
    }

    // 🔹 Vérifier si on a bien récupéré les IDs avant d'insérer l'activité
    if (idTypeActivite == -1 || idClasse == -1 || idProf == -1) {
        qDebug() << "Erreur : Impossible de récupérer tous les identifiants nécessaires.";
        return;
    }

    // 🔹 Insérer l'activité
    query.prepare("INSERT INTO Activite (Source, Consigne, Duree_Activite, DateActivite, Id_TypeActivite, Id_Classe, Id_Prof) "
                  "VALUES (:source, :consigne, :duree, :date, :type, :classe, :prof)");
    query.bindValue(":source", source);
    query.bindValue(":consigne", ui->ConsigneTextEdit->toPlainText());
    query.bindValue(":duree", ui->DureeActivite->time().toString("HH:mm:ss"));
    query.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":type", idTypeActivite);
    query.bindValue(":classe", idClasse);
    query.bindValue(":prof", idProf);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion de l'activité :" << query.lastError();
    } else {
        qDebug() << "Insertion de l'activité réussie !";
    }

    on_echapButton_clicked();

    editStatusButton(ui->PlanButton, true);
    editStatusButton(ui->PresenceButton, true);
    editStatusButton(ui->EnregistrementButton, true);
    editStatusButton(ui->AppelButton, true);
    editStatusButton(ui->StatutButton, true);
}

void MainWindow::on_delButton_clicked()
{
    ui->NameLineEdit->setText("");
    ui->DureeActivite->setTime(QTime::fromString("00:00:00"));
    ui->ConsigneTextEdit->setText("");
    listeParticipant = {};
    selectionParticipants = false;
    for(unsigned int i=0; i!=listeRasp.size(); i++) {
        if (!listeRasp[i]) return;

        // Récupérer l'icône check du groupe
        QGraphicsPixmapItem *checkItem = listeRasp[i]->getCheckItem();

        if (checkItem) {
            checkItem->setVisible(false); // Afficher l'icône check
        } else {
            qDebug() << "L'icône check est introuvable pour ce groupe.";
        }
    }
}


void MainWindow::on_echapButton_clicked()
{
    on_delButton_clicked();
    ui->ParametrageSession->setVisible(false);
}

void MainWindow::openParametrageEleve()
{
    ui->ParametrageEleve->setVisible(true);
}
