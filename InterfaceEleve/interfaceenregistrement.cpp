#include "interfaceenregistrement.h"
#include "qstandardpaths.h"
#include "qtimer.h"
#include "ui_interfaceenregistrement.h"

InterfaceEnregistrement::InterfaceEnregistrement(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceEnregistrement)
{
    ui->setupUi(this);
    //Pour cacher quelque chose
    ui->labelAppelProf->hide();

    //Pour fixer la taille de la page et le titre
    setFixedSize(800,480);
    this->setWindowTitle("Page d'Enregistrement");

    // Initialiser les variables
    timer = new QTimer(this);
    rewindTimer = new QTimer(this);
    player = new QMediaPlayer(this);
    isRewinding = false;
    speakButtonClicked = false;
    totalSecondes = 0;
    pausedSecondes = 0;
    isPaused = false;


    //Affichage des Images
    QPixmap imageSon(":/images/Son"); // Charge l'image
    if (imageSon.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageSon); // Crée une icône
        ui->pushButtonSon->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonSon->setIconSize(ui->pushButtonSon->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    QPixmap imageFavoris(":/images/Favoris"); // Charge l'image
    if (imageFavoris.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageFavoris); // Crée une icône
        ui->pushButtonFavoris->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonFavoris->setIconSize(ui->pushButtonFavoris->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    QPixmap imageSignet(":/images/Signet"); // Charge l'image
    if (imageSignet.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageSignet); // Crée une icône
        ui->pushButtonSignet->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonSignet->setIconSize(ui->pushButtonSignet->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    QPixmap imagePasSurveiller(":/images/PasSurveiller"); // Charge l'image
    if (imagePasSurveiller.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imagePasSurveiller); // Crée une icône
        ui->pushButtonSurveiller->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonSurveiller->setIconSize(ui->pushButtonSurveiller->size());
    }

    QPixmap imageRevenirArriere(":/images/RevenirArriere"); // Charge l'image
    if (imageRevenirArriere.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageRevenirArriere); // Crée une icône
        ui->pushButtonRetourArriere->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonRetourArriere->setIconSize(ui->pushButtonRetourArriere->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    QPixmap imagePause(":/images/Pause"); // Charge l'image
    if (imagePause.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imagePause); // Crée une icône
        ui->pushButtonPause->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonPause->setIconSize(ui->pushButtonPause->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    QPixmap imageAvancer(":/images/Avancer"); // Charge l'image
    if (imageAvancer.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageAvancer); // Crée une icône
        ui->pushButtonAvancer->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonAvancer->setIconSize(ui->pushButtonAvancer->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    QPixmap imageEnregistrement(":/images/Enregistrement"); // Charge l'image
    if (imageEnregistrement.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageEnregistrement); // Crée une icône
        ui->pushButtonSpeak->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonSpeak->setIconSize(ui->pushButtonSpeak->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    QPixmap imagePlay(":/images/Play"); // Charge l'image
    if (imagePlay.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imagePlay); // Crée une icône
        ui->pushButtonPlay->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonPlay->setIconSize(ui->pushButtonPlay->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    QPixmap imageRevenirALaPhrasePrecedente(":/images/RevenirALaPhrasePrecedente"); // Charge l'image
    if (imageRevenirALaPhrasePrecedente.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageRevenirALaPhrasePrecedente); // Crée une icône
        ui->pushButtonRevenirALaPhrasePrecedente->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonRevenirALaPhrasePrecedente->setIconSize(ui->pushButtonRevenirALaPhrasePrecedente->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    QPixmap imageRepeter(":/images/Repeter"); // Charge l'image
    if (imageRepeter.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageRepeter); // Crée une icône
        ui->pushButtonRepeter->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonRepeter->setIconSize(ui->pushButtonRepeter->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    QPixmap imageEffacer(":/images/Effacer"); // Charge l'image
    if (imageEffacer.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageEffacer); // Crée une icône
        ui->pushButtonClear->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonClear->setIconSize(ui->pushButtonClear->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imageAppelProf(":/images/AppelProf"); // Charge l'image
    if (imageAppelProf.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageAppelProf); // Crée une icône
        ui->pushButtonAppelProf->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonAppelProf->setIconSize(ui->pushButtonAppelProf->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    connect(rewindTimer, &QTimer::timeout, this, &InterfaceEnregistrement::updateChrono);
}

InterfaceEnregistrement::~InterfaceEnregistrement()
{
    delete ui;
}

void InterfaceEnregistrement::on_pushButtonSon_clicked()
{

}


void InterfaceEnregistrement::on_pushButtonSignet_clicked()
{

}


void InterfaceEnregistrement::on_pushButtonFavoris_clicked()
{

}


void InterfaceEnregistrement::on_pushButtonRevenirALaPhrasePrecedente_clicked()
{

}


void InterfaceEnregistrement::on_pushButtonRepeter_clicked()
{

}


void InterfaceEnregistrement::on_pushButtonClear_clicked()
{

}


void InterfaceEnregistrement::on_pushButtonSurveiller_clicked()
{

}

void InterfaceEnregistrement::on_pushButtonRetourArriere_clicked()
{
    if (totalSecondes > 0 && !isRewinding) {
        isRewinding = true;
        rewindTimer->start(100); // Défile rapidement (toutes les 100 ms)
    }
}


void InterfaceEnregistrement::on_pushButtonPause_clicked()
{
    if (timer->isActive()) {
        timer->stop();
        qDebug() << "Chronomètre arrêté";
    }
}

void InterfaceEnregistrement::on_pushButtonSpeak_clicked()
{
    if (!speakButtonClicked) {
        // Démarrer le chrono
        connect(timer, &QTimer::timeout, this, &InterfaceEnregistrement::updateChrono);
        totalSecondes = 0; // Réinitialiser le chronomètre
        timer->start(1000);

        ui->labelChrono->setText("00:00:00"); // Initialiser le label du chronomètre à 0
        ui->labelChrono->show();
        ui->pushButtonSpeak->setEnabled(false);
        speakButtonClicked = true;

        // Simuler un enregistrement (mettre votre code d'enregistrement ici)
        audioFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/recording.wav";
        qDebug() << "Enregistrement sauvegardé à :" << audioFilePath;
    }
}

void InterfaceEnregistrement::on_pushButtonAvancer_clicked()
{

}





void InterfaceEnregistrement::on_pushButtonPlay_clicked()
{
    if (!isRewinding) { // Vérifie que le retour arrière est terminé
        if (!timer->isActive()) {
            timer->start(1000);
            qDebug() << "Chrono redémarré à partir de " << totalSecondes;

            // Lire l'audio enregistré depuis le début
            player->setSource(QUrl::fromLocalFile(audioFilePath));
            player->play();
        } else {
            qDebug() << "Le chrono est déjà en cours";
        }
    }
}

void InterfaceEnregistrement::on_pushButtonAppelProf_clicked()
{
    ui->pushButtonAppelProf->setStyleSheet("QPushButton { background-color: none; border: none; }");
    // Faire apparaître le label instantanément
    ui->labelAppelProf->show();
    qWarning() << "Label Appel Prof affiche";

}
void InterfaceEnregistrement::updateChrono()
{
    if (totalSecondes > 0 && isRewinding) {
        totalSecondes--;
    } else {
        totalSecondes++;
    }

    int heures = totalSecondes / 3600;
    int minutes = (totalSecondes % 3600) / 60;
    int secondes = totalSecondes % 60;

    ui->labelChrono->setText(QString::number(heures).rightJustified(2, '0') + ":" +
                             QString::number(minutes).rightJustified(2, '0') + ":" +
                             QString::number(secondes).rightJustified(2, '0'));

    if (totalSecondes == 0 && isRewinding) {
        rewindTimer->stop();
        isRewinding = false;
    }
}
