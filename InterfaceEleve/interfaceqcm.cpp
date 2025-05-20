#include "interfaceqcm.h"
#include "mainwindow.h"
#include "ui_interfaceqcm.h"

InterfaceQCM::InterfaceQCM(MainWindow *parentWindow,const QString &filePath,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceQCM)
    , isButton1Image(true)
    , isButton2Image(true)
    , isButton3Image(true)
    , isButton4Image(true)
{
    ui->setupUi(this);
    setFixedSize(800, 480);
    setWindowTitle("Page de QCM");

    setButtonIcons();
    //Consigne
    if (!udpSocketConsigne.bind(QHostAddress::Any, consignePort)) {
        qWarning() << "❌ Impossible de binder le port UDP pour la consigne.";
    }
    connect(&udpSocketConsigne, &QUdpSocket::readyRead, this, &InterfaceQCM::receiveResponse);
    //Chrono
    if (!udpChrono.bind(QHostAddress::Any, chronoPort)) {
        qWarning() << "❌ Impossible de binder le port UDP pour le chrono.";
    }
    //Recup Fichier
    // Socket pour recevoir un chemin de fichier
    /*if (!udpSocketNomFichier.bind(QHostAddress::Any, portNomFichier)) {
        qWarning() << "❌ Impossible de binder le port UDP pour le fichier JSON.";
    }
    connect(&udpSocketNomFichier, &QUdpSocket::readyRead, this, &InterfaceQCM::onUdpNomFichierRecu);*/



    if (!Professor) {
        ui->textEditFeedBack->setReadOnly(true);
        ui->textEditConsigne->setReadOnly(true);
        ui->textEditAffichageQuestion->setReadOnly(true);
    }

    if (!QFile::exists(filePath)) {
        qWarning() << "❌ Fichier non trouvé :" << filePath;
    }

    loadQuestionsJson(filePath);
    currentQuestionIndex = 0;
    showCurrentQuestion();
    ui->chronoLabel->setVisible(true);

    remainingTime = parentWindow->getTime();

    // Initialisation des timers
    chronoTimer = new QTimer(this);
    connect(chronoTimer, &QTimer::timeout, this, &InterfaceQCM::updateChronoLabel);

    clignotementTimer = new QTimer(this);
    connect(clignotementTimer, &QTimer::timeout, this, &InterfaceQCM::faireClignoterLabel);

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

void InterfaceQCM::faireClignoterLabel()
{
    clignotementEtat = !clignotementEtat;
    if (clignotementEtat)
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: red; border: 2px solid red; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
    else
        ui->chronoLabel->setStyleSheet("background-color: #0097a7; color: white; border: 2px solid white; border-radius: 8px; font-family: 'Segoe UI', 'Arial', sans-serif; font-weight: bold; font-size: 28px; padding: 5px 15px; qproperty-alignment: 'AlignCenter';");
}

void InterfaceQCM::updateChronoLabel()
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


InterfaceQCM::~InterfaceQCM()
{
    delete ui;
}

void InterfaceQCM::onUdpNomFichierRecu()
{
    while (udpSocketNomFichier.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketNomFichier.pendingDatagramSize());
        udpSocketNomFichier.readDatagram(datagram.data(), datagram.size());

        fichierRecu = QString::fromUtf8(datagram).trimmed();
        qDebug() << "📁 Chemin de fichier JSON reçu par UDP :" << fichierRecu;

        // Charger les questions si le fichier est bien reçu
        if (QFile::exists(fichierRecu)) {
            loadQuestionsJson(fichierRecu);
            currentQuestionIndex = 0;
            showCurrentQuestion();
        } else {
            qWarning() << "❌ Fichier JSON non trouvé :" << fichierRecu;
        }
    }
}


void InterfaceQCM::loadQuestionsJson(const QString &filePath)
{
    QFile file(filePath);
    qDebug() << "📂 Ouverture du fichier JSON :" << filePath;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "❌ Échec d'ouverture : " << file.errorString();
        return;
    }

    QByteArray data = file.readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "❌ Erreur JSON : " << error.errorString();
        qWarning() << "Position de l'erreur : " << error.offset;
        return;
    }

    if (!doc.isObject()) {
        qWarning() << "❌ JSON invalide : document racine non-objet.";
        return;
    }

    QJsonObject root = doc.object();
    if (root.contains("questions") && root["questions"].isArray()) {
        questionArray = root["questions"].toArray();
        qDebug() << "✅ Nombre de questions chargées :" << questionArray.size();
    } else {
        qWarning() << "❌ Clé 'questions' manquante ou invalide.";
    }
}

void InterfaceQCM::showCurrentQuestion()
{
    if (currentQuestionIndex < 0 || currentQuestionIndex >= questionArray.size()) {
        qWarning() << "❌ Index de question invalide.";
        return;
    }

    QJsonObject currentQuestion = questionArray[currentQuestionIndex].toObject();
    QString questionText = currentQuestion["text"].toString();
    ui->labelQuestion->setText(questionText);

    QJsonArray answers = currentQuestion["answers"].toArray();

    ui->pushButton1->setVisible(answers.size() > 0);
    ui->pushButton2->setVisible(answers.size() > 1);
    ui->pushButton3->setVisible(answers.size() > 2);
    ui->pushButton4->setVisible(answers.size() > 3);

    if (answers.size() > 0) ui->pushButton1->setText(answers[0].toObject()["text"].toString());
    if (answers.size() > 1) ui->pushButton2->setText(answers[1].toObject()["text"].toString());
    if (answers.size() > 2) ui->pushButton3->setText(answers[2].toObject()["text"].toString());
    if (answers.size() > 3) ui->pushButton4->setText(answers[3].toObject()["text"].toString());

    on_pushButtonEffacerReponse_clicked();
    ui->pushButtonSoumettre->setEnabled(currentQuestionIndex == questionArray.size() - 1);
}

void InterfaceQCM::setButtonIcons()
{
    auto setIcon = [](QPushButton *button, const QString &path) {
        QPixmap pixmap(path);
        if (!pixmap.isNull()) {
            QIcon icon(pixmap);
            button->setIcon(icon);
            button->setIconSize(button->size());
        } else {
            qWarning() << "❌ Image introuvable :" << path;
        }
    };

    setIcon(ui->pushButtonEffacerReponse, ":/images/Effacer");
    setIcon(ui->pushButtonQuestionSuivante, ":/images/Avancer");
    setIcon(ui->pushButtonQuestionPrecedente, ":/images/RevenirArriere");
    setIcon(ui->pushButtonSoumettre, ":/images/Enregistrer");
}

void InterfaceQCM::on_pushButton1_clicked()
{
    ui->pushButton1->setStyleSheet("background-color:blue; border:3px solid white; border-radius:20px;");
    isButton1Image = false;
}

void InterfaceQCM::on_pushButton2_clicked()
{
    ui->pushButton2->setStyleSheet("background-color:green; border:3px solid white; border-radius:20px;");
    isButton2Image = false;
}

void InterfaceQCM::on_pushButton3_clicked()
{
    ui->pushButton3->setStyleSheet("background-color:red; border:3px solid white; border-radius:20px;");
    isButton3Image = false;
}

void InterfaceQCM::on_pushButton4_clicked()
{
    ui->pushButton4->setStyleSheet("background-color:orange; border:3px solid white; border-radius:20px;");
    isButton4Image = false;
}

void InterfaceQCM::on_pushButtonEffacerReponse_clicked()
{
    ui->pushButton1->setStyleSheet("background-color:blue; border-radius:20px;");
    ui->pushButton2->setStyleSheet("background-color:green; border-radius:20px;");
    ui->pushButton3->setStyleSheet("background-color:red; border-radius:20px;");
    ui->pushButton4->setStyleSheet("background-color:orange; border-radius:20px;");

    isButton1Image = true;
    isButton2Image = true;
    isButton3Image = true;
    isButton4Image = true;
}

void InterfaceQCM::receiveResponse()
{
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

void InterfaceQCM::on_pushButtonQuestionSuivante_clicked()
{
    if (currentQuestionIndex < questionArray.size() - 1) {
        currentQuestionIndex++;
        showCurrentQuestion();
    }
}

void InterfaceQCM::on_pushButtonQuestionPrecedente_clicked()
{
    if (currentQuestionIndex > 0) {
        currentQuestionIndex--;
        showCurrentQuestion();
    }
}

void InterfaceQCM::on_pushButtonSoumettre_clicked()
{
    if (currentQuestionIndex < 0 || currentQuestionIndex >= questionArray.size()) return;

    const QString docs = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    const QString folder = QDir(docs).filePath("Travail");
    if (!QDir(folder).exists()) QDir().mkpath(folder);

    const QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    const QString filePath = QDir(folder).filePath(timestamp + ".txt");

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "❌ Impossible d’écrire dans le fichier.";
        return;
    }

    QTextStream out(&file);
    QJsonObject currentQuestion = questionArray[currentQuestionIndex].toObject();
    QJsonArray answers = currentQuestion["answers"].toArray();

    out << QString("Question %1:\n").arg(currentQuestionIndex + 1);
    if (!isButton1Image && answers.size() > 0)
        out << QString("- %1 %2\n").arg(ui->pushButton1->text(), answers[0].toObject()["isCorrect"].toBool() ? "✅" : "❌");
    if (!isButton2Image && answers.size() > 1)
        out << QString("- %1 %2\n").arg(ui->pushButton2->text(), answers[1].toObject()["isCorrect"].toBool() ? "✅" : "❌");
    if (!isButton3Image && answers.size() > 2)
        out << QString("- %1 %2\n").arg(ui->pushButton3->text(), answers[2].toObject()["isCorrect"].toBool() ? "✅" : "❌");
    if (!isButton4Image && answers.size() > 3)
        out << QString("- %1 %2\n").arg(ui->pushButton4->text(), answers[3].toObject()["isCorrect"].toBool() ? "✅" : "❌");

    file.close();
    QMessageBox::information(this, "Soumission", "Réponses enregistrées.");
    accept();
}


