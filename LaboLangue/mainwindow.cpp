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

void MainWindow::loadImagesFromDB() {
    if (!connectToDatabase()) {
        return;
    }

    QSqlQuery query("SELECT Id_Eleve, Activite.Id_Classe, Raspberry.IP FROM SessionEleve, Activite, Raspberry WHERE Activite.Id_Activite = 1 AND Activite.Id_Classe = SessionEleve.Id_Classe AND Raspberry.Id_Raspberry = SessionEleve.Id_Raspberry");
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError();
        return;
    }

    QPixmap pixmap("../img/person.png");
    if (pixmap.isNull()) {
        qWarning("L'image n'a pas pu être chargée.");
        return;
    }

    int column = 0;       // Compteur pour savoir quand passer à la ligne suivante
    int row = 0;          // Compteur de ligne
    int spacing = 10;     // Espacement entre les images
    int maxPerRow = 7;    // Nombre max d'images par ligne

    int imageWidth = pixmap.width();
    int imageHeight = pixmap.height();

    int id = 1;
    while (query.next()) {
        int id_eleve = query.value(0).toInt();
        QString ip = query.value(2).toString();

        // Ajouter l'image
        QGraphicsPixmapItem *imageItem = new QGraphicsPixmapItem(pixmap);
        imageItem->setFlag(QGraphicsItem::ItemIsMovable);

        // Ajouter le texte avec le numéro de l'élève
        QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::number(id));
        textItem->setPos(16, pixmap.height()); // Positionner le texte en dessous de l'image

        // Créer un groupe pour regrouper l'image et le texte
        CustomGraphicsItemGroup *group = new CustomGraphicsItemGroup(id, id_eleve, ip);
        group->addToGroup(imageItem);
        group->addToGroup(textItem);
        group->setFlag(QGraphicsItem::ItemIsMovable);

        // Calculer la position pour garantir 6 colonnes max par ligne
        int x = column * (imageWidth + spacing);
        int y = row * (imageHeight + spacing +10);
        group->setPos(x, y);

        listeElve.push_back(group);

        // Connecter le signal doubleClicked à un slot
        connect(group, &CustomGraphicsItemGroup::doubleClicked, this, &MainWindow::onImageGroupDoubleClicked);

        // Ajouter le groupe à la scène
        scene->addItem(group);

        // Mettre à jour la colonne et la ligne
        column++;
        if (column >= maxPerRow) { // Si on atteint 6 colonnes, passer à la ligne suivante
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

void MainWindow::on_NewButton_clicked()
{
    ui->Parametrage->setVisible(!ui->Parametrage->isVisible());
}

