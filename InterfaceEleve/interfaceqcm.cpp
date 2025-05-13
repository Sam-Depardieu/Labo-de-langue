#include "interfaceqcm.h"
#include "interfaceenregistrement.h"
#include "ui_interfaceqcm.h"

InterfaceQCM::InterfaceQCM(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceQCM)
    , isButton1Image(true)
    , isButton2Image(true)
    , isButton3Image(true)
    , isButton4Image(true)
{
    ui->setupUi(this);
    setFixedSize(800,480);
    this->setWindowTitle("Page de QCM");
    // Affichage des Images
    setButtonIcons();

    udpSocketConsigne.bind(QHostAddress::Any, consignePort);
    connect(&udpSocketConsigne, &QUdpSocket::readyRead, this, &InterfaceQCM::receiveResponse);
    udpChrono.bind(QHostAddress::Any, chronoPort);

    // 2) dès qu’on reçoit un datagramme, on va parse mm:ss et fermer
    connect(&udpChrono, &QUdpSocket::readyRead,
            this,     &InterfaceQCM::onUdpTimeout);

    if (!Professor) {
        ui->textEditFeedBack->setReadOnly(true); // Bloquer l'accès en écriture
        ui->textEditConsigne->setReadOnly(true); // Bloquer l'accès en écriture
        ui->textEditAffichageQuestion->setReadOnly(true); // Bloquer l'accès en écriture
    }

    loadQuestionsJson(R"("\\CIEL-T171-05\Activites\qsdfgsdg_2025-05-12_14-54\questions.qcmlabo")");

    currentQuestionIndex = 0;
    showCurrentQuestion();
}

InterfaceQCM::~InterfaceQCM()
{
    delete ui;
}

void InterfaceQCM::onUdpTimeout()
{
    while (udpChrono.hasPendingDatagrams()) {
        QByteArray dg;
        dg.resize(udpChrono.pendingDatagramSize());
        udpChrono.readDatagram(dg.data(), dg.size());
        QString s = QString::fromUtf8(dg).trimmed();

        auto parts = s.split(':');
        if (parts.size()==2) {
            int m = parts[0].toInt();
            int sec = parts[1].toInt();
            int ms = (m*60 + sec) * 1000;
            QTimer::singleShot(ms, this, &QDialog::accept);
        }
    }
}

void InterfaceQCM::loadQuestionsJson(const QString &filePath)
{
    QFile file(filePath);
    qDebug() << "📂 Tentative d'ouverture du fichier :" << filePath;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "❌ Impossible d'ouvrir le fichier : " << file.errorString();
        return;
    }

    QByteArray data = file.readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "❌ Erreur de parsing JSON :" << error.errorString();
        return;
    }

    if (!doc.isObject()) {
        qWarning() << "❌ Format invalide : le document JSON n’est pas un objet.";
        return;
    }

    QJsonObject root = doc.object();
    questionArray = root["questions"].toArray();
    qDebug() << "✅ Questions chargées :" << questionArray.size();
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

    // Réinitialiser les boutons
    if (answers.size() > 0) {
        ui->pushButton1->setText(answers[0].toObject()["text"].toString());
        ui->pushButton1->setVisible(true);
    } else {
        ui->pushButton1->setVisible(false);
    }

    if (answers.size() > 1) {
        ui->pushButton2->setText(answers[1].toObject()["text"].toString());
        ui->pushButton2->setVisible(true);
    } else {
        ui->pushButton2->setVisible(false);
    }

    if (answers.size() > 2) {
        ui->pushButton3->setText(answers[2].toObject()["text"].toString());
        ui->pushButton3->setVisible(true);
    } else {
        ui->pushButton3->setVisible(false);
    }

    if (answers.size() > 3) {
        ui->pushButton4->setText(answers[3].toObject()["text"].toString());
        ui->pushButton4->setVisible(true);
    } else {
        ui->pushButton4->setVisible(false);
    }

    on_pushButtonEffacerReponse_clicked();
}

void InterfaceQCM::on_pushButtonQuestionSuivante_clicked()
{
    if (currentQuestionIndex >= questionArray.size()) {
        qDebug() << "❌ Aucune question suivante à afficher.";
        return;
    }

    QJsonObject currentQuestion = questionArray[currentQuestionIndex].toObject();
    QJsonArray answers = currentQuestion["answers"].toArray();

    QString fileName = "C:/Users/Quentin/Documents/Projet/responses.txt";
    QFile file(fileName);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Erreur : impossible d'ouvrir le fichier pour écrire.";
        return;
    }

    QTextStream out(&file);
    out << QString("Question %1:\n").arg(currentQuestionIndex + 1);

    if (!isButton1Image) {
        QString emoji = answers[0].toObject()["isCorrect"].toBool() ? "✅" : "❌";
        QString buttonText = ui->pushButton1->text();
        out << QString("- %1 %2\n").arg(buttonText).arg(emoji);
    }
    if (!isButton2Image) {
        QString emoji = answers[1].toObject()["isCorrect"].toBool() ? "✅" : "❌";
        QString buttonText = ui->pushButton2->text();
        out << QString("- %1 %2\n").arg(buttonText).arg(emoji);
    }
    if (!isButton3Image) {
        QString emoji = answers[2].toObject()["isCorrect"].toBool() ? "✅" : "❌";
        QString buttonText = ui->pushButton3->text();
        out << QString("- %1 %2\n").arg(buttonText).arg(emoji);
    }
    if (!isButton4Image) {
        QString emoji = answers[3].toObject()["isCorrect"].toBool() ? "✅" : "❌";
        QString buttonText = ui->pushButton4->text();
        out << QString("- %1 %2\n").arg(buttonText).arg(emoji);
    }

    out << "\n";
    file.close();

    // Aller à la question suivante (si possible)
    currentQuestionIndex++;

    if (currentQuestionIndex < questionArray.size()) {
        showCurrentQuestion();
    } else {
        qDebug() << "✅ Dernière question atteinte. Fin du QCM.";

        // Appel automatique de la popup pour soumettre
        on_pushButtonSoumettre_clicked();
    }
}

void InterfaceQCM::setButtonIcons()
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

    setIcon(ui->pushButtonEffacerReponse, ":/images/Effacer");
    setIcon(ui->pushButtonQuestionSuivante, ":/images/Avancer");
    setIcon(ui->pushButtonQuestionPrecedente, ":/images/RevenirArriere");
    setIcon(ui->pushButtonSoumettre, ":/images/Enregistrer");
}

void InterfaceQCM::on_pushButton1_clicked()
{
    ui->pushButton1->setStyleSheet("QPushButton { background-color:blue;border: 3px solid white;border-radius: 20px;}");
    isButton1Image = false;
}

void InterfaceQCM::on_pushButton2_clicked()
{
    ui->pushButton2->setStyleSheet("QPushButton { background-color:green;border: 3px solid white;border-radius: 20px; }");
    isButton2Image = false;
}

void InterfaceQCM::on_pushButton3_clicked()
{
    ui->pushButton3->setStyleSheet("QPushButton { background-color:red;border: 3px solid white;border-radius: 20px; }");
    isButton3Image = false;
}

void InterfaceQCM::on_pushButton4_clicked()
{
    ui->pushButton4->setStyleSheet("QPushButton { background-color:orange;border: 3px solid white;border-radius: 20px; }");
    isButton4Image = false;
}

void InterfaceQCM::on_pushButtonEffacerReponse_clicked()
{
    ui->pushButton1->setStyleSheet("QPushButton { background-color:blue; border-radius: 20px; }");
    ui->pushButton2->setStyleSheet("QPushButton { background-color:green; border-radius: 20px; }");
    ui->pushButton3->setStyleSheet("QPushButton { background-color:red;border-radius: 20px; }");
    ui->pushButton4->setStyleSheet("QPushButton { background-color:orange;border-radius: 20px; }");

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
        quint16 senderPort;

        udpSocketConsigne.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString response = QString::fromUtf8(datagram).trimmed();
        qDebug() << "📢 Réponse reçue de" << sender.toString() << ":" << response;

        if (!response.isEmpty()) {
            consigne = response;
        }
    }
}

void InterfaceQCM::on_pushButtonQuestionPrecedente_clicked()
{
    if (currentQuestionIndex <= 0) {
        qDebug() << "❌ Pas de question précédente.";
        return;
    }

    currentQuestionIndex--;
    showCurrentQuestion();
}

void InterfaceQCM::on_pushButtonSoumettre_clicked()
{
    // Affichage popup pour soumettre les réponses
    QMessageBox::information(this, "Soumettre les réponses", "Vos réponses ont été enregistrées.");
    // Ferme la fenêtre QCM après soumission
    accept();
}
