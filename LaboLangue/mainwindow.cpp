#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);  // Supprime la barre de titre et les boutons
    showFullScreen();

    scene = new QGraphicsScene(0, 0, 381, 361, this);
    ui->PlanClasse->setScene(scene);

    ui->Parametrage1->setVisible(false);
    ui->PlanClasse->setVisible(false);

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
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(ui->NameLabel);
    layout->addWidget(ui->NameLineEdit);

    // Appliquez le layout à Parametrage1
    ui->Parametrage1->setLayout(layout);

    loadImagesFromDB();
}

MainWindow::~MainWindow()
{
    ui->PlanClasse->setScene(nullptr); // Déconnecter la scène avant de la supprimer
    delete scene;
    delete ui;
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

void MainWindow::loadImagesFromDB()
{
    if (!connectToDatabase()) {
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT SessionEleve.Id_Eleve, Activite.Id_Classe, Raspberry.IP, Placement.X, Placement.Y "
                  "FROM SessionEleve "
                  "JOIN Activite ON Activite.Id_Classe = SessionEleve.Id_Classe "
                  "JOIN Raspberry ON Raspberry.Id_Raspberry = SessionEleve.Id_Raspberry "
                  "JOIN Placement ON Placement.NumPoste = Raspberry.NumPoste "
                  "WHERE Activite.Id_Activite = :idActivite");

    query.bindValue(":idActivite", 1);  // ID de l'activité sélectionnée

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError();
        return;
    }

    QPixmap pixmap("../img/person.png");
    if (pixmap.isNull()) {
        qWarning("L'image n'a pas pu être chargée.");
        return;
    }

    int column = 0;
    int row = 0;
    int spacing = 10;
    int maxPerRow = 7;

    int imageWidth = pixmap.width();
    int imageHeight = pixmap.height();

    int id = 1;
    while (query.next()) {
        int id_eleve = query.value(0).toInt();
        QString ip = query.value(2).toString();
        int x = query.value(3).toInt();
        int y = query.value(4).toInt();

        QGraphicsPixmapItem *imageItem = new QGraphicsPixmapItem(pixmap);
        imageItem->setFlag(QGraphicsItem::ItemIsMovable);

        QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::number(id));
        textItem->setPos(16, pixmap.height());

        CustomGraphicsItemGroup *group = new CustomGraphicsItemGroup(id, id_eleve, ip);
        group->addToGroup(imageItem);
        group->addToGroup(textItem);
        group->setFlag(QGraphicsItem::ItemIsMovable);

        if (x == 0 || y == 0) {
            x = column * (imageWidth + spacing);
            y = row * (imageHeight + spacing + 10);
        }
        group->setPos(x, y);

        listeElve.push_back(group);

        connect(group, &CustomGraphicsItemGroup::doubleClicked, this, &MainWindow::onImageGroupDoubleClicked);

        scene->addItem(group);

        column++;
        if (column >= maxPerRow) {
            column = 0;
            row++;
        }
        id++;
    }

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
}

