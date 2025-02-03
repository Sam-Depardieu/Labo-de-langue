#include "interfaceaudio.h"
#include "ui_interfaceaudio.h"
#include <QAudioOutput>

interfaceaudio::interfaceaudio(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::interfaceaudio)
{
    ui->setupUi(this);
    setFixedSize(800,480);
    this->setWindowTitle("Interface Audio");

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
        ui->pushButton_Avant->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Avant->setIconSize(ui->pushButton_Avant->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imageApres10(":/image/Apres10"); // Charge l'image
    if (imageApres10.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageApres10); // Crée une icône
        ui->pushButton_Apres->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Apres->setIconSize(ui->pushButton_Apres->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

}

interfaceaudio::~interfaceaudio()
{
    delete ui;
}

void interfaceaudio::on_pushButton_Avant_clicked()
{
    qint64 currentPosition = player->position();

    // Rewind by 10 seconds (10000 milliseconds)
    qint64 newPosition = currentPosition - 10000;

    // Ensure we don't go below 0 (start of the video)
    if (newPosition < 0)
        newPosition = 0;
    player->setPosition(newPosition);
}

void interfaceaudio::on_pushButton_Play_clicked()
{
    player->play();
}


void interfaceaudio::on_pushButton_Pause_clicked()
{
    player->pause();
}


void interfaceaudio::on_pushButton_Apres_clicked()
{
    qint64 currentPosition = player->position();

    // Advance by 10 seconds (10000 milliseconds)
    qint64 newPosition = currentPosition + 10000;

    // Set the new position
    player->setPosition(newPosition);
}


void interfaceaudio::on_horizontalSlider_son_actionTriggered(int action)
{
    int volume = ui->horizontalSlider_son->value();  // Récupère la valeur du slider
    audioOutput->setVolume(volume / 100.0);
}


void interfaceaudio::on_pushButton_SelectionnerAudio_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Sélectionner un Audio", "", "Audio (*.mp3 *.wav *.flac)");
    if (!fileName.isEmpty()) {
        player->setSource(QUrl::fromLocalFile(fileName));  // Assigner le fichier audio à la source
        player->play();  // Lancer la lecture audio
        qDebug() << fileName;  // Afficher le chemin du fichier sélectionné dans la console
    }

}

