#include "interfaceenregistrement.h"
#include "ui_interfaceenregistrement.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUdpSocket>
#include <QMessageBox>
#include <QDir>
#include "mainwindow.h"

InterfaceEnregistrement::InterfaceEnregistrement(MainWindow* parentWindow, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceEnregistrement)
    , mainWindow(parentWindow)
    , isButtonAppelProfImage(true)
{
    ui->setupUi(this);
    setFixedSize(800, 480);
    setWindowTitle("Page d'Enregistrement");

    ui->pushButtonPause->setVisible(true);
    ui->pushButtonPlay->setVisible(false);
    ui->verticalSlider_sonVideo->setVisible(false);

    udpSocket.bind(QHostAddress::Any, responsePort);
    connect(&udpSocket, &QUdpSocket::readyRead, this, &InterfaceEnregistrement::receiveResponse);

    audioInput = new QAudioInput(this);
    mediaRecorder = new QMediaRecorder(this);
    audioOutput = new QAudioOutput(this);
    player = new QMediaPlayer(this);
    player->setAudioOutput(audioOutput);

    captureSession.setAudioInput(audioInput);
    captureSession.setRecorder(mediaRecorder);

    QMediaFormat fmt;
    fmt.setFileFormat(QMediaFormat::FileFormat::Wave);
    mediaRecorder->setMediaFormat(fmt);

    timer = new QTimer(this);
    rewindTimer = new QTimer(this);

    connect(rewindTimer, &QTimer::timeout,this, &InterfaceEnregistrement::rewindChrono);
    connect(timer, &QTimer::timeout,this, &InterfaceEnregistrement::updateChrono);
    connect(mediaRecorder, &QMediaRecorder::recorderStateChanged, this, &InterfaceEnregistrement::onRecorderStateChanged);
    connect(mediaRecorder, &QMediaRecorder::errorOccurred, this, &InterfaceEnregistrement::onRecorderErrorOccurred);
    connect(ui->pushButtonRetourArriere, &QPushButton::clicked,this, &InterfaceEnregistrement::on_pushButtonRetourArriere_clicked);

    setButtonIcons();

    isRewinding = false;
    totalSecondes = 0;
    lastRecordedTime = 0;

    QFile file("feedback.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "";
        file.close();
    }

    if (!Professor) {
        ui->textEditFeedBack->setReadOnly(true);
        ui->textEditFeedBack->setPlaceholderText("Accès réservé aux professeurs");
        ui->textEditConsigne->setReadOnly(true);
    }

    ui->textEditConsigne->setText(mainWindow->getConsigne());

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

    ui->chronoLabel->setVisible(true);
    ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: white; border: 2px solid white; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");

    if (remainingTime.isValid() && remainingTime != QTime(0, 0)) {
        ui->chronoLabel->setText(remainingTime.toString("mm:ss"));
        chronoTimer->start(1000);
    } else {
        ui->chronoLabel->setText("00:00");
        ui->chronoLabel->setVisible(false);

    }

    loadConsigneJson(sessionPATH);

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

void InterfaceEnregistrement::loadConsigneJson(QString &filePath)
{
    QString cheminConsigne = QString("%1/config.labo").arg(filePath);
    QFile file(cheminConsigne);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erreur Impossible d'ouvrir le fichier consigne JSON.";
        ui->pushButtonAppelProf->hide();

        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull() || !doc.isObject()) {
        qWarning() << "Erreur Le fichier consigne JSON n'est pas valide.";
        return;
    }

    QJsonObject obj = doc.object();

    // Extraction du port
    QString portStr = obj.value("port").toString();
    bool ok;
    quint16 portNum = portStr.toUShort(&ok);
    if (ok) {
        consignePort = portNum;
        qDebug() << "Port consigne chargé:" << consignePort;
    } /*else {
        qWarning() << "Conversion du port consigne impossible, valeur par défaut utilisée:" << consignePort;
    }*/

    // Extraction de la consigne
    consigne = obj.value("consigne").toString();

    // Affichage dans le textEditConsigne avec "Consigne :"
    QString currentText = ui->textEditConsigne->toPlainText(); // Conserve l'ancien texte
    currentText += QString(" %1\n").arg(consigne);   // Ajoute la nouvelle consigne formatée
    ui->textEditConsigne->setPlainText(currentText);           // Met à jour le champ texte
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

    setIcon(ui->pushButtonSon, ":/images/sonVid");
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
    if (mediaRecorder->recorderState() != QMediaRecorder::StoppedState) {
        mediaRecorder->stop();
    }

    const QString docs = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    const QString folder = QDir(docs).filePath("Travail");
    if (!QDir(folder).exists()) {
        QDir().mkpath(folder);
    }

    audioFilePath = QDir(folder).filePath("audio.wav");
    if (QFile::exists(audioFilePath)) {
        QFile::remove(audioFilePath);
    }
    QMediaFormat fmt;
    fmt.setFileFormat(QMediaFormat::FileFormat::Wave);
    mediaRecorder->setMediaFormat(fmt);
    mediaRecorder->setOutputLocation(QUrl::fromLocalFile(audioFilePath));
    mediaRecorder->record();
    timer->start(1000);
    ui->pushButtonPause->setVisible(true);
    ui->pushButtonPlay->setVisible(false);
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
        ui->pushButtonPlay->setVisible(true);
    }

    totalSecondes = 0;
    ui->chrono_enregistrement->setText("00:00:00");

    QMessageBox::information(this, "Enregistrement", "Enregistrement terminé et sauvegardé.");
    ui->pushButtonPlay->setVisible(false);
    ui->pushButtonPause->setVisible(true);
}

void InterfaceEnregistrement::on_pushButtonPause_clicked()
{
    if (isRewinding) {
        rewindTimer->stop();
        isRewinding = false;
    }
    if (timer->isActive())
        timer->stop();

    if (mediaRecorder->recorderState() == QMediaRecorder::RecordingState)
        mediaRecorder->pause();

    ui->pushButtonPause->setVisible(false);
    ui->pushButtonPlay->setVisible(true);
}

void InterfaceEnregistrement::on_pushButtonPlay_clicked()
{
    if (!timer->isActive())
        timer->start(1000);

    if (mediaRecorder->recorderState() == QMediaRecorder::PausedState)
        mediaRecorder->record();

    ui->pushButtonPlay->setVisible(false);
    ui->pushButtonPause->setVisible(true);
}

void InterfaceEnregistrement::on_pushButtonClear_clicked()
{
    animateButtonClick(ui->pushButtonClear);
    if (timer->isActive()) {
        timer->stop();
    }

    totalSecondes = 0;
    updateChronoLabel();
    ui->pushButtonPause->setVisible(true);
    ui->pushButtonPlay->setVisible(false);
}

void InterfaceEnregistrement::on_pushButtonRetourArriere_clicked()
{
    if (timer->isActive())
        timer->stop();

    ui->pushButtonPause->setVisible(true);
    ui->pushButtonPlay->setVisible(false);

    if (totalSecondes == 0 && lastRecordedTime > 0) {
        totalSecondes = lastRecordedTime;
        updateChronoLabel();
        return;
    }

    if (totalSecondes > 0 && !isRewinding) {
        isRewinding = true;
        rewindTimer->start(100);
    }
}

void InterfaceEnregistrement::rewindChrono()
{
    if (totalSecondes > 0) {
        totalSecondes--;
        updateChronoLabel();
    } else {
        rewindTimer->stop();
        isRewinding = false;
        ui->pushButtonPause->setVisible(true);
        ui->pushButtonPlay->setVisible(false);
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
            clignotementTimer->start(500);
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

    if (!mainWindow) {
        qDebug() << "[InterfaceEnregistrement] mainWindow est null, impossible d'envoyer le message";
        return;
    }

    QString ipProf = mainWindow->getIpProf(); // Récupérer l'adresse IP du professeur
    qDebug() << "[InterfaceEnregistrement] Adresse IP prof récupérée :" << ipProf; // Log pour vérifier l'adresse IP du professeur
    if (ipProf.isEmpty()) {
        qDebug() << "[InterfaceEnregistrement] IP Prof vide, envoi annulé";
        return;
    }

    quint16 port = 5557;
    QString message = "help"; // Message à envoyer

    mainWindow->sendCommandToProf(ipProf, port, message);
}

void InterfaceEnregistrement::checkPlaybackPosition(qint64 position)
{
    if( position /1000 >= totalSecondes){
        player->stop();
    }
}

void InterfaceEnregistrement::onRecorderStateChanged(QMediaRecorder::RecorderState state)
{
    switch (state) {
    case QMediaRecorder::RecordingState:
        break;
    case QMediaRecorder::PausedState:
        break;
    case QMediaRecorder::StoppedState:
        break;
    }
}

void InterfaceEnregistrement::onRecorderErrorOccurred(QMediaRecorder::Error error, const QString &errorString)
{
    qDebug() << "Erreur d'enregistrement:" << errorString;
}

void InterfaceEnregistrement::animateButtonClick(QPushButton* btn) {
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

void InterfaceEnregistrement::on_pushButtonSon_clicked()
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

        if (response.trimmed() != "") {
            QFile file("feedback.txt");
            if (file.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&file);
                out << response << "\n";
                file.close();
            }

            QFile inFile("feedback.txt");
            if (inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&inFile);
                QString contenu = in.readAll();
                inFile.close();
                ui->textEditFeedBack->setText(contenu);
            }
        }
    }
    while (udpSocketConsigne.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketConsigne.pendingDatagramSize());
        QHostAddress sender;
        quint16 port;
        udpSocketConsigne.readDatagram(datagram.data(), datagram.size(), &sender, &port);
        QString response = QString::fromUtf8(datagram).trimmed();
        qDebug() << "📢 Reçu :" << response;
    }
}
