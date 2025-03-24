#include "interfaceenregistrement.h"
#include "ui_interfaceenregistrement.h"

InterfaceEnregistrement::InterfaceEnregistrement(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::InterfaceEnregistrement)
{
    ui->setupUi(this);
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
    mediaRecorder = new QMediaRecorder(this);
    audioInput = new QAudioInput(this);
    captureSession.setAudioInput(audioInput);
    captureSession.setRecorder(mediaRecorder);


    rewindTimer = new QTimer(this);
    connect(rewindTimer, &QTimer::timeout, this, &InterfaceEnregistrement::rewindChrono);
    audioInput = new QAudioInput(this);
    // Création du média recorder
    mediaRecorder = new QMediaRecorder(this);
    captureSession.setAudioInput(audioInput);
    captureSession.setRecorder(mediaRecorder);

    isRewinding = false;
    totalSecondes = 0;
    speakButtonClicked = false;






    //Affichage des Images
    QPixmap imageSon(":/images/Son"); // Charge l'image
    if (imageSon.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageSon); // Crée une icône
        ui->pushButtonSon->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonSon->setIconSize(ui->pushButtonSon->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    QPixmap imagePasSurveiller(":/images/PasSurveiller"); // Charge l'image
    if (imagePasSurveiller.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imagePasSurveiller); // Crée une icône
        ui->pushButtonSurveiller->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonSurveiller->setIconSize(ui->pushButtonSurveiller->size());
    }
    QPixmap imageEnregistrer(":/images/Enregistrer"); // Charge l'image
    if (imageEnregistrer.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        qDebug() << "Image chargée avec succès !";
        QIcon icone(imageEnregistrer); // Crée une icône
        ui->pushButtonEnregistrer->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonEnregistrer->setIconSize(ui->pushButtonEnregistrer->size());
        qDebug() << "Icône définie sur le bouton.";
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
    if (mediaRecorder->recorderState() == QMediaRecorder::RecordingState) {
        qWarning() << "L'enregistrement est déjà en cours.";
        return;
    }

    if (QFile::exists(audioFilePath)) {
        QFile::remove(audioFilePath);
        qDebug() << "Ancien enregistrement supprimé.";
    }

    // Réinitialiser le chrono
    totalSecondes = 0;
    ui->labelChrono->setText("00:00:00");

    // Assurer que le MediaRecorder est prêt à enregistrer
    mediaRecorder->setOutputLocation(QUrl::fromLocalFile(audioFilePath));

    // Démarrer le chrono
    timer->start(1000);

    // Démarrer l'enregistrement
    mediaRecorder->record();
    isRecordingPaused = false;
    qDebug() << "Nouvel enregistrement démarré.";
}
void InterfaceEnregistrement::on_pushButtonPause_clicked()
{
    if (mediaRecorder->recorderState() == QMediaRecorder::RecordingState) {
        mediaRecorder->pause(); // Met en pause l'enregistrement
        isRecordingPaused = true;
        pausedTime = totalSecondes; // Sauvegarde le temps actuel
        timer->stop(); // Met en pause le chrono
        qDebug() << "Enregistrement et chrono mis en pause.";
    } else if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
        qDebug() << "Lecture mise en pause.";
    }
}
void InterfaceEnregistrement::on_pushButtonPlay_clicked()
{
    if (isRecordingPaused) {
        // Reprendre l'enregistrement
        mediaRecorder->record();
        isRecordingPaused = false;
        totalSecondes = pausedTime; // Reprend le chrono là où on l'avait arrêté
        timer->start(1000);  // Redémarrer le chrono
        qDebug() << "Reprise de l'enregistrement et du chrono.";
        return;
    }

    if (!player) return;

    player->setSource(QUrl::fromLocalFile(audioFilePath));

    if (player->playbackState() == QMediaPlayer::PausedState) {
        player->play();
        totalSecondes = pausedTime; // Reprend là où on s'était arrêté
        timer->start(1000);
        qDebug() << "Reprise de la lecture et du chrono.";
    } else if (player->playbackState() == QMediaPlayer::StoppedState) {
        player->setPosition(0);
        player->play();
        qDebug() << "Lecture redémarrée depuis le début.";
    }

}
void InterfaceEnregistrement::on_pushButtonClear_clicked()
{
    // Arrêter l'enregistrement s'il est en cours
    if (mediaRecorder->recorderState() == QMediaRecorder::RecordingState) {
        mediaRecorder->stop();
        qDebug() << "Enregistrement arrêté.";
    }

    // Arrêter le lecteur s'il joue l'audio
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->stop();
        qDebug() << "Lecture stoppée.";
    }

    // Supprimer le fichier enregistré
    if (QFile::exists(audioFilePath)) {
        QFile::remove(audioFilePath);
        qDebug() << "Enregistrement supprimé.";
    }

    // Réinitialiser les variables
    totalSecondes = 0;
    ui->labelChrono->setText("00:00:00");
    speakButtonClicked = false;

    qDebug() << "Tout a été réinitialisé.";
}

void InterfaceEnregistrement::on_pushButtonSon_clicked()
{
    // Création de la fenêtre popup
    QDialog popup(this);
    popup.setWindowTitle("Réglages du Son");
    popup.setModal(true);  // Bloque l'interaction avec la fenêtre principale


    // Création des sliders
    QSlider *slider1 = new QSlider(Qt::Vertical);
    slider1->setRange(0, 100);
    slider1->setValue(50);  // Valeur par défaut

    // Création des labels
    QLabel *label1 = new QLabel("Son");

    // Bouton de fermeture
    QPushButton *closeButton = new QPushButton("Fermer");

    // Layout de la popup
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Layout pour les sliders et les labels à mettre horizontalement
    QHBoxLayout *slidersLayout = new QHBoxLayout;
    slidersLayout->addWidget(label1);
    slidersLayout->addWidget(slider1);

    // Ajouter le layout des sliders et labels à celui principal
    mainLayout->addLayout(slidersLayout);
    mainLayout->addWidget(closeButton);

    // Appliquer le layout principal à la popup
    popup.setLayout(mainLayout);

    // Connexion du bouton de fermeture
    QObject::connect(closeButton, &QPushButton::clicked, &popup, &QDialog::accept);

    // Affichage de la popup
    popup.exec();
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
    if (player && player->playbackState() == QMediaPlayer::PlayingState) {
        qint64 newPosition = player->position() + 5000; // Avancer de 5 secondes
        if (newPosition < player->duration()) {
            player->setPosition(newPosition);
            qDebug() << "Avancé de 5 secondes.";
        }
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



void InterfaceEnregistrement::on_pushButtonEnregistrer_clicked()
{
    qDebug() << "Bouton Enregistrer cliqué";
}

