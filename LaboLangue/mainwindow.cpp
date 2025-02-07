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

    scene = new QGraphicsScene(0, 0, 381, 361, this);
    ui->PlanClasse->setScene(scene);

    ui->Parametrage1->setVisible(false);
    //ui->PlanClasse->setVisible(false);

    ui->PlanButton->setEnabled(false);
    ui->PlanButton->setStyleSheet(
        "background-color: #cccccc;"  // lighter gray to indicate disable
        "font: 9pt \"Segoe UI\";"
        "color: #999999;"             // lighter text color
        "border: 1px solid #999999;"  // lighter border color
        "border-radius: 10px;"
        );

    ui->PresenceButton->setEnabled(false);
    ui->PresenceButton->setStyleSheet(
        "background-color: #cccccc;"  // lighter gray to indicate disable
        "font: 9pt \"Segoe UI\";"
        "color: #999999;"             // lighter text color
        "border: 1px solid #999999;"  // lighter border color
        "border-radius: 10px;"
        );

    ui->EnregistrementButton->setEnabled(false);
    ui->EnregistrementButton->setStyleSheet(
        "background-color: #cccccc;"  // lighter gray to indicate disable
        "font: 9pt \"Segoe UI\";"
        "color: #999999;"             // lighter text color
        "border: 1px solid #999999;"  // lighter border color
        "border-radius: 10px;"
        );

    ui->AppelButton->setEnabled(false);
    ui->AppelButton->setStyleSheet(
        "background-color: #cccccc;"  // lighter gray to indicate disable
        "font: 9pt \"Segoe UI\";"
        "color: #999999;"             // lighter text color
        "border: 1px solid #999999;"  // lighter border color
        "border-radius: 10px;"
        );

    ui->StatutButton->setEnabled(false);
    ui->StatutButton->setStyleSheet(
        "background-color: #cccccc;"  // lighter gray to indicate disable
        "font: 9pt \"Segoe UI\";"
        "color: #999999;"             // lighter text color
        "border: 1px solid #999999;"  // lighter border color
        "border-radius: 10px;"
        );

    // Créez un layout vertical pour organiser les labels
    // Créez un QHBoxLayout pour les éléments sur la même ligne
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->addWidget(ui->NameLabel);
    horizontalLayout->addWidget(ui->NameLineEdit);

    // Créez le QVBoxLayout principal
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(20, 30, 20, 10);  // Ajoute des marges
    layout->setAlignment(Qt::AlignCenter);       // Centre tout le layout
    layout->setAlignment(Qt::AlignTop);

    // Ajoutez le QHBoxLayout et les autres widgets
    layout->addLayout(horizontalLayout); // Ajoute les widgets sur la même ligne
    layout->addSpacing(15);  // Espacement entre les sections

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->addWidget(ui->ChoixActLabel);
    horizontalLayout->addWidget(ui->ChoixActivite);

    layout->addLayout(horizontalLayout);

    // Appliquez le layout à Parametrage1
    ui->Parametrage1->setLayout(layout);

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

    // Revenir à la première ligne de la requête
    query.first();

    QPixmap pixmap("../img/person.png");
    if (pixmap.isNull()) {
        qWarning("L'image n'a pas pu être chargée. Vérifiez le chemin.");
        return;
    }

    int column = 0;
    int row = 0;
    int spacing = 10;
    int maxPerRow = 7;

    int imageWidth = pixmap.width();
    int imageHeight = pixmap.height();

    int id = 1;
    do {
        QString ip = query.value(0).toString();
        int x = query.value(1).toInt();
        int y = query.value(2).toInt();

        // Vérification des valeurs x et y
        if (query.value(1).isNull() || query.value(2).isNull()) {
            x = column * (imageWidth + spacing);
            y = row * (imageHeight + spacing + 10);
        } else {
            x = query.value(1).toInt();
            y = query.value(2).toInt();
        }

        QGraphicsPixmapItem *imageItem = new QGraphicsPixmapItem(pixmap);
        imageItem->setFlag(QGraphicsItem::ItemIsMovable);

        QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::number(id));
        textItem->setPos(16, pixmap.height());

        CustomGraphicsItemGroup *group = new CustomGraphicsItemGroup(id, ip, this);
        group->addToGroup(imageItem);
        group->addToGroup(textItem);
        group->setFlag(QGraphicsItem::ItemIsMovable);

        group->setPos(x, y);
        listeRasp.push_back(group);

        connect(group, &CustomGraphicsItemGroup::doubleClicked, this, &MainWindow::onImageGroupDoubleClicked);

        scene->addItem(group);

        column++;
        if (column >= maxPerRow) {
            column = 0;
            row++;
        }
        id++;

    } while (query.next());  // Assurez-vous que vous traitez tous les résultats.

    ui->PlanClasse->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
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

void MainWindow::onImageGroupDoubleClicked() {
    qDebug() << "Slot onImageGroupDoubleClicked() exécuté !";
    // Ajoutez ici le code à exécuter lors du double-clic sur un groupe
}

void MainWindow::on_SessionButton_clicked()
{
    ui->Parametrage1->setVisible(!ui->Parametrage1->isVisible());
    ui->PlanClasse->setVisible(true);
    loadImagesFromDB();
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
    // Supposons que tu as un QComboBox nommé activityComboBox dans ton UI
    QComboBox *activityComboBox = ui->ChoixActivite;

    // Liste des activités à ajouter
    QStringList activities = {
        "📢 Audio - Écoute simple",
        "🎤 Audio - Écoute et répétition",
        "📜 Audio - Dicter et répéter",
        "🎙 Audio - Enregistrement libre",
        "📖 Audio - Lecture orale",

        "🎬 Vidéo - Regarder et répondre",
        "📹 Vidéo - Description d’une scène",
        "🎙 Vidéo - Doublage",
        "📺 Vidéo - Vidéo interactive",

        "🎭 Interactif - Jeux de rôles",
        "🗣 Interactif - Débats enregistrés",

        "🤝 Collaboratif - Travail en binôme",
        "🎙 Collaboratif - Chat écrit/audio",
        "👥 Collaboratif - Exercices en groupe",

        "🎮 Gamification - Quiz interactif",
        "🏆 Gamification - QCM en temps réel",
    };

    // Ajouter toutes les activités dans le QComboBox
    activityComboBox->addItems(activities);

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
    listeParticipant = listeRasp;
}

