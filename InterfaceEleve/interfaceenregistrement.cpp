#include "interfaceenregistrement.h"
#include "ui_interfaceenregistrement.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUdpSocket>
#include <QMessageBox>

InterfaceEnregistrement::InterfaceEnregistrement(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::InterfaceEnregistrement)
{
    ui->setupUi(this);
    ui->labelAppelProf->hide();

    // Pour fixer la taille de la page et le titre
    setFixedSize(800, 480);
    this->setWindowTitle("Page d'Enregistrement");
    connect(ui->pushButtonPause, &QPushButton::clicked,
            this, &InterfaceEnregistrement::on_pushButtonPause_clicked);

    // Initialisation des autres composants et variables
    mediaRecorder = new QMediaRecorder(this);
    player = new QMediaPlayer(this);
    audioInput = new QAudioInput(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &InterfaceEnregistrement::updateChrono);
    mediaRecorder = new QMediaRecorder(this);
    audioInput = new QAudioInput(this);
    captureSession.setAudioInput(audioInput);
    captureSession.setRecorder(mediaRecorder);
    QMediaFormat fmt;
    fmt.setFileFormat(QMediaFormat::FileFormat::Wave);
    fmt.setAudioCodec(QMediaFormat::AudioCodec::Wave);  // ← fonctionne sur Linux / PulseAudio
    mediaRecorder->setMediaFormat(fmt);


    rewindTimer = new QTimer(this);
    captureSession.setAudioInput(audioInput);
    captureSession.setRecorder(mediaRecorder);

    connect(timer, &QTimer::timeout, this, &InterfaceEnregistrement::updateChrono);
    connect(rewindTimer, &QTimer::timeout, this, &InterfaceEnregistrement::rewindChrono);
    connect(mediaRecorder, &QMediaRecorder::recorderStateChanged, this, &InterfaceEnregistrement::onRecorderStateChanged);
    connect(mediaRecorder, &QMediaRecorder::errorOccurred, this, &InterfaceEnregistrement::onRecorderErrorOccurred);

    // Affichage des Images
    setButtonIcons();

    isRewinding = false;
    totalSecondes = 0;
    speakButtonClicked = false;
    isButtonSpeak = false;
    isRecordingPaused = false;
    lastRecordedTime = 0;
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
    setIcon(ui->pushButtonSurveiller, ":/images/PasSurveiller");
    setIcon(ui->pushButtonEnregistrer, ":/images/Enregistrer");
    setIcon(ui->pushButtonRetourArriere, ":/images/RevenirArriere");
    setIcon(ui->pushButtonPause, ":/images/Pause");
    setIcon(ui->pushButtonAvancer, ":/images/Avancer");
    setIcon(ui->pushButtonSpeak, ":/images/Enregistrement");
    setIcon(ui->pushButtonClear, ":/images/Effacer");
    setIcon(ui->pushButtonAppelProf, ":/images/CallProf");
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

    totalSecondes = 0;
    ui->labelChrono->setText("00:00:00");
    mediaRecorder->setOutputLocation(QUrl::fromLocalFile(audioFilePath));
    timer->start(1000);
    mediaRecorder->record();
    isRecordingPaused = false;
    qDebug() << "Nouvel enregistrement démarré.";
}

void InterfaceEnregistrement::on_pushButtonPause_clicked()
{
    if (mediaRecorder->recorderState() == QMediaRecorder::RecordingState) {
        mediaRecorder->pause();
        isRecordingPaused = true;
        pausedTime = totalSecondes;
        timer->stop();
        qDebug() << "Enregistrement et chrono mis en pause.";
    } else if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
        qDebug() << "Lecture mise en pause.";
    }
}

void InterfaceEnregistrement::on_pushButtonClear_clicked()
{
    if (mediaRecorder->recorderState() == QMediaRecorder::RecordingState) {
        mediaRecorder->stop();
        qDebug() << "Enregistrement arrêté.";
    }

    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->stop();
        qDebug() << "Lecture stoppée.";
    }

    if (QFile::exists(audioFilePath)) {
        QFile::remove(audioFilePath);
        qDebug() << "Enregistrement supprimé.";
    }

    totalSecondes = 0;
    ui->labelChrono->setText("00:00:00");
    speakButtonClicked = false;
    qDebug() << "Tout a été réinitialisé.";
}

void InterfaceEnregistrement::on_pushButtonSon_clicked()
{
    QDialog popup(this);
    popup.setWindowTitle("Réglages du Son");
    popup.setModal(true);

    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 100);
    int volume = static_cast<int>(audioOutput->volume() * 100);
    slider->setValue(volume);
    audioOutput->setVolume(volume / 100.0);

    QLabel *label = new QLabel("Son");
    QPushButton *closeButton = new QPushButton("Fermer");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *slidersLayout = new QHBoxLayout;
    slidersLayout->addWidget(label);
    slidersLayout->addWidget(slider);
    mainLayout->addLayout(slidersLayout);
    mainLayout->addWidget(closeButton);
    popup.setLayout(mainLayout);

    QObject::connect(slider, &QSlider::valueChanged, this, [=](int value) {
        audioOutput->setVolume(value / 100.0);
        qDebug() << "Volume réglé à :" << value;
    });

    QObject::connect(closeButton, &QPushButton::clicked, &popup, &QDialog::accept);
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

void InterfaceEnregistrement::updateChrono()
{
    if (isRewinding) {
        return;
    }
    totalSecondes++;
    updateChronoLabel();
}

void InterfaceEnregistrement::rewindChrono()
{
    if (totalSecondes > 1) {
        lastRecordedTime = totalSecondes;
    }

    if (totalSecondes > 0) {
        totalSecondes--;
        updateChronoLabel();
    } else {
        qDebug() << "Chrono à zéro, dernier temps enregistré : " << lastRecordedTime;
        rewindTimer->stop();
        isRewinding = false;
    }
}

void InterfaceEnregistrement::updateChronoLabel()
{
    int heures = totalSecondes / 3600;
    int minutes = (totalSecondes % 3600) / 60;
    int secondes = totalSecondes % 60;
    ui->labelChrono->setText(QString::number(heures).rightJustified(2, '0') + ":" +
                             QString::number(minutes).rightJustified(2, '0') + ":" +
                             QString::number(secondes).rightJustified(2, '0'));
}

void InterfaceEnregistrement::on_pushButtonAppelProf_clicked()
{
    ui->pushButtonAppelProf->setStyleSheet("QPushButton { background-color: none; border: none; }");
    ui->labelAppelProf->show();
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

void InterfaceEnregistrement::on_pushButtonEnregistrer_clicked()
{

    if (mediaRecorder->recorderState() == QMediaRecorder::RecordingState) {
        mediaRecorder->stop();
        ui->pushButtonEnregistrer->setText("Enregistrer");
        qDebug() << "Enregistrement arrêté :" << audioFilePath;
        return;
    }

    // Génération du nom : YYYYMMDD_hhmmss_id<studentId>.wav
    const QString docs = QStandardPaths::writableLocation(
        QStandardPaths::DocumentsLocation);
    const QString timestamp = QDateTime::currentDateTime()
                                  .toString("yyyyMMdd_hhmmss");
    audioFilePath = QString("%1/%2_id%3.wav")
                        .arg(docs)
                        .arg(timestamp)
                        .arg(studentId);

    if (QFile::exists(audioFilePath))
        QFile::remove(audioFilePath);

    // --- CORRECTION ICI ---
    QMediaFormat fmt;
    fmt.setFileFormat(QMediaFormat::FileFormat::Wave);           // .wav
    // fmt.setAudioCodec(QMediaFormat::AudioCodec::Wave);        // optionnel
    mediaRecorder->setMediaFormat(fmt);
    mediaRecorder->setOutputLocation(QUrl::fromLocalFile(audioFilePath));

    mediaRecorder->record();
    ui->pushButtonEnregistrer->setText("Arrêter");
    timer->start(1000);
    qDebug() << "Enregistrement démarré dans :" << audioFilePath;


    qDebug() << "Bouton Enregistrer cliqué";
    QMediaCaptureSession *session = new QMediaCaptureSession(this);
    QAudioInput *audioInput = new QAudioInput(this);
    QMediaRecorder *recorder = new QMediaRecorder(this);
    session->setAudioInput(audioInput);
    session->setRecorder(recorder);
    QMediaFormat format;
    format.setFileFormat(QMediaFormat::Mpeg4Audio);
    recorder->setMediaFormat(format);
    recorder->setOutputLocation(QUrl::fromLocalFile("output.mp3"));
    recorder->record();

}

void InterfaceEnregistrement::showFeedbackDialog()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Donner votre avis");
    QLabel *label = new QLabel("Merci de donner votre avis sur cette activité :", dialog);
    QTextEdit *feedbackEdit = new QTextEdit(dialog);
    QSpinBox *ratingSpin = new QSpinBox(dialog);
    ratingSpin->setRange(1, 5);
    QPushButton *submitBtn = new QPushButton("Envoyer", dialog);
    QPushButton *cancelBtn = new QPushButton("Annuler", dialog);
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(label);
    layout->addWidget(feedbackEdit);
    layout->addWidget(new QLabel("Notez cette activité (1 à 5) :"));
    layout->addWidget(ratingSpin);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(submitBtn);
    layout->addLayout(btnLayout);

    connect(submitBtn, &QPushButton::clicked, this, [=]() {
        QString feedback = feedbackEdit->toPlainText();
        int rating = ratingSpin->value();
        if (!feedback.isEmpty()) {
            QFile file("feedback.txt");
            if (file.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&file);
                out << "Feedback: " << feedback << "\n";
                out << "Note: " << rating << "\n";
                file.close();
            }
            QMessageBox::information(dialog, "Merci", "Votre avis a été enregistré.");
        } else {
            QMessageBox::warning(dialog, "Erreur", "Veuillez écrire un commentaire.");
        }
        dialog->accept();
    });

    connect(cancelBtn, &QPushButton::clicked, dialog, &QDialog::reject);
    dialog->exec();
}
