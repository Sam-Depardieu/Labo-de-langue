#include "interfaceenregistrement.h"
#include "ui_interfaceenregistrement.h"
#include "volumecontroldialog.h"
#include <QTimer>

InterfaceEnregistrement::InterfaceEnregistrement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterfaceEnregistrement),
    pauseClickCount(0)
{
    ui->setupUi(this);
    ui->labelAppelProf->hide();


    this->setWindowTitle("Interface Enregistrement");  // Changez "Interface Enregistrement" par le titre désiré
    setFixedSize(800, 480); // Remplacez 800 et 480 par la largeur et la hauteur souhaitées
    connect(ui->pushButtonPause, &QPushButton::clicked, this, &InterfaceEnregistrement::on_pushButtonPause_clicked);

    QPixmap image(":/Image/Son"); // Charge l'image
    if (image.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image); // Crée une icône
        ui->pushButtonSon->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonSon->setIconSize(ui->pushButtonSon->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image2(":/Image/Favoris"); // Charge l'image
    if (image2.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image2); // Crée une icône
        ui->pushButtonFavoris->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonFavoris->setIconSize(ui->pushButtonFavoris->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image3(":/Image/Signet"); // Charge l'image
    if (image3.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image3); // Crée une icône
        ui->pushButtonSignet->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonSignet->setIconSize(ui->pushButtonSignet->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image4(":/Image/PasSurveiller"); // Charge l'image
    if (image4.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image4); // Crée une icône
        ui->pushButtonSurveiller->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonSurveiller->setIconSize(ui->pushButtonSurveiller->size());
    }
    QPixmap image5(":/Image/RevenirArriere"); // Charge l'image
    if (image5.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image5); // Crée une icône
        ui->pushButtonRetourArriere->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonRetourArriere->setIconSize(ui->pushButtonRetourArriere->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image6(":/Image/Pause"); // Charge l'image
    if (image6.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image6); // Crée une icône
        ui->pushButtonPause->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonPause->setIconSize(ui->pushButtonPause->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image7(":/Image/Avancer"); // Charge l'image
    if (image7.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image7); // Crée une icône
        ui->pushButtonAvancer->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonAvancer->setIconSize(ui->pushButtonAvancer->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image8(":/Image/Enregistrement"); // Charge l'image
    if (image8.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image8); // Crée une icône
        ui->pushButtonSpeak->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonSpeak->setIconSize(ui->pushButtonSpeak->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image9(":/Image/Start"); // Charge l'image
    if (image9.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image9); // Crée une icône
        ui->pushButtonPlay->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonPlay->setIconSize(ui->pushButtonPlay->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image10(":/Image/RevenirALaPhrasePrecedente"); // Charge l'image
    if (image10.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image10); // Crée une icône
        ui->pushButtonRevenirALaPhrasePrecedente->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonRevenirALaPhrasePrecedente->setIconSize(ui->pushButtonRevenirALaPhrasePrecedente->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image11(":/Image/Repeter"); // Charge l'image
    if (image11.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image11); // Crée une icône
        ui->pushButtonRepeter->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonRepeter->setIconSize(ui->pushButtonRepeter->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image12(":/Image/Effacer"); // Charge l'image
    if (image12.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image12); // Crée une icône
        ui->pushButtonClear->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonClear->setIconSize(ui->pushButtonClear->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image13(":/Image/AppelProf"); // Charge l'image
    if (image13.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image13); // Crée une icône
        ui->pushButtonAppelProf->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonAppelProf->setIconSize(ui->pushButtonAppelProf->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
}

void InterfaceEnregistrement::on_pushButtonSon_clicked()
{
    VolumeControlDialog volumeDialog(this);
    volumeDialog.exec();
}

InterfaceEnregistrement::~InterfaceEnregistrement()
{
    delete ui;
}
void InterfaceEnregistrement::on_pushButtonAppelProf_clicked()
{

    // Faire apparaître le label instantanément
    ui->labelAppelProf->show();
    qWarning() << "Label affiche";
}
void InterfaceEnregistrement::on_pushButtonSpeak_clicked()
{
    if (!speakButtonClicked) {
        // Démarrer le chronomètre
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &InterfaceEnregistrement::updateChrono);

        timer->start(1000); // Le chronomètre se déclenche toutes les secondes
        initialSecondes = 0;

        // Afficher le label et démarrer l'animation (si tu en as une)
        ui->labelChrono->show();
        // ... (code pour l'animation si nécessaire)

        // Désactiver le bouton
        ui->pushButtonSpeak->setEnabled(false);

        // Mettre à jour l'état du booléen
        speakButtonClicked = true;
    }
}


void InterfaceEnregistrement::updateChrono()
{
    static int totalSecondes = 0;
    totalSecondes++;

    int heures = totalSecondes / 3600;
    int minutes = (totalSecondes % 3600) / 60;
    int secondes = totalSecondes % 60;

    ui->labelChrono->setText(QString::number(heures).rightJustified(2, '0') + ":" +
                             QString::number(minutes).rightJustified(2, '0') + ":" +
                             QString::number(secondes).rightJustified(2, '0'));
}

void InterfaceEnregistrement::on_pushButtonPause_clicked()
{
    pauseClickCount++;

    if (pauseClickCount % 2 == 0) {
        // Nombre pair de clics, redémarrer le chronomètre
        if (!timer->isActive()) {
            timer->start(1000); // Redémarrer le chronomètre
            qDebug() << "Chronomètre redémarré";
        }
    } else {
        // Nombre impair de clics, arrêter le chronomètre
        if (timer->isActive()) {
            timer->stop();
            qDebug() << "Chronomètre arrêté";
        }
    }
}



void InterfaceEnregistrement::on_pushButtonRetourArriere_clicked()
{
    initialSecondes = 0;
    ui->labelChrono->setText("00:00:00");
}
void InterfaceEnregistrement::on_pushButtonPlay_clicked()
{
    if (!timer->isActive()) { // Vérifie si le timer est arrêté
        timer->start(1000);  // Redémarre le chronomètre
        qWarning() << "Chrono redémarré";
    } else {
        qWarning() << "Le chrono est déjà en cours";
    }
}

