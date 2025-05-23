#include "interfaceenregistrement.h"
#include "ui_interfaceenregistrement.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUdpSocket>
#include <QMessageBox>
#include <QDir>

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
    connect(mediaRecorder, &QMediaRecorder::recorderStateChanged, this, &InterfaceEnregistrement::onRecorderStateChanged);
    connect(mediaRecorder, &QMediaRecorder::errorOccurred, this, &InterfaceEnregistrement::onRecorderErrorOccurred);
    connect(timer, &QTimer::timeout,this, &InterfaceEnregistrement::updateChrono);
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

    // 2) Supprimer l’ancien fichier réellement enregistré
    if (!audioFilePath.isEmpty() && QFile::exists(audioFilePath)) {
        QFile::remove(audioFilePath);
        qDebug() << "🗑 Ancien enregistrement supprimé :" << audioFilePath;
    }

    // 3) Préparer le dossier & chemin du nouveau fichier
    const QString docs   = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    const QString folder = QDir(docs).filePath("Travail");
    if (!QDir(folder).exists()) QDir().mkpath(folder);

    const QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    audioFilePath = QDir(folder).filePath(timestamp + ".wav");
    qDebug() << "🎙 Création du fichier :" << audioFilePath;

    // 4) Réinitialiser le chrono
    totalSecondes = 0;
    ui->chrono_enregistrement->setText("00:00:00");

    // 5) Configurer & lancer l’enregistrement
    QMediaFormat fmt;
    fmt.setFileFormat(QMediaFormat::FileFormat::Wave);
    mediaRecorder->setMediaFormat(fmt);
    mediaRecorder->setOutputLocation(QUrl::fromLocalFile(audioFilePath));
    mediaRecorder->record();

    // 6) Redémarrer le timer en s'assurant qu'il est arrêté d'abord
    timer->stop();
    timer->start(1000);

    // 7) Mémoriser ce fichier pour la prochaine suppression
    audioFilePath = audioFilePath;

    // 8) Mettre à jour l’UI
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
        ui->chrono_enregistrement->setText("00:00:00");
        ui->pushButtonPause->setVisible(false);
        ui->pushButtonPlay ->setVisible(true);
        qDebug() << "🛑 Enregistrement arrêté via Enregistrer.";
    }
    // 2) Réinitialiser le chrono
    totalSecondes = 0;
    ui->chrono_enregistrement->setText("00:00:00");

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
    // 1) Arrêt immédiat du chrono, quel que soit le recorderState
    if (timer->isActive()) {
        timer->stop();
        qDebug() << "⏸️ Chrono mis en pause à" << totalSecondes;
    }

    // 2) Si on enregistre, on met en pause le mediaRecorder
    if (mediaRecorder->recorderState() == QMediaRecorder::RecordingState) {
        mediaRecorder->pause();
        qDebug() << "⏸️ Enregistrement mis en pause";
    }
    // 3) Sinon, si on lit, on met la lecture en pause
    else if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
        qDebug() << "⏸️ Lecture mise en pause";
    }

    // 4) UI : masquer Pause, afficher Play
    ui->pushButtonPause->setVisible(false);
    ui->pushButtonPlay ->setVisible(true);
}

void InterfaceEnregistrement::on_pushButtonPlay_clicked()
{
    // 1) Relance du chrono
    if (!timer->isActive()) {
        timer->start(1000);
        qDebug() << "▶️ Chrono repris à" << totalSecondes;
    }

    // 2) Si on reprenait un enregistrement en pause, on relance le mediaRecorder
    if (mediaRecorder->recorderState() == QMediaRecorder::PausedState) {
        mediaRecorder->record();
        qDebug() << "▶️ Enregistrement repris";
    }
    // 3) Sinon, si on reprenait une lecture en pause, on relance la lecture
    else if (player->playbackState() == QMediaPlayer::PausedState) {
        player->play();
        qDebug() << "▶️ Lecture reprise";
    }

    // 4) UI : masquer Play, afficher Pause
    ui->pushButtonPlay->setVisible(false);
    ui->pushButtonPause->setVisible(true);
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
    ui->chrono_enregistrement->setText("00:00:00");

    // 4) Remettre l'UI en mode « prêt » : on cache les contrôles Play/Pause
    ui->pushButtonPause->setVisible(false);
    ui->pushButtonPlay ->setVisible(false);
    // (le bouton Speak reste visible pour démarrer un nouvel enregistrement)

    qDebug() << "Chrono remis à zéro. Fichier inchangé :"
             << audioFilePath;
}

void InterfaceEnregistrement::on_pushButtonRetourArriere_clicked()
{
    // Affiche toujours Pause (et cache Play) pour permettre un arrêt manuel
    ui->pushButtonPlay->setVisible(false);
    ui->pushButtonPause->setVisible(true);

    // Si on est à 0 mais qu’on a mémorisé un dernier point, on le restaure
    if (totalSecondes == 0 && lastRecordedTime > 0) {
        totalSecondes = lastRecordedTime;
        updateChrono();
        qDebug() << "🔄 Restauration du dernier temps :" << totalSecondes;
        return;
    }

    // Sinon, si on peut reculer et qu’on n’est pas déjà en rewind
    if (totalSecondes > 0 && !isRewinding) {
        isRewinding = true;
        rewindTimer->start(100);  // tick toutes les 100 ms
        qDebug() << "⏪ Retour arrière en cours";
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
void InterfaceEnregistrement::rewindChrono()
{
    if (totalSecondes > 0) {
        totalSecondes--;
        // On met à jour **seulement** l'affichage
        updateChronoLabel();
    } else {
        // Arrêt automatique à 0
        rewindTimer->stop();
        isRewinding = false;
        ui->pushButtonPause->setVisible(true);
        ui->pushButtonPlay ->setVisible(false);
        qDebug() << "⏹ Chrono à zéro, pause maintenue";
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
void InterfaceEnregistrement::on_pushButtonAppelProf_clicked()
{
    ui->pushButtonAppelProf->setStyleSheet("QPushButton { background-color: none; border: none; }");
    qWarning() << "Label Appel Prof affiche";

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

