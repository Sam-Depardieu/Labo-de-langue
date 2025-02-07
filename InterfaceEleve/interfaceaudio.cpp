#include "interfaceaudio.h"
#include "ui_interfaceaudio.h"
#include <QAudioOutput>
#include <QStandardPaths>

InterfaceAudio::InterfaceAudio(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceAudio)
{
    ui->setupUi(this);
    setFixedSize(800,480);
    this->setWindowTitle("Page de Comprehension Orale");


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
        ui->pushButton_Avant->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Avant->setIconSize(ui->pushButton_Avant->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imageApres10(":/images/Apres10"); // Charge l'image
    if (imageApres10.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageApres10); // Crée une icône
        ui->pushButton_Apres->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Apres->setIconSize(ui->pushButton_Apres->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
}

InterfaceAudio::~InterfaceAudio()
{
    delete ui;
}

void InterfaceAudio::on_pushButton_Avant_clicked()
{
    qint64 currentPosition = player->position();

    // Rewind by 10 seconds (10000 milliseconds)
    qint64 newPosition = currentPosition - 10000;

    // Ensure we don't go below 0 (start of the video)
    if (newPosition < 0)
        newPosition = 0;
    player->setPosition(newPosition);
}


void InterfaceAudio::on_pushButton_Play_clicked()
{
    player->play();
}


void InterfaceAudio::on_pushButton_Pause_clicked()
{
     player->pause();
}


void InterfaceAudio::on_pushButton_SelectAudio_clicked()
{
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation); // Récupère le dossier Documents

    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Sélectionner un fichier audio",
        documentsPath,  // Définit "Documents" comme dossier par défaut
        "Audio Files (*.mp3 *.wav *.ogg *.flac *.aac)"  // Filtre uniquement les fichiers audio
        );

    if (!fileName.isEmpty()) {
        player->setSource(QUrl::fromLocalFile(fileName));  // Charger le fichier audio
        player->play();  // Lancer la lecture
        qDebug() << "Fichier sélectionné : " << fileName;
    }
}


void InterfaceAudio::on_horizontalSliderSon_actionTriggered(int action)
{
    int volume = ui->horizontalSliderSon->value();  // Récupère la valeur du slider
    audioOutput->setVolume(volume / 100.0);
}


void InterfaceAudio::on_pushButton_Apres_clicked()
{
    qint64 currentPosition = player->position();

    // Advance by 10 seconds (10000 milliseconds)
    qint64 newPosition = currentPosition + 10000;

    // Set the new position
    player->setPosition(newPosition);
}

