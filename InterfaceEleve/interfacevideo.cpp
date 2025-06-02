#include "interfacevideo.h"
#include "mainwindow.h"
#include "ui_interfacevideo.h"
#include "mainwindow.h"
#include <QAudioOutput>
#include <QStandardPaths>

InterfaceVideo::InterfaceVideo(bool co, MainWindow *parentWindow, QWidget *parent)
    : QDialog(parent)
    , mainWindow(parentWindow)
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

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("background: black; border: none;");
    ui->graphicsView->setFrameShape(QFrame::NoFrame);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    videoItem = new QGraphicsVideoItem();
    scene->addItem(videoItem);
    player->setVideoOutput(videoItem);

    // Taille initiale
    videoItem->setSize(ui->graphicsView->viewport()->size());

    //ui->verticalSlider_sonVideo->setParent(ui->graphicsView->viewport());
    //ui->verticalSlider_sonVideo->move(740, 20);  // Ajuste selon ton design
    ui->verticalSlider_sonVideo->setVisible(false);

    ui->verticalSlider_sonVideo->raise();


    connect(player,&QMediaPlayer::durationChanged,this,[=](qint64 duration){
        ui->horizontalSlider->setRange(0, static_cast<int>(duration));
    });

    connect(player, &QMediaPlayer::positionChanged, this, [=](qint64 position) {
        ui->horizontalSlider->setValue(static_cast<int>(position));
    });

    setFixedSize(800,480);

    this->setWindowTitle("Interface Vidéo");

    QPixmap imagePlay(":/images/Play");
    if (imagePlay.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imagePlay);
        ui->pushButton_Play->setIcon(icone);
        ui->pushButton_Play->setIconSize(ui->pushButton_Play->size());
    }
    QPixmap imagePause(":/images/Pause");
    if (imagePause.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imagePause);
        ui->pushButton_Pause->setIcon(icone);
        ui->pushButton_Pause->setIconSize(ui->pushButton_Pause->size());
    }
    QPixmap imageAvant10(":/images/Avant10");
    if (imageAvant10.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageAvant10);
        ui->pushButton_Avant10->setIcon(icone);
        ui->pushButton_Avant10->setIconSize(ui->pushButton_Avant10->size());
    }
    QPixmap imageApres10(":/images/Apres10");
    if (imageApres10.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageApres10);
        ui->pushButton_Apres10->setIcon(icone);
        ui->pushButton_Apres10->setIconSize(ui->pushButton_Apres10->size());
    }
    QPixmap imageReset(":/images/Repeter");
    if (imageReset.isNull()){
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageReset);
        ui->pushButtonReset->setIcon(icone);
        ui->pushButtonReset->setIconSize(ui->pushButtonReset->size());
    };
    QPixmap sonVid(":/images/sonVid");
    if (sonVid.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(sonVid);
        ui->pushButton_Son->setIcon(icone);
        ui->pushButton_Son->setIconSize(ui->pushButton_Son->size());
    }

    QPixmap AppelProf(":/images/CallProf");
    if (AppelProf.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(AppelProf);
        ui->pushButtonAppelProf->setIcon(icone);
        ui->pushButtonAppelProf->setIconSize(ui->pushButtonAppelProf->size());
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
    if (remainingTime.isValid() && remainingTime != QTime(0, 0)) {
        ui->chronoLabel->setText(remainingTime.toString("mm:ss"));
        chronoTimer->start(1000);
    } else {
        ui->chronoLabel->setText("00:00");
        ui->chronoLabel->setVisible(false);

    }


    if (mainWindow->getNomFichier() != nullptr) {
        player->setSource(QUrl::fromLocalFile(mainWindow->getSessionPATH()+ "/" + mainWindow->getNomFichier()));
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
            clignotementTimer->start(500);
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
    setVideoPause(false);
}

void InterfaceVideo::on_pushButton_Pause_clicked()
{
    setVideoPause(true);
}


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
    int position = ui->horizontalSlider->value();
    player->setPosition(position);
}
void InterfaceVideo::animateButtonClick(QPushButton* btn) {
    const QRect orig = btn->geometry();
    const QRect small = orig.adjusted(5, 5, -5, -5);

    auto *shrink = new QPropertyAnimation(btn, "geometry");
    shrink->setDuration(50);
    shrink->setStartValue(orig);
    shrink->setEndValue(small);

    auto *expand = new QPropertyAnimation(btn, "geometry");
    expand->setDuration(50);
    expand->setStartValue(small);
    expand->setEndValue(orig);

    auto *seq = new QSequentialAnimationGroup(btn);
    seq->addAnimation(shrink);
    seq->addAnimation(expand);

    seq->start(QAbstractAnimation::DeleteWhenStopped);
}

void InterfaceVideo::on_pushButtonReset_clicked()
{
    if (resetCount >= maxResets) {
        QMessageBox::warning(this,
                             "Limite atteinte",
                             "Vous ne pouvez réinitialiser l'audio que 3 fois.");
        return;
    }
    if (player->playbackState() != QMediaPlayer::StoppedState) {
        QMessageBox::information(this,
                                 "Lecture en cours",
                                 "Veuillez attendre la fin de la lecture avant de réinitialiser.");
        return;
    }
    player->setPosition(0);
    player->play();
    resetCount++;
    QMessageBox::information(this,
                             "Réinitialisation",
                             QString("Remise à zéro effectuée (%1/%2).")
                                 .arg(resetCount)
                                 .arg(maxResets));
}
void InterfaceVideo::on_pushButtonAppelProf_clicked()
{
    ui->pushButtonAppelProf->setEnabled(false);
    ui->pushButtonAppelProf->setStyleSheet("border:1px solid white; border-radius:20px;");
    if (!mainWindow) {
        qDebug() << "[InterfaceVideo] mainWindow est null, impossible d'envoyer le message";
        return;
    }

    QString ipProf = mainWindow->getIpProf(); // Récupérer l'adresse IP du professeur
    qDebug() << "[InterfaceVideo] Adresse IP prof récupérée :" << ipProf; // Log pour vérifier l'adresse IP du professeur
    if (ipProf.isEmpty()) {
        qDebug() << "[InterfaceVideo] IP Prof vide, envoi annulé";
        return;
    }

    quint16 port = 5557;
    QString message = "help"; // Message à envoyer

    mainWindow->sendCommandToProf(ipProf, port, message);
}
void InterfaceVideo::on_pushButton_Son_clicked()
{
    bool visible = ui->verticalSlider_sonVideo->isVisible();
    ui->verticalSlider_sonVideo->setVisible(!visible);
    if (!visible) {
        ui->verticalSlider_sonVideo->setRange(0, 100);
        int volume = static_cast<int>(audioOutput->volume() * 50);
        ui->verticalSlider_sonVideo->setValue(volume);
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


