#include "interfaceenregistrement.h"
#include "ui_interfaceenregistrement.h"

InterfaceEnregistrement::InterfaceEnregistrement(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::InterfaceEnregistrement)
{
    ui->setupUi(this);

    //Pour cacher quelque chose
    ui->labelAppelProf->hide();

    //Pour fixer la taille de la page et le titre
    setFixedSize(800,480);
    this->setWindowTitle("Page d'Enregistrement");

    // Initialisation des autres composants et variables
    mediaRecorder = new QMediaRecorder(this);  // Remplacer audioRecorder par mediaRecorder
    player = new QMediaPlayer(this);           // Initialisation correcte de QMediaPlayer
    audioInput = new QAudioInput(this);      // Instancier QAudioOutput ici
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);       // Configurer QAudioOutput pour le player

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &InterfaceEnregistrement::updateChrono);

    rewindTimer = new QTimer(this);
    connect(rewindTimer, &QTimer::timeout, this, &InterfaceEnregistrement::rewindChrono);

    isRewinding = false;
    totalSecondes = 0;
    speakButtonClicked = false;

    // Configuration de l'enregistrement
    audioFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/audio.mp3";  // Changé en mp3
    mediaRecorder->setOutputLocation(QUrl::fromLocalFile(audioFilePath));

    // Définir les paramètres d'enregistrement avec la nouvelle API Qt 6
    QMediaFormat format;
    format.setFileFormat(QMediaFormat::FileFormat::MP3);
    format.setAudioCodec(QMediaFormat::AudioCodec::MP3);

    mediaRecorder->setMediaFormat(format);
    mediaRecorder->setQuality(QMediaRecorder::HighQuality);
    mediaRecorder->setAudioSampleRate(44100);
    mediaRecorder->setAudioBitRate(128000);
    mediaRecorder->setAudioChannelCount(2);

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

    // Connexions des signaux
    connect(mediaRecorder, &QMediaRecorder::recorderStateChanged, this, &InterfaceEnregistrement::onRecorderStateChanged);
    connect(mediaRecorder, &QMediaRecorder::errorOccurred, this, &InterfaceEnregistrement::onRecorderErrorOccurred);
}

InterfaceEnregistrement::~InterfaceEnregistrement()
{
    delete ui;
    delete mediaRecorder;
    delete player;  // N'oublie pas de supprimer les objets alloués dynamiquement
    delete audioInput;  // Libérer l'objet QAudioOutput
    delete timer;
    delete rewindTimer;  // Nettoyer rewindTimer
}

void InterfaceEnregistrement::on_pushButtonSpeak_clicked()
{
    if (!speakButtonClicked) {
        if (!timer->isActive()) {
            // Démarrer l'enregistrement
            totalSecondes = 0; // Réinitialiser le chronomètre
            timer->start(1000);
            ui->labelChrono->setText("00:00:00");
            ui->labelChrono->show();

            // Démarrer l'enregistrement
            qDebug() << "Enregistrement démarré";

            // Démarrer le QMediaRecorder
            mediaRecorder->record();  // Utiliser mediaRecorder ici
            speakButtonClicked = true;
        } else {
            qDebug() << "L'enregistrement est déjà en cours";
        }
    } else {
        qDebug() << "L'enregistrement est déjà terminé, vous pouvez jouer le fichier.";
    }
}

void InterfaceEnregistrement::on_pushButtonPause_clicked()
{
    if (timer->isActive()) {
        timer->stop();
        qDebug() << "Chronomètre arrêté";
    }
}
void InterfaceEnregistrement::on_pushButtonPlay_clicked()
{
    if (mediaRecorder->recorderState() != QMediaRecorder::RecordingState) {
        mediaRecorder->record();
        timer->start();
        qDebug() << "Enregistrement démarré";
    }
}


void InterfaceEnregistrement::on_pushButtonClear_clicked()
{
    // Arrêter l'enregistrement
    if (mediaRecorder->recorderState() == QMediaRecorder::RecordingState ||
        mediaRecorder->recorderState() == QMediaRecorder::PausedState) {
        mediaRecorder->stop();
        qDebug() << "Enregistrement arrêté et effacé";
    }

    // Arrêter le chronomètre
    if (timer->isActive()) {
        timer->stop();
        qDebug() << "Chronomètre arrêté";
    }

    // Réinitialiser le chronomètre
    timer->setInterval(0);
    timer->start();

    // Optionnel : Effacer les fichiers d'enregistrement
    // Assurez-vous d'avoir les permissions nécessaires pour supprimer les fichiers
    QFile::remove("path/to/your/recording/file.mp4");
}

void InterfaceEnregistrement::on_pushButtonSon_clicked()
{
    if (player->position() / 1000 >= totalSecondes) {
        player->stop();
        qDebug() << "Lecture arrêtée car elle a dépassé le temps du chronomètre";
    }
}

void InterfaceEnregistrement::on_pushButtonRetourArriere_clicked()
{
    if (totalSecondes == 0 && lastRecordedTime > 0) {
        totalSecondes = lastRecordedTime;  // Restaurer le dernier temps enregistré
        int heures = totalSecondes / 3600;
        int minutes = (totalSecondes % 3600) / 60;
        int secondes = totalSecondes % 60;

        ui->labelChrono->setText(QString::number(heures).rightJustified(2, '0') + ":" +
                                 QString::number(minutes).rightJustified(2, '0') + ":" +
                                 QString::number(secondes).rightJustified(2, '0'));

        qDebug() << "Retour au dernier temps enregistré : " << totalSecondes;
    } else if (totalSecondes > 0 && !isRewinding) {
        isRewinding = true;
        rewindTimer->start(100);  // Défile rapidement
        qDebug() << "Retour arrière en cours";
    }
}
void InterfaceEnregistrement::on_pushButtonAvancer_clicked()
{
    if (totalSecondes > 0 && !isRewinding) {
        isRewinding = true;
        rewindTimer->start(100); // Défile rapidement (toutes les 100 ms)
    }
}


void InterfaceEnregistrement::updateChrono()
{
    if (isRewinding) {
        return; // Ne pas mettre à jour le chrono pendant le retour arrière
    }

    totalSecondes++;

    int heures = totalSecondes / 3600;
    int minutes = (totalSecondes % 3600) / 60;
    int secondes = totalSecondes % 60;

    ui->labelChrono->setText(QString::number(heures).rightJustified(2, '0') + ":" +
                             QString::number(minutes).rightJustified(2, '0') + ":" +
                             QString::number(secondes).rightJustified(2, '0'));
}

void InterfaceEnregistrement::rewindChrono()
{
    if (totalSecondes > 1) {
        lastRecordedTime = totalSecondes;  // Sauvegarde correcte du dernier temps avant 0
    }

    if (totalSecondes > 0) {
        totalSecondes--;
        int heures = totalSecondes / 3600;
        int minutes = (totalSecondes % 3600) / 60;
        int secondes = totalSecondes % 60;

        ui->labelChrono->setText(QString::number(heures).rightJustified(2, '0') + ":" +
                                 QString::number(minutes).rightJustified(2, '0') + ":" +
                                 QString::number(secondes).rightJustified(2, '0'));
    } else {
        qDebug() << "Chrono à zéro, dernier temps enregistré : " << lastRecordedTime;
        rewindTimer->stop();
        isRewinding = false;
    }
}

void InterfaceEnregistrement::on_pushButtonAppelProf_clicked()
{
    ui->pushButtonAppelProf->setStyleSheet("QPushButton { background-color: none; border: none; }");
    // Faire apparaître le label instantanément
    ui->labelAppelProf->show();
    qWarning() << "Label Appel Prof affiche";

    QUdpSocket *udpSocket = new QUdpSocket(this);

    QJsonObject message;
    message["type"] = "call_request";
    message["id_eleve"] = studentId;

    QJsonDocument doc(message);
    QByteArray data = doc.toJson();

    QHostAddress profAddress("192.168.88.216");  // Adresse IP de l'appli Prof
    quint16 profPort = 45454;  // Port d'écoute de l'appli Prof

    udpSocket->writeDatagram(data, profAddress, profPort);
}

// Ajouter ces deux fonctions nécessaires pour Qt 6
void InterfaceEnregistrement::checkPlaybackPosition(qint64 position)
{
    // Cette méthode surveille la position de lecture
    if (position / 1000 >= totalSecondes) {
        player->stop();
        qDebug() << "Lecture arrêtée car elle a dépassé le temps du chronomètre";
    }
}

void InterfaceEnregistrement::onRecorderStateChanged(QMediaRecorder::RecorderState state)
{
    // Gérer les changements d'état de l'enregistreur
    switch (state) {
    case QMediaRecorder::RecordingState:
        qDebug() << "État de l'enregistreur: Enregistrement en cours";
        break;
    case QMediaRecorder::PausedState:
        qDebug() << "État de l'enregistreur: En pause";
        break;
    case QMediaRecorder::StoppedState:
        qDebug() << "État de l'enregistreur: Arrêté";
        break;
    }
}

void InterfaceEnregistrement::onRecorderErrorOccurred(QMediaRecorder::Error error, const QString &errorString)
{
    // Gérer les erreurs d'enregistrement
    qDebug() << "Erreur d'enregistrement:" << errorString;
}


