#include "interfaceaudioco.h"
#include "ui_interfaceaudioco.h"
#include "volumecontroldialog.h"
#include <QPixmap>
#include <QIcon>

InterfaceAudioCO::InterfaceAudioCO(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterfaceAudioCO)
{
    ui->setupUi(this);
    ui->labelAppelProf->hide();

    this->setWindowTitle("Interface Audio CO");
    setFixedSize(800, 480); // Remplacez 800 et 480 par la largeur et la hauteur souhaitées

    // *** Code pour l'image ***
    QPixmap image(":/Image/AppelProf"); // Charge l'image
    if (image.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image); // Crée une icône
        ui->pushButtonAppelProf->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonAppelProf->setIconSize(ui->pushButtonAppelProf->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image2(":/Image/Son"); // Charge l'image
    if (image.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image2); // Crée une icône
        ui->pushButtonSon->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonSon->setIconSize(ui->pushButtonSon->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    // *** Fin du code pour l'image ***


}



void InterfaceAudioCO::on_pushButtonAppelProf_clicked()
{

    // Faire apparaître le label instantanément
    ui->labelAppelProf->show();
    qWarning() << "Label affiche";
}
InterfaceAudioCO::~InterfaceAudioCO()
{
    delete ui;
}

void InterfaceAudioCO::on_pushButtonSon_clicked()
{
    VolumeControlDialog volumeDialog(this);
    volumeDialog.exec();
}

