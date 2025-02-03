#include "interfaceaudio.h"
#include "ui_interfaceaudio.h"
#include <QAudioOutput>
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

}


void InterfaceAudio::on_pushButton_Play_clicked()
{

}


void InterfaceAudio::on_pushButton_Pause_clicked()
{

}

