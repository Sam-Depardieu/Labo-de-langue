#include "interfacevideo.h"
#include "ui_interfacevideo.h"
#include <QAudioOutput>
InterfaceVideo::InterfaceVideo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceVideo)
{
    ui->setupUi(this);

    setFixedSize(800,480);
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

    QPixmap imagePlay(":/image/Play"); // Charge l'image
    if (imagePlay.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imagePlay); // Crée une icône
        ui->pushButton_Play->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Play->setIconSize(ui->pushButton_Play->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imagePause(":/image/Pause"); // Charge l'image
    if (imagePause.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imagePause); // Crée une icône
        ui->pushButton_Pause->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Pause->setIconSize(ui->pushButton_Pause->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imageAvant10(":/image/Avant10"); // Charge l'image
    if (imageAvant10.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageAvant10); // Crée une icône
        ui->pushButton_Avant10->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Avant10->setIconSize(ui->pushButton_Avant10->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imageApres10(":/image/Apres10"); // Charge l'image
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

}


void InterfaceVideo::on_pushButton_Avant10_clicked()
{

}


void InterfaceVideo::on_pushButton_Play_clicked()
{

}


void InterfaceVideo::on_pushButton_Pause_clicked()
{

}


void InterfaceVideo::on_pushButton_Apres10_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Sélectionner une vidéo",
        "C:\\",  // Définit C:\ comme dossier par défaut
        "Videos (*.mp4 *.avi *.mkv)"
        );

}


void InterfaceVideo::on_horizontalSlider_sonVideo_actionTriggered(int action)
{
    int volume = ui->horizontalSlider_sonVideo->value();  // Récupère la valeur du slider
    audioOutput->setVolume(volume / 100.0);
}

