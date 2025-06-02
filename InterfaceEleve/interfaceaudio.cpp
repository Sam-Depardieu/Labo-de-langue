#include "interfaceaudio.h"
#include "mainwindow.h"
#include "ui_interfaceaudio.h"
#include <QAudioOutput>
#include <QStandardPaths>
#include <QMediaRecorder>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QHostAddress>
#include <QDebug>

InterfaceAudio::InterfaceAudio(bool co,MainWindow* parentWindow, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceAudio)
    , mainWindow(parentWindow)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , CO(co)
    , coMode(co)
{
    ui->setupUi(this);
    connect(player, &QMediaPlayer::durationChanged, this, [=](qint64 duration) {
        ui->horizontalSlider->setRange(0, static_cast<int>(duration));
    });

    connect(player, &QMediaPlayer::positionChanged, this, [=](qint64 position) {
        ui->horizontalSlider->setValue(static_cast<int>(position));
    });


    ui->pushButton_Pause->setVisible(true);
    ui->pushButton_Play->setVisible(false);
    setFixedSize(800,480);
    if (CO) {
        ui->pushButton_Avant->setEnabled(false);
        ui->pushButton_Pause->setEnabled(false);
        ui->pushButton_Apres->setEnabled(false);
        ui->horizontalSlider->setEnabled(false);

        ui->pushButtonReset->setVisible(true);
    } else {
        ui->pushButton_Avant->setEnabled(true);
        ui->pushButton_Pause->setEnabled(true);
        ui->pushButton_Apres->setEnabled(true);
        ui->horizontalSlider->setEnabled(true);

        ui->pushButtonReset->setVisible(false);
    }

    this->setWindowTitle("Page de Comprehension Orale");
    player->setAudioOutput(audioOutput);
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
        ui->pushButton_Avant->setIcon(icone);
        ui->pushButton_Avant->setIconSize(ui->pushButton_Avant->size());
    }
    QPixmap imageApres10(":/images/Apres10");
    if (imageApres10.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageApres10);
        ui->pushButton_Apres->setIcon(icone);
        ui->pushButton_Apres->setIconSize(ui->pushButton_Apres->size());
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
    ui->chronoLabel->setVisible(true);

    remainingTime = parentWindow->getTime();
    chronoTimer = new QTimer(this);

    connect(chronoTimer, &QTimer::timeout, this, &InterfaceAudio::updateChronoLabel);

    udpSocketCMD.bind(QHostAddress::Any, cmdPort);
    connect(&udpSocketCMD, &QUdpSocket::readyRead, this, &InterfaceAudio::receiveCmd);

    clignotementTimer = new QTimer(this);
    connect(clignotementTimer, &QTimer::timeout, this, &InterfaceAudio::faireClignoterLabel);

    clignotementEtat = false;

    ui->chronoLabel->setVisible(true);
    ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: white; border: 2px solid white; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");

    if (remainingTime.isValid() && remainingTime != QTime(0, 0)) {
        ui->chronoLabel->setText(remainingTime.toString("mm:ss"));
        chronoTimer->start(1000);
    } else {
        ui->chronoLabel->setText("00:00");
        ui->chronoLabel->setVisible(false);

    }

    QFile file(mainWindow->getSessionPATH() + "/" + mainWindow->getNomFichier());

    if (mainWindow->getNomFichier() != nullptr) {
        player->setSource(QUrl::fromLocalFile(file.fileName()));
        player->play();
        qDebug() << "Fichier sélectionné : " << file.fileName() << file.exists();
    }
}

void InterfaceAudio::receiveCmd() {
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

InterfaceAudio::~InterfaceAudio()
{
    delete ui;
}

void InterfaceAudio::setAudioPause(bool pause)
{
    if (pause) {
        player->pause();
    } else {
        player->play();
    }

    ui->pushButton_Pause->setVisible(!pause);
    ui->pushButton_Play->setVisible(pause);
}

void InterfaceAudio::on_pushButton_Play_clicked()
{
    setAudioPause(false);
}

void InterfaceAudio::on_pushButton_Pause_clicked()
{
    setAudioPause(true);
}
void InterfaceAudio::on_pushButton_Avant_clicked()
{
    animateButtonClick(ui->pushButton_Avant);
    qint64 currentPosition = player->position();
    qint64 newPosition = currentPosition - 10000;
    if (newPosition < 0)
        newPosition = 0;
    player->setPosition(newPosition);
}
void InterfaceAudio::on_pushButton_Apres_clicked()
{
    animateButtonClick(ui->pushButton_Apres);
    qint64 currentPosition = player->position();
    qint64 newPosition = currentPosition + 10000;
    player->setPosition(newPosition);
}

void InterfaceAudio::closeEvent(QCloseEvent *event) {
    if (player) {
        player->stop();
        delete player;
        player = nullptr;
    }
    event->accept();
}

void InterfaceAudio::on_horizontalSlider_sliderReleased()
{
    int position = ui->horizontalSlider->value();

    player->setPosition(position);
}
void InterfaceAudio::animateButtonClick(QPushButton* btn) {
    const QRect orig = btn->geometry();
    const QRect small = orig.adjusted(5, 5, -5, -5);
    auto *shrink = new QPropertyAnimation(btn, "geometry");
    shrink->setDuration(60);
    shrink->setStartValue(orig);
    shrink->setEndValue(small);
    auto *expand = new QPropertyAnimation(btn, "geometry");
    expand->setDuration(60);
    expand->setStartValue(small);
    expand->setEndValue(orig);
    auto *seq = new QSequentialAnimationGroup(btn);
    seq->addAnimation(shrink);
    seq->addAnimation(expand);
    seq->start(QAbstractAnimation::DeleteWhenStopped);
}

void InterfaceAudio::on_pushButtonReset_clicked()
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

void InterfaceAudio::on_pushButton_Son_clicked()
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

void InterfaceAudio::faireClignoterLabel()
{
    clignotementEtat = !clignotementEtat;
    if (clignotementEtat)
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: red; border: 2px solid red; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
    else
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: white; border: 2px solid white; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
}

void InterfaceAudio::updateChronoLabel()
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


void InterfaceAudio::on_pushButtonAppelProf_clicked()
{
    ui->pushButtonAppelProf->setEnabled(false); // désactive le bouton
    ui->pushButtonAppelProf->setStyleSheet("border:1px solid white; border-radius:20px;");

    if (!mainWindow) {
        qDebug() << "[InterfaceAudio] mainWindow est null, impossible d'envoyer le message";
        return;
    }

    QString ipProf = mainWindow->getIpProf(); // Récupérer l'adresse IP du professeur
    qDebug() << "[InterfaceAudio] Adresse IP prof récupérée :" << ipProf; // Log pour vérifier l'adresse IP du professeur
    if (ipProf.isEmpty()) {
        qDebug() << "[InterfaceAudio] IP Prof vide, envoi annulé";
        return;
    }

    quint16 port = 5557;
    QString message = "help"; // Message à envoyer

    mainWindow->sendCommandToProf(ipProf, port, message);
}

