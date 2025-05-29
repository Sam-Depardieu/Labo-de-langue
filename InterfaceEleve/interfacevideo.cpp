#include "interfacevideo.h"
#include "mainwindow.h"
#include "ui_interfacevideo.h"
#include "mainwindow.h"
#include <QAudioOutput>
#include <QStandardPaths>

InterfaceVideo::InterfaceVideo(bool co, MainWindow *parentWindow, QWidget *parent)
    : QDialog(parent)
    , mainWindow(parentWindow)  // 🔹 Initialisation de player
    , ui(new Ui::InterfaceVideo)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , CO(co)
    , coMode(co)
{
    ui->setupUi(this);
    if (CO) {
        ui->pushButton_Avant10->setEnabled(false);
        ui->pushButton_Pause->setEnabled(false);
        ui->pushButton_Apres10->setEnabled(false);
        ui->horizontalSlider->setEnabled(false);
        ui->pushButtonReset->setVisible(true);
    } else {
        ui->pushButton_Avant10->setEnabled(true);
        ui->pushButton_Pause->setEnabled(true);
        ui->pushButton_Apres10->setEnabled(true);
        ui->horizontalSlider->setEnabled(true);
        ui->pushButtonReset->setVisible(false);
    }
    setFixedSize(800,480);
    this->setWindowTitle("Page de Video");



    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    // Configuration de la scène pour la graphicsView existante
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("background: black; border: none;");
    ui->graphicsView->setFrameShape(QFrame::NoFrame);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Création de l'élément vidéo
    videoItem = new QGraphicsVideoItem();
    scene->addItem(videoItem);
    player->setVideoOutput(videoItem);

    // Taille initiale
    videoItem->setSize(ui->graphicsView->viewport()->size());

    // Mise à jour de la taille quand le viewport change

    // Pour afficher un slider ou widget par-dessus la vidéo :
    //ui->verticalSlider_sonVideo->setParent(ui->graphicsView->viewport());
    //ui->verticalSlider_sonVideo->move(740, 20);  // Ajuste selon ton design
    ui->verticalSlider_sonVideo->setVisible(false); // Cacher au démarrage

    ui->verticalSlider_sonVideo->raise();


    connect(player,&QMediaPlayer::durationChanged,this,[=](qint64 duration){
        ui->horizontalSlider->setRange(0, static_cast<int>(duration));
    });

    connect(player, &QMediaPlayer::positionChanged, this, [=](qint64 position) {
        ui->horizontalSlider->setValue(static_cast<int>(position));
    });

    setFixedSize(800,480);

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
    QPixmap imageReset(":/images/Repeter");
    if (imageReset.isNull()){
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageReset); // Crée une icône
        ui->pushButtonReset->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonReset->setIconSize(ui->pushButtonReset->size());
    };
    QPixmap sonVid(":/images/sonVid"); // Charge l'image
    if (sonVid.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(sonVid); // Crée une icône
        ui->pushButton_Son->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton_Son->setIconSize(ui->pushButton_Son->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    QPixmap AppelProf(":/images/CallProf"); // Charge l'image
    if (AppelProf.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(AppelProf); // Crée une icône
        ui->pushButtonAppelProf->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonAppelProf->setIconSize(ui->pushButtonAppelProf->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }

    ui->verticalSlider_sonVideo->setVisible(false);
    ui->verticalSlider_sonVideo->raise();

    ui->pushButton_Pause->setVisible(true);
    ui->pushButton_Play->setVisible(false);
    ui->chronoLabel->setVisible(true);

    remainingTime = parentWindow->getTime();

    udpSocketCMD.bind(QHostAddress::Any, cmdPort);
    connect(&udpSocketCMD, &QUdpSocket::readyRead, this, &InterfaceVideo::receiveCmd);

    // Initialisation des timers
    chronoTimer = new QTimer(this);
    connect(chronoTimer, &QTimer::timeout, this, &InterfaceVideo::updateChronoLabel);

    clignotementTimer = new QTimer(this);
    connect(clignotementTimer, &QTimer::timeout, this, &InterfaceVideo::faireClignoterLabel);

    clignotementEtat = false;

    // Style initial du label
    ui->chronoLabel->setVisible(true);
    ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: white; border: 2px solid white; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");

    // Affichage du temps initial et démarrage du chrono
    if (remainingTime.isValid() && remainingTime != QTime(0, 0)) {
        ui->chronoLabel->setText(remainingTime.toString("mm:ss"));
        chronoTimer->start(1000);
    } else {
        ui->chronoLabel->setText("00:00");
    }


    if (mainWindow->getNomFichier() != nullptr) {
        player->setSource(QUrl::fromLocalFile(mainWindow->getSessionPATH()+ "/" + mainWindow->getNomFichier()));  // Charger et lire l'audio
        player->play();
        qDebug() << "Fichier sélectionné : " << mainWindow->getSessionPATH() + "/" + mainWindow->getNomFichier();
    }
}

void InterfaceVideo::receiveCmd() {
    while (udpSocketCMD.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketCMD.pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udpSocketCMD.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString response = QString::fromUtf8(datagram).trimmed();
        qDebug() << "📢 Message reçu de" << sender.toString() << ":" << response;

        if(response == "pause") on_pushButton_Pause_clicked();
        else if (response == "lecture") on_pushButton_Play_clicked();
    }
}

void InterfaceVideo::faireClignoterLabel()
{
    clignotementEtat = !clignotementEtat;
    if (clignotementEtat)
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: red; border: 2px solid red; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
    else
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: white; border: 2px solid white; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
}

void InterfaceVideo::updateChronoLabel()
{
    remainingTime = remainingTime.addSecs(-1);

    ui->chronoLabel->setText(remainingTime.toString("mm:ss"));

    if (remainingTime.minute() == 0 && remainingTime.second() < 31) {
        if (!clignotementTimer->isActive())
            clignotementTimer->start(500); // clignote toutes les 500 ms
    }

    if (remainingTime == QTime(0, 0)) {
        chronoTimer->stop();
        ui->chronoLabel->setText("00:00");
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: red; border: 2px solid red; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
        QMessageBox::information(this, "Fin de l'activité", "Pensez à mettre fin à l'activité en cours !");
    }
}


InterfaceVideo::~InterfaceVideo()
{
    delete ui;
}
void InterfaceVideo::on_pushButton_Avant10_clicked()
{
    animateButtonClick(ui->pushButton_Avant10);
    qint64 currentPosition = player->position();
    qint64 newPosition = currentPosition - 10000;
    if (newPosition < 0)
        newPosition = 0;
    player->setPosition(newPosition);
}
void InterfaceVideo::on_pushButton_Apres10_clicked()
{
    animateButtonClick(ui->pushButton_Apres10);
    qint64 currentPosition = player->position();
    qint64 newPosition = currentPosition + 10000;
    player->setPosition(newPosition);
}

void InterfaceVideo::setVideoPause(bool pause)
{
    if (pause) {
        player->pause();
    } else {
        player->play();
    }

    ui->pushButton_Pause->setVisible(!pause);
    ui->pushButton_Play->setVisible(pause);
}

void InterfaceVideo::on_pushButton_Play_clicked()
{
    setVideoPause(false); // Jouer
}

void InterfaceVideo::on_pushButton_Pause_clicked()
{
    setVideoPause(true); // Mettre en pause
}

/*void InterfaceVideo::on_horizontalSlider_sonVideo_actionTriggered(int action)
{
    int volume = ui->horizontalSlider_sonVideo->value();  // Récupère la valeur du slider
    audioOutput->setVolume(volume / 100.0);
}*/

void InterfaceVideo::on_verticalSlider_sonVideo_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);
}

void InterfaceVideo::closeEvent(QCloseEvent *event)
{
    if (player) {
        player->stop();
        delete player;
        player = nullptr;
    }
    event->accept();
}
void InterfaceVideo::on_horizontalSlider_sliderReleased()
{
    int position = ui->horizontalSlider->value();  // récupère la position du curseur
    player->setPosition(position);
}
void InterfaceVideo::animateButtonClick(QPushButton* btn) {
    // 1) on prend la géométrie d'origine
    const QRect orig = btn->geometry();
    const QRect small = orig.adjusted(5, 5, -5, -5);

    // 2) animation pour rétrécir
    auto *shrink = new QPropertyAnimation(btn, "geometry");
    shrink->setDuration(50);
    shrink->setStartValue(orig);
    shrink->setEndValue(small);

    // 3) animation pour réagrandir
    auto *expand = new QPropertyAnimation(btn, "geometry");
    expand->setDuration(50);
    expand->setStartValue(small);
    expand->setEndValue(orig);

    // 4) on les enchaîne
    auto *seq = new QSequentialAnimationGroup(btn);
    seq->addAnimation(shrink);
    seq->addAnimation(expand);

    // 5) on lance et on supprime l’objet à la fin
    seq->start(QAbstractAnimation::DeleteWhenStopped);
}

void InterfaceVideo::on_pushButtonReset_clicked()
{
    // 1) Si on a déjà reset 3 fois, on bloque
    if (resetCount >= maxResets) {
        QMessageBox::warning(this,
                             "Limite atteinte",
                             "Vous ne pouvez réinitialiser l'audio que 3 fois.");
        return;
    }

    // 2) N'autoriser le reset que si la lecture est terminée
    if (player->playbackState() != QMediaPlayer::StoppedState) {
        QMessageBox::information(this,
                                 "Lecture en cours",
                                 "Veuillez attendre la fin de la lecture avant de réinitialiser.");
        return;
    }

    // 3) On remet la position à 0 et on relance
    player->setPosition(0);
    player->play();

    // 4) Comptabiliser un reset, et informer l’utilisateur
    resetCount++;
    QMessageBox::information(this,
                             "Réinitialisation",
                             QString("Remise à zéro effectuée (%1/%2).")
                                 .arg(resetCount)
                                 .arg(maxResets));
}
void InterfaceVideo::on_pushButtonAppelProf_clicked()
{
    ui->pushButtonAppelProf->setEnabled(false); // désactive le bouton
    ui->pushButtonAppelProf->setStyleSheet("border:1px solid white; border-radius:20px;");

    // Récupérer l'adresse IP du professeur depuis MainWindow
    QString ipProf = mainWindow->getIpProf();

    // Envoyer le message "help" à l'adresse IP du professeur
    mainWindow->sendCommandToProf(ipProf, 5557, "help");
    qDebug() << "Appel prof envoyé à l'adresse IP : " << ipProf;
}
void InterfaceVideo::on_pushButton_Son_clicked()
{
    // 1. Afficher ou cacher le slider de volume
    bool visible = ui->verticalSlider_sonVideo->isVisible();
    ui->verticalSlider_sonVideo->setVisible(!visible);

    // 2. Si on l'affiche pour la première fois, on initialise
    if (!visible) {
        ui->verticalSlider_sonVideo->setRange(0, 100);

        // 🔄 Corrigé : récupérer correctement le volume actuel
        int volume = static_cast<int>(audioOutput->volume() * 50);
        ui->verticalSlider_sonVideo->setValue(volume);

        // 3. Connecter une seule fois le signal du slider
        static bool sliderConnected = false;
        if (!sliderConnected) {
            connect(ui->verticalSlider_sonVideo, &QSlider::valueChanged, this, [=](int value) {
                audioOutput->setVolume(value / 100.0);
                qDebug() << "Volume réglé à :" << value;
            });
            sliderConnected = true;
        }
    }
}


