#include "interfaceaudio.h"
#include "ui_interfaceaudio.h"
#include <QAudioOutput>
#include <QStandardPaths>
#include <QMediaRecorder>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QHostAddress>
#include <QDebug>

InterfaceAudio::InterfaceAudio(bool co, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceAudio)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))  // 🔹 Initialisation de player
    , CO(co) // 🔹 Initialisation de audioOutput
    , coMode(co)
{
    ui->setupUi(this);
    connect(player, &QMediaPlayer::durationChanged, this, [=](qint64 duration) {
        ui->horizontalSlider->setRange(0, static_cast<int>(duration));
    });

    connect(player, &QMediaPlayer::positionChanged, this, [=](qint64 position) {
        ui->horizontalSlider->setValue(static_cast<int>(position));
    });

    {
        // bind() sur l'instance udpChrono, pas sur QAbstractSocket::UdpSocket !
        if (!udpChrono.bind(
                QHostAddress::AnyIPv4,      // écoute sur toutes les interfaces IPv4
                5558,
                QUdpSocket::ShareAddress |
                    QUdpSocket::ReuseAddressHint
                ))
        {
            qCritical() << "Impossible de binder UDP sur le port 5558 :"
                        << udpChrono.errorString();
        }
        else {
            connect(&udpChrono, &QUdpSocket::readyRead,
                    this,      &InterfaceAudio::receiveChrono);
        }
    }
    ui->pushButton_Pause->setVisible(true);
    ui->pushButton_Play->setVisible(false);
    setFixedSize(800,480);
    if (CO) {
        // mode "écoute_co" : on verrouille les contrôles
        ui->pushButton_Avant->setEnabled(false);
        ui->pushButton_Pause->setEnabled(false);
        ui->pushButton_Apres->setEnabled(false);
        ui->horizontalSlider->setEnabled(false);

        // on cache le bouton Reset
        ui->pushButtonReset->setVisible(true);
    } else {
        // mode normal : tout est actif
        ui->pushButton_Avant->setEnabled(true);
        ui->pushButton_Pause->setEnabled(true);
        ui->pushButton_Apres->setEnabled(true);
        ui->horizontalSlider->setEnabled(true);

        // on affiche le bouton Reset
        ui->pushButtonReset->setVisible(false);
    }

    this->setWindowTitle("Page de Comprehension Orale");
    if (coMode) {
        ui->pushButton_SelectAudio->setEnabled(false);
    }
     player->setAudioOutput(audioOutput);
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

    ui->verticalSlider_sonVideo->setVisible(false);
    ui->verticalSlider_sonVideo->setVisible(false);
    ui->verticalSlider_sonVideo->raise();
}

InterfaceAudio::~InterfaceAudio()
{
    delete ui;
}

void InterfaceAudio::on_pushButton_Play_clicked()
{
    player->play();
    ui->pushButton_Pause->setVisible(true);
    ui->pushButton_Play->setVisible(false);
}
void InterfaceAudio::on_pushButton_Pause_clicked()
{
    player->pause();
    ui->pushButton_Pause->setVisible(false);
    ui->pushButton_Play->setVisible(true);
}
void InterfaceAudio::on_pushButton_SelectAudio_clicked()
{
    QString videoPath = "\\\\192.168.89.42\\Activites";  // Adresse réseau correcte

    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Sélectionner une audio",
        videoPath,  // Ouvre directement le dossier réseau
        "Audio Files (*.mp3 *.wav *.ogg *.flac *.aac)"
        );
    if (!fileName.isEmpty()) {
        player->setSource(QUrl::fromLocalFile(fileName));  // Charger et lire l'audio
        player->play();
        qDebug() << "Fichier sélectionné : " << fileName;
    }

}
void InterfaceAudio::on_pushButton_Avant_clicked()
{
    animateButtonClick(ui->pushButton_Avant);
    qint64 currentPosition = player->position();
    qint64 newPosition = currentPosition - 10000;

    // Ensure we don't go below 0 (start of the video)
    if (newPosition < 0)
        newPosition = 0;
    player->setPosition(newPosition);
}
void InterfaceAudio::on_pushButton_Apres_clicked()
{
    animateButtonClick(ui->pushButton_Apres);
    qint64 currentPosition = player->position();
    qint64 newPosition = currentPosition + 10000;

    // Set the new position
    player->setPosition(newPosition);
}

void InterfaceAudio::closeEvent(QCloseEvent *event) {
    if (player) {
        player->stop();  // 🔹 Arrêter la lecture
        delete player;   // 🔹 Libérer la mémoire
        player = nullptr;
    }
    event->accept();  // Accepter la fermeture
}

void InterfaceAudio::on_horizontalSlider_sliderReleased()
{
    int position = ui->horizontalSlider->value();

    player->setPosition(position);
}
void InterfaceAudio::animateButtonClick(QPushButton* btn) {
    // 1) on prend la géométrie d'origine
    const QRect orig = btn->geometry();
    const QRect small = orig.adjusted(5, 5, -5, -5);

    // 2) animation pour rétrécir
    auto *shrink = new QPropertyAnimation(btn, "geometry");
    shrink->setDuration(60);
    shrink->setStartValue(orig);
    shrink->setEndValue(small);

    // 3) animation pour réagrandir
    auto *expand = new QPropertyAnimation(btn, "geometry");
    expand->setDuration(60);
    expand->setStartValue(small);
    expand->setEndValue(orig);

    // 4) on les enchaîne
    auto *seq = new QSequentialAnimationGroup(btn);
    seq->addAnimation(shrink);
    seq->addAnimation(expand);

    // 5) on lance et on supprime l’objet à la fin
    seq->start(QAbstractAnimation::DeleteWhenStopped);
}

void InterfaceAudio::on_pushButtonReset_clicked()
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
void InterfaceAudio::receiveChrono()
{
    while (udpChrono.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(udpChrono.pendingDatagramSize()));

        QHostAddress sender;
        quint16 senderPort;
        udpChrono.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        qDebug() << "📢 Chrono reçu de" << sender.toString() << ":" << datagram;

        // 1) Parse JSON
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(datagram, &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject()) {
            qWarning() << "⛔ JSON invalide pour chrono:" << err.errorString();
            continue;
        }

        QJsonObject obj = doc.object();
        if (!obj.contains("chrono") || !obj.value("chrono").isString()) {
            qWarning() << "⛔ Aucun champ \"chrono\" ou type incorrect";
            continue;
        }

        QString chronoStr = obj.value("chrono").toString();   // ex: "05:30"
        QStringList parts = chronoStr.split(':');
        if (parts.size() != 2) {
            qWarning() << "⛔ Format chrono inattendu (MM:SS)";
            continue;
        }

        bool okMin, okSec;
        int minutes = parts[0].toInt(&okMin);
        int seconds = parts[1].toInt(&okSec);
        if (!okMin || !okSec) {
            qWarning() << "⛔ Impossible de convertir minutes/secondes";
            continue;
        }

        int totalMs = (minutes * 60 + seconds) * 1000;
        qDebug() << "⏳ Démarrage du timer pour" << minutes << "min" << seconds << "sec";

        // 2) Lance un single-shot pour fermer l'interface à la fin du chrono
        QTimer::singleShot(totalMs, this, [this]() {
            qDebug() << "⏰ Temps écoulé, fermeture de l'interface.";
            this->close();
        });

        // On ne traite qu’un seul chrono par réception
        break;
    }
}


void InterfaceAudio::on_pushButton_Son_clicked()
{
    ui->verticalSlider_sonVideo->setVisible(!ui->verticalSlider_sonVideo->isVisible());
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
            clignotementTimer->start(500); // clignote toutes les 500 ms
    }

    if (remainingTime == QTime(0, 0)) {
        chronoTimer->stop();
        ui->chronoLabel->setText("00:00");
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: red; border: 2px solid red; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
        QMessageBox::information(this, "Fin de l'activité", "Pensez à mettre fin à l'activité en cours !");
    }
}
