#include "interfaceenregistrement.h"
#include "ui_interfaceenregistrement.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUdpSocket>
#include <QMessageBox>
#include <QDir>

InterfaceEnregistrement::InterfaceEnregistrement(MainWindow* parentWindow, QWidget *parent)
    : QDialog(parent), ui(new Ui::InterfaceEnregistrement)
    , mainWindow(parentWindow)
    , isButtonAppelProfImage(true)
{
    ui->setupUi(this);
    ui->pushButtonPause->setVisible(true);
    ui->pushButtonPlay->setVisible(false);
    // Pour fixer la taille de la page et le titre
    setFixedSize(800, 480);

    this->setWindowTitle("Page d'Enregistrement");
    udpSocket.bind(QHostAddress::Any, responsePort);
    connect(&udpSocket, &QUdpSocket::readyRead, this, &InterfaceEnregistrement::receiveResponse);

    // Initialisation des autres composants et variables
    mediaRecorder = new QMediaRecorder(this);
    player = new QMediaPlayer(this);
    audioInput = new QAudioInput(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    timer = new QTimer(this);
    mediaRecorder = new QMediaRecorder(this);
    audioInput = new QAudioInput(this);
    captureSession.setAudioInput(audioInput);
    captureSession.setRecorder(mediaRecorder);
    QMediaFormat fmt;
    fmt.setFileFormat(QMediaFormat::FileFormat::Wave);
    mediaRecorder->setMediaFormat(fmt);

    rewindTimer = new QTimer(this);
    captureSession.setAudioInput(audioInput);
    captureSession.setRecorder(mediaRecorder);
    connect(mediaRecorder, &QMediaRecorder::recorderStateChanged, this, &InterfaceEnregistrement::onRecorderStateChanged);
    connect(mediaRecorder, &QMediaRecorder::errorOccurred, this, &InterfaceEnregistrement::onRecorderErrorOccurred);

    clignotementTimer = new QTimer(this);
    connect(clignotementTimer, &QTimer::timeout, this, &InterfaceEnregistrement::faireClignoterLabel);

    clignotementEtat = false;

    // Affichage des Images
    setButtonIcons();

    isRewinding = false;
    totalSecondes = 0;
    speakButtonClicked = false;
    isRecordingPaused = false;
    lastRecordedTime = 0;

    QFile file("feedback.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out<<"";
        file.close();
    }

    // Vérifier si l'utilisateur est un professeur
    if (!Professor) {
        ui->textEditFeedBack->setReadOnly(true); // Bloquer l'accès en écriture
        ui->textEditFeedBack->setPlaceholderText("Accès réservé aux professeurs"); // Message d'information
    }

    ui->textEditConsigne->setText(mainWindow->getConsigne());
    ui->chronoLabel->setVisible(true);

    remainingTime = mainWindow->getTime();
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

void InterfaceEnregistrement::faireClignoterLabel()
{
    clignotementEtat = !clignotementEtat;
    if (clignotementEtat)
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: red; border: 2px solid red; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
    else
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: white; border: 2px solid white; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
}

void InterfaceEnregistrement::updateChronoLabel()
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
void InterfaceEnregistrement::onUdpTimeout()
{
    // on peut recevoir plusieurs paquets, on les vide tous
    while (udpChrono.hasPendingDatagrams()) {
        QByteArray dg;
        dg.resize(udpChrono.pendingDatagramSize());
        udpChrono.readDatagram(dg.data(), dg.size());
        QString s = QString::fromUtf8(dg).trimmed();    // ex: "05:00"

        // on s’attend à un format mm:ss
        auto parts = s.split(':');
        if (parts.size()==2) {
            int m   = parts[0].toInt();
            int sec = parts[1].toInt();
            int ms  = (m*60 + sec) * 1000;
            // 3) schedule la fermeture automatique
            QTimer::singleShot(ms, this, &QDialog::accept);
        }
    }
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
    setIcon(ui->pushButtonAvancer, ":/images/Avancer");
    setIcon(ui->pushButtonSpeak, ":/images/Enregistrement");
    setIcon(ui->pushButtonClear, ":/images/Effacer");
    setIcon(ui->pushButtonAppelProf, ":/images/CallProf");
    setIcon(ui->pushButtonPlay,":/images/Play");
}

void InterfaceEnregistrement::on_pushButtonSpeak_clicked()
{
    if (mediaRecorder->recorderState() != QMediaRecorder::StoppedState) {
        mediaRecorder->stop();
        timer->stop();
        qDebug() << "🛑 Enregistrement existant stoppé via Speak.";
    }

    // 1) Supprimer l’ancien fichier **réellement enregistré** (pas le nouveau)
    if (!lastAudioFilePath.isEmpty() && QFile::exists(lastAudioFilePath)) {
        QFile::remove(lastAudioFilePath);
        qDebug() << "🗑 Ancien enregistrement supprimé :" << lastAudioFilePath;
    }

    // 2) Préparer le dossier & chemin du nouveau fichier
    const QString docs   = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    const QString folder = QDir(docs).filePath("Travail");
    if (!QDir(folder).exists()) QDir().mkpath(folder);

    const QString timestamp         = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    audioFilePath = QDir(folder).filePath(timestamp + ".wav");
    qDebug() << "🎙 Création du fichier :" << audioFilePath;

    // 3) Réinitialiser le chrono
    totalSecondes = 0;
    ui->labelChrono->setText("00:00:00");

    // 4) Configurer & lancer l’enregistrement + chrono
    QMediaFormat fmt;
    fmt.setFileFormat(QMediaFormat::FileFormat::Wave);
    mediaRecorder->setMediaFormat(fmt);
    mediaRecorder->setOutputLocation(QUrl::fromLocalFile(audioFilePath));
    mediaRecorder->record();
    timer->start(1000);

    // 5) Mémoriser ce fichier pour la prochaine suppression
    lastAudioFilePath = audioFilePath;

    // 6) Mettre à jour l’UI
    ui->pushButtonPause->setVisible(true);
    ui->pushButtonPlay ->setVisible(false);
    qDebug() << "▶️ Nouvel enregistrement démarré";
}
void InterfaceEnregistrement::on_pushButtonEnregistrer_clicked()
{
    animateButtonClick(ui->pushButtonEnregistrer);

    if (mediaRecorder->recorderState() != QMediaRecorder::StoppedState) {
        mediaRecorder->stop();
        timer->stop();
        totalSecondes = 0;
        ui->labelChrono->setText("00:00:00");
        ui->pushButtonPause->setVisible(false);
        ui->pushButtonPlay ->setVisible(true);
        qDebug() << "🛑 Enregistrement arrêté via Enregistrer.";
    }
    // 2) Réinitialiser le chrono
    totalSecondes = 0;
    ui->labelChrono->setText("00:00:00");

    // 3) Préparer le dossier et le chemin du fichier
    const QString docs = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    const QString folder = QDir(docs).filePath("Travail");
    if (!QDir(folder).exists())
        QDir().mkpath(folder);

    const QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    audioFilePath = QDir(folder).filePath(timestamp + ".wav");
    qDebug() << "🎙 Fichier cible :" << audioFilePath;

    // 4) Supprimer l’ancien fichier pour écraser
    if (QFile::exists(audioFilePath)) {
        QFile::remove(audioFilePath);
        qDebug() << "🗑 Ancien fichier supprimé.";
    }

    // 5) Configurer le média et lancer l’enregistrement
    QMediaFormat fmt;
    fmt.setFileFormat(QMediaFormat::FileFormat::Wave);
    mediaRecorder->setMediaFormat(fmt);
    mediaRecorder->setOutputLocation(QUrl::fromLocalFile(audioFilePath));

    ui->pushButtonPlay ->setVisible(false);
    ui->pushButtonPause->setVisible(true);

    //mediaRecorder->record();
    //timer->start(1000);

    //qDebug() << "▶️ Nouvel enregistrement démarré, ancienne piste écrasée.";

}
void InterfaceEnregistrement::on_pushButtonPause_clicked()
{
    if (mediaRecorder->recorderState() == QMediaRecorder::RecordingState) {
        // Pause de l’enregistrement + chrono
        mediaRecorder->pause();
        timer->stop();
        qDebug() << "⏸️ Enregistrement en pause";
    } else if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
        qDebug() << "⏸️ Lecture en pause";
    }

    // UI
    ui->pushButtonPause->setVisible(false);
    ui->pushButtonPlay ->setVisible(true);
}
void InterfaceEnregistrement::on_pushButtonPlay_clicked()
{
    if (mediaRecorder->recorderState() == QMediaRecorder::PausedState) {
        mediaRecorder->record();  // reprend l'enregistrement
        timer->start(1000);       // reprend le chrono
        qDebug() << "Reprise de l'enregistrement.";

    } else if (player->playbackState() == QMediaPlayer::PausedState) {
        player->play();
        qDebug() << "Reprise de la lecture.";
    }

    ui->pushButtonPlay->setVisible(false);   // ❗ masquer play
    ui->pushButtonPause->setVisible(true);   // ❗ afficher pause
}


void InterfaceEnregistrement::on_pushButtonClear_clicked()
{
    animateButtonClick(ui->pushButtonClear);
    if (mediaRecorder->recorderState() == QMediaRecorder::RecordingState ||
        mediaRecorder->recorderState() == QMediaRecorder::PausedState) {
        mediaRecorder->stop();
        qDebug() << "🛑 Enregistrement stoppé par Clear.";
    }

    // 2) Arrêter le timer s'il tourne
    if (timer->isActive()) {
        timer->stop();
        qDebug() << "⏱ Timer stoppé par Clear.";
    }

    // 3) Réinitialiser le chrono à zéro
    totalSecondes = 0;
    ui->labelChrono->setText("00:00:00");

    // 4) Remettre l'UI en mode « prêt » : on cache les contrôles Play/Pause
    ui->pushButtonPause->setVisible(false);
    ui->pushButtonPlay ->setVisible(false);
    // (le bouton Speak reste visible pour démarrer un nouvel enregistrement)

    qDebug() << "Chrono remis à zéro. Fichier inchangé :"
             << audioFilePath;
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
    QDialog popup(this);
    popup.setWindowTitle(" ");
    popup.setGeometry(1075, 330, 20, 150); // Positionne la fenêtre popup à (1030, 330) avec une taille de 20x150
    popup.setFixedSize(80, 150);
    popup.setModal(true);

    // Création du slider vertical
    QSlider *slider = new QSlider(Qt::Vertical, &popup);
    slider->setRange(0, 100);
    int volume = static_cast<int>(audioOutput->volume() * 100);
    slider->setValue(volume);
    audioOutput->setVolume(volume / 100.0);

    // Label et bouton
    QLabel *label = new QLabel("Son", &popup);
    QPushButton *closeButton = new QPushButton("Fermer", &popup);

    // Layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(&popup);
    QHBoxLayout *slidersLayout = new QHBoxLayout();
    slidersLayout->addWidget(label);
    slidersLayout->addWidget(slider);
    mainLayout->addLayout(slidersLayout);
    mainLayout->addWidget(closeButton);
    popup.setLayout(mainLayout);

    // Connexion des signaux
    QObject::connect(slider, &QSlider::valueChanged, this, [=](int value) {
        audioOutput->setVolume(value / 100.0);
        qDebug() << "Volume réglé à :" << value;
    });

    QObject::connect(closeButton, &QPushButton::clicked, &popup, &QDialog::accept);

    // Affichage de la popup
    popup.exec();

}

void InterfaceEnregistrement::on_pushButtonRetourArriere_clicked()
{
    if (totalSecondes == 0 && lastRecordedTime > 0) {
        totalSecondes = lastRecordedTime;
        updateChronoLabel();
        qDebug() << "Retour au dernier temps enregistré : " << totalSecondes;
    } else if (totalSecondes > 0 && !isRewinding) {
        isRewinding = true;
        rewindTimer->start(100);
        qDebug() << "Retour arrière en cours";
    }
}

void InterfaceEnregistrement::on_pushButtonAvancer_clicked()
{
    if (player && player->playbackState() == QMediaPlayer::PlayingState) {
        qint64 newPosition = player->position() + 5000;
        if (newPosition < player->duration()) {
            player->setPosition(newPosition);
            qDebug() << "Avancé de 5 secondes.";
        }
    }
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


