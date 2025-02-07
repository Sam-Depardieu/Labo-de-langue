#include "interfacevideo.h"
#include "ui_interfacevideo.h"
#include <QAudioOutput>
#include <QStandardPaths>
InterfaceVideo::InterfaceVideo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceVideo)
{
    ui->setupUi(this);

    setFixedSize(800,480);
    this->setWindowTitle("Page de Video");

    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);

    audioOutput = new QAudioOutput(this);  // Crée un objet QAudioOutput pour gérer l'audio
    player->setAudioOutput(audioOutput);   // Associe l'objet QAudioOutput au lecteur multimédia
    setFixedSize(800,480);
    // Ajouter `videoWidget` dans l'interface (si non présent dans `.ui`)
    ui->verticalLayout->addWidget(videoWidget);

    // Associer le lecteur multimédia au widget vidéo
    player->setVideoOutput(videoWidget);

    this->setWindowTitle("Interface Vidéo");

    QPixmap imagePlay(":/images/Play"); // Charge l'image
    if (imagePlay.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imagePlay); // Crée une icône
        ui->pushButton_Play->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Play->setIconSize(ui->pushButton_Play->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imagePause(":/images/Pause"); // Charge l'image
    if (imagePause.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imagePause); // Crée une icône
        ui->pushButton_Pause->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Pause->setIconSize(ui->pushButton_Pause->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imageAvant10(":/images/Avant10"); // Charge l'image
    if (imageAvant10.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageAvant10); // Crée une icône
        ui->pushButton_Avant10->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Avant10->setIconSize(ui->pushButton_Avant10->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imageApres10(":/images/Apres10"); // Charge l'image
    if (imageApres10.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageApres10); // Crée une icône
        ui->pushButton_Apres10->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Apres10->setIconSize(ui->pushButton_Apres10->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

}

InterfaceVideo::~InterfaceVideo()
{
    delete ui;
}

void InterfaceVideo::on_pushButton_SelectVideo_clicked()
{

    // Récupère le chemin du dossier "Documents" de l'utilisateur
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Sélectionner une vidéo",
        documentsPath,  // Ouvre le dossier "Documents"
        "Vidéos (*.mp4 *.avi *.mkv *.mov *.wmv)"  // Filtrer les fichiers vidéo
        );

    if (!fileName.isEmpty()) {
        player->setSource(QUrl::fromLocalFile(fileName));  // Charger la vidéo
        videoWidget->show();  // Afficher le widget vidéo
        player->play();  // Lancer la lecture
        qDebug() << "Fichier sélectionné : " << fileName;
    }
}


void InterfaceVideo::on_pushButton_Avant10_clicked()
{
    qint64 currentPosition = player->position();

    // Rewind by 10 seconds (10000 milliseconds)
    qint64 newPosition = currentPosition - 10000;

    // Ensure we don't go below 0 (start of the video)
    if (newPosition < 0)
        newPosition = 0;
    player->setPosition(newPosition);
}


void InterfaceVideo::on_pushButton_Play_clicked()
{
    player->play();
}


void InterfaceVideo::on_pushButton_Pause_clicked()
{
    player->pause();
}


void InterfaceVideo::on_pushButton_Apres10_clicked()
{
    qint64 currentPosition = player->position();

    // Advance by 10 seconds (10000 milliseconds)
    qint64 newPosition = currentPosition + 10000;

    // Set the new position
    player->setPosition(newPosition);
}


void InterfaceVideo::on_horizontalSlider_sonVideo_actionTriggered(int action)
{
    int volume = ui->horizontalSlider_sonVideo->value();  // Récupère la valeur du slider
    audioOutput->setVolume(volume / 100.0);
}

