#include "interfaceenregistrement.h"
#include "ui_interfaceenregistrement.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUdpSocket>
#include <QMessageBox>
#include <QDir>
#include "mainwindow.h"

InterfaceEnregistrement::InterfaceEnregistrement(MainWindow* parentWindow,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceEnregistrement)
    ,mainWindow(parentWindow)
    ,isButtonAppelProfImage(true)
{
    ui->setupUi(this);
    setFixedSize(800, 480);
    setWindowTitle("Page d'Enregistrement");

    // Initialisation des boutons
    ui->pushButtonPause->setVisible(true);
    ui->pushButtonPlay->setVisible(false);
    ui->verticalSlider_sonVideo->setVisible(false); // Cacher au démarrage


    // UDP pour feedback
    udpSocket.bind(QHostAddress::Any, responsePort);
    connect(&udpSocket, &QUdpSocket::readyRead, this, &InterfaceEnregistrement::receiveResponse);


    // Initialisation audio / enregistrement
    audioInput = new QAudioInput(this);
    mediaRecorder = new QMediaRecorder(this);
    audioOutput = new QAudioOutput(this);
    player = new QMediaPlayer(this);
    player->setAudioOutput(audioOutput);

    // Configuration de la session de capture
    captureSession.setAudioInput(audioInput);
    captureSession.setRecorder(mediaRecorder);

    // Format d'enregistrement
    QMediaFormat fmt;
    fmt.setFileFormat(QMediaFormat::FileFormat::Wave);
    mediaRecorder->setMediaFormat(fmt);

    // Timers
    timer = new QTimer(this);             // chrono d'enregistrement
    rewindTimer = new QTimer(this);       // retour arrière
    // Note: pas de chronoTimer pour enregistrement

    connect(rewindTimer, &QTimer::timeout,this, &InterfaceEnregistrement::rewindChrono);
    connect(timer, &QTimer::timeout,this, &InterfaceEnregistrement::updateChrono);
    connect(mediaRecorder, &QMediaRecorder::recorderStateChanged, this, &InterfaceEnregistrement::onRecorderStateChanged);
    connect(mediaRecorder, &QMediaRecorder::errorOccurred, this, &InterfaceEnregistrement::onRecorderErrorOccurred);
    connect(ui->pushButtonRetourArriere, &QPushButton::clicked,this, &InterfaceEnregistrement::on_pushButtonRetourArriere_clicked);
    // Icônes des boutons
    setButtonIcons();

    // Variables
    isRewinding = false;
    totalSecondes = 0;
    lastRecordedTime = 0;

    // Préparer feedback.txt
    QFile file("feedback.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "";
        file.close();
    }

    // Verrouiller zones pour non-prof
    if (!Professor) {
        ui->textEditFeedBack->setReadOnly(true);
        ui->textEditFeedBack->setPlaceholderText("Accès réservé aux professeurs");
        ui->textEditConsigne->setReadOnly(true);
    }

    // Afficher consigne
    ui->textEditConsigne->setText(mainWindow->getConsigne());

    // Initialiser label chrono enregistrement
    ui->chrono_enregistrement->setText("00:00:00");
    ui->chrono_enregistrement->setVisible(true);
    ui->chrono_enregistrement->setStyleSheet("font-size: 24px; font-weight: bold; color: black;");

    ui->chronoLabel->setVisible(true);

    remainingTime = parentWindow->getTime();
    chronoTimer = new QTimer(this);

    connect(chronoTimer, &QTimer::timeout, this, &InterfaceEnregistrement::updateChronoGlobal);

    clignotementTimer = new QTimer(this);
    connect(clignotementTimer, &QTimer::timeout, this, &InterfaceEnregistrement::faireClignoterLabel);

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
}


InterfaceEnregistrement::~InterfaceEnregistrement()
{
    delete ui;
    delete mediaRecorder;
    delete player;
    delete audioInput;
    delete audioOutput;
    delete timer;
    delete rewindTimer;
}
void InterfaceEnregistrement::setButtonIcons()
{
    auto setIcon = [&](QPushButton *button, const QString &imagePath) {
        QPixmap image(imagePath);
        if (image.isNull()) {
            qWarning() << "Erreur : image non trouvée !";
        } else {
            QIcon icon(image);
            button->setIcon(icon);
            button->setIconSize(button->size());
        }
    };

    setIcon(ui->pushButtonSon, ":/images/Son");
    setIcon(ui->pushButtonEnregistrer, ":/images/Enregistrer");
    setIcon(ui->pushButtonRetourArriere, ":/images/RevenirArriere");
    setIcon(ui->pushButtonPause, ":/images/Pause");
    setIcon(ui->pushButtonSpeak, ":/images/Enregistrement");
    setIcon(ui->pushButtonClear, ":/images/Effacer");
    setIcon(ui->pushButtonAppelProf, ":/images/CallProf");
    setIcon(ui->pushButtonPlay,":/images/Play");
}

void InterfaceEnregistrement::on_pushButtonSpeak_clicked()
{
    if (timer->isActive()) {
        timer->stop();
    }
    totalSecondes = 0;
    ui->chrono_enregistrement->setText("00:00:00");
    qDebug() << "🔄 Chrono remis à zéro via Speak.";

    // --- 2) Si un enregistrement est déjà en cours, on l'arrête proprement ---
    if (mediaRecorder->recorderState() != QMediaRecorder::StoppedState) {
        mediaRecorder->stop();
        qDebug() << "🛑 Enregistrement existant stoppé via Speak.";
    }


    // --- 4) Préparer le dossier Travail et le nom de fichier fixe ---
    const QString docs = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    const QString folder = QDir(docs).filePath("Travail");
    if (!QDir(folder).exists()) {
        QDir().mkpath(folder);  // Crée le dossier s'il n'existe pas
        qDebug() << "📂 Dossier créé : " << folder;
    }

    audioFilePath = QDir(folder).filePath("audio.wav");  // Toujours le même fichier
    qDebug() << "🎙 Fichier cible :" << audioFilePath;

    // --- 4) Supprimer l’ancien fichier s’il existe ---
    if (QFile::exists(audioFilePath)) {
        QFile::remove(audioFilePath);  // Supprime le fichier existant
        qDebug() << "🗑 Ancien fichier supprimé.";
    }

    // --- 5) Configurer & lancer le nouvel enregistrement ---
    QMediaFormat fmt;
    fmt.setFileFormat(QMediaFormat::FileFormat::Wave);  // Utiliser le format WAV
    mediaRecorder->setMediaFormat(fmt);
    mediaRecorder->setOutputLocation(QUrl::fromLocalFile(audioFilePath));
    mediaRecorder->record();  // Commence l'enregistrement

    // --- 6) Relancer le timer pour le chrono d’enregistrement ---
    timer->start(1000);  // Relance le chrono

    // --- 7) Mettre à jour l’UI des boutons ---
    ui->pushButtonPause->setVisible(true);
    ui->pushButtonPlay->setVisible(false);
    qDebug() << "▶️ Nouvel enregistrement démarré, fichier :" << audioFilePath;
}

void InterfaceEnregistrement::on_pushButtonEnregistrer_clicked()
{
    animateButtonClick(ui->pushButtonEnregistrer);

    // Si un enregistrement est en cours, on l'arrête
    if (mediaRecorder->recorderState() != QMediaRecorder::StoppedState) {
        mediaRecorder->stop();
        timer->stop();  // Arrêter le chrono
        totalSecondes = 0;
        ui->chrono_enregistrement->setText("00:00:00");
        ui->pushButtonPause->setVisible(false);
        ui->pushButtonPlay->setVisible(true);
        qDebug() << "🛑 Enregistrement arrêté via Enregistrer.";
    }

    // 2) Réinitialiser le chrono
    totalSecondes = 0;
    ui->chrono_enregistrement->setText("00:00:00");

    // Afficher un message de confirmation (optionnel)
    QMessageBox::information(this, "Enregistrement", "Enregistrement terminé et sauvegardé.");
    qDebug() << "✅ Enregistrement sauvegardé dans le fichier : " << audioFilePath;
    ui->pushButtonPlay->setVisible(false);
    ui->pushButtonPause->setVisible(true);  // "Pause" sera affiché au lieu de "Play"
    qDebug() << "▶️ Enregistrement mis en pause et prêt à être repris.";
}

void InterfaceEnregistrement::on_pushButtonPause_clicked()
{
    // 0) Si on était en rewind, on l'interrompt d'abord
    if (isRewinding) {
        rewindTimer->stop();
        isRewinding = false;
        qDebug() << "⏸️ Rewind stoppé à" << totalSecondes << "s";
    }
    // 1) Arrêt immédiat du chrono, quel que soit le recorderState
    if (timer->isActive())
        timer->stop();

    // 2) met en pause l'enregistrement si on enregistre
    if (mediaRecorder->recorderState() == QMediaRecorder::RecordingState)
        mediaRecorder->pause();

    // 3) UI : cacher Pause, afficher Play
    ui->pushButtonPause->setVisible(false);
    ui->pushButtonPlay ->setVisible(true);

    qDebug() << "⏸️ Chrono et enregistrement mis en pause à" << totalSecondes;
}

void InterfaceEnregistrement::on_pushButtonPlay_clicked()
{
    // 1) Relance du chrono (sauf si on est encore en rewind, mais on désactive rewind dans pause)
    if (!timer->isActive())
        timer->start(1000);

    // 2) reprend l'enregistrement si on était en pause
    if (mediaRecorder->recorderState() == QMediaRecorder::PausedState)
        mediaRecorder->record();

    // 3) UI : cacher Play, afficher Pause
    ui->pushButtonPlay ->setVisible(false);
    ui->pushButtonPause->setVisible(true);

    qDebug() << "▶️ Chrono et enregistrement repris à" << totalSecondes;
}


void InterfaceEnregistrement::on_pushButtonClear_clicked()
{
    animateButtonClick(ui->pushButtonClear);
    if (timer->isActive()) {
        timer->stop();
        qDebug() << "⏱ Timer stoppé par Clear.";
    }

    // 2) Remettre le compteur à zéro
    totalSecondes = 0;
    updateChronoLabel();  // affiche "00:00:00" dans le label

    // 3) UI : afficher Pause, masquer Play
    ui->pushButtonPause->setVisible(true);
    ui->pushButtonPlay ->setVisible(false);

    qDebug() << "🔄 Chrono remis à zéro et bouton Pause affiché.";
}

void InterfaceEnregistrement::on_pushButtonRetourArriere_clicked()
{
    if (timer->isActive())
        timer->stop();

    // 2) UI — on reste en mode “Pause” pour que l'utilisateur puisse interrompre
    ui->pushButtonPause->setVisible(true);
    ui->pushButtonPlay ->setVisible(false);

    // 3) Si on est déjà à 0 mais qu'on a un dernier point, on restaure ce point
    if (totalSecondes == 0 && lastRecordedTime > 0) {
        totalSecondes = lastRecordedTime;
        updateChronoLabel();
        qDebug() << "🔄 Restauration du dernier temps :" << totalSecondes;
        return;
    }

    // 4) Sinon, si on peut reculer et qu'on n'est pas déjà en rewind, on lance le rewind
    if (totalSecondes > 0 && !isRewinding) {
        isRewinding = true;
        rewindTimer->start(100);  // décrémente toutes les 100 ms
        qDebug() << "⏪ Rewind démarré";
    }
}
void InterfaceEnregistrement::rewindChrono()
{
    if (totalSecondes > 0) {
        totalSecondes--;
        updateChronoLabel();    // affiche la nouvelle valeur
    } else {
        // Arrêt automatique quand on atteint 0
        rewindTimer->stop();
        isRewinding = false;
        ui->pushButtonPause->setVisible(true);
        ui->pushButtonPlay ->setVisible(false);
        qDebug() << "⏹ Rewind terminé (0 reached)";
    }
}
void InterfaceEnregistrement::updateChrono()
{
    if(isRewinding) return;
    totalSecondes++;
    updateChronoLabel();
}

void InterfaceEnregistrement::updateChronoLabel()
{
    int h = totalSecondes / 3600;
    int m = (totalSecondes % 3600) / 60;
    int s = totalSecondes % 60;
    ui->chrono_enregistrement->setText(
        QString("%1:%2:%3")
            .arg(h, 2, 10, QChar('0'))
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0')));
}

void InterfaceEnregistrement::updateChronoGlobal()
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

void InterfaceEnregistrement::faireClignoterLabel()
{
    clignotementEtat = !clignotementEtat;
    if (clignotementEtat)
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: red; border: 2px solid red; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
    else
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: white; border: 2px solid white; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
}
void InterfaceEnregistrement::on_pushButtonAppelProf_clicked()
{
    ui->pushButtonAppelProf->setStyleSheet(" border:1px solid white; border-radius:20px;");
    isButtonAppelProfImage = false;

    QUdpSocket *udpSocket = new QUdpSocket(this);
    QJsonObject message;
    message["type"] = "call_request";
    message["id_eleve"] = studentId;
    QJsonDocument doc(message);
    QByteArray data = doc.toJson();
    QHostAddress profAddress("192.168.88.216");
    quint16 profPort = 45454;
    udpSocket->writeDatagram(data, profAddress, profPort);
}

void InterfaceEnregistrement::checkPlaybackPosition(qint64 position)
{
    if (position / 1000 >= totalSecondes) {
        player->stop();
        qDebug() << "Lecture arrêtée car elle a dépassé le temps du chronomètre";
    }
}

void InterfaceEnregistrement::onRecorderStateChanged(QMediaRecorder::RecorderState state)
{
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
    qDebug() << "Erreur d'enregistrement:" << errorString;
}
void InterfaceEnregistrement::animateButtonClick(QPushButton* btn) {
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
void InterfaceEnregistrement::on_pushButtonSon_clicked()
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

void InterfaceEnregistrement::receiveResponse() {
    while (udpSocket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString response = QString::fromUtf8(datagram);
        qDebug() << "📢 Réponse reçue de" << sender.toString() << ":" << response;

        // Vérifiez si le message est "mute"
        if (response.trimmed() != "")        {
            QFile file("feedback.txt");
            if (file.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&file);
                out<< response << "\n";
                file.close();
            }

            QFile inFile("feedback.txt");
            if (inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&inFile);
                QString contenu = in.readAll();
                inFile.close();

                // 🔍 Exemple : afficher dans la console ou un widget
                qDebug() << "Contenu complet du fichier :";
                qDebug().noquote() << contenu;
                ui->textEditFeedBack->setText(contenu);
            }
        }
    }
}

