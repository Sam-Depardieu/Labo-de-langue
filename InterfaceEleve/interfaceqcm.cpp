#include "interfaceqcm.h"
#include "interfaceenregistrement.h"
#include "ui_interfaceqcm.h"

InterfaceQCM::InterfaceQCM(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceQCM)
    //Declaration des Image de base des ronds
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

    // Vérifier si l'utilisateur est un professeur
    if (!isTeacher) {
        ui->textEditFeedBack->setReadOnly(true); // Bloquer l'accès en écriture
        ui->textEditConsigne->setReadOnly(true); // Bloquer l'accès en écriture
    }

    loadQuestions(R"(\\CIEL-T171-05\Activites\questions.qcmlabo)");
    showCurrentQuestion();

}

InterfaceQCM::~InterfaceQCM()
{
    delete ui;
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

    ui->pushButton3->setStyleSheet("QPushButton {  background-color:red;border: 3px solid white;border-radius: 20px; }");
    isButton3Image = false;
}


void InterfaceQCM::on_pushButton4_clicked()
{

    ui->pushButton4->setStyleSheet("QPushButton { background-color:orange;border: 3px solid white;border-radius: 20px; }");
    isButton4Image = false;
}

void InterfaceQCM::on_pushButtonEffacerReponse_clicked()
{
    // On ne touche qu'à la bordure : le reste du style .ui reste intact
    ui->pushButton1->setStyleSheet("QPushButton { background-color:blue; border-radius: 20px; }");
    ui->pushButton2->setStyleSheet("QPushButton { background-color:green; border-radius: 20px; }");
    ui->pushButton3->setStyleSheet("QPushButton { background-color:red;border-radius: 20px; }");
    ui->pushButton4->setStyleSheet("QPushButton { background-color:orange;border-radius: 20px; }");

    // Réinitialiser les flags
    isButton1Image = true;
    isButton2Image = true;
    isButton3Image = true;
    isButton4Image = true;
}



void InterfaceQCM::on_pushButtonQuestionSuivante_clicked()
{
    // Chemin relatif
    QString fileName = "C:/Users/Quentin/Documents/Projet/responses.txt";
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Erreur : impossible d'ouvrir le fichier pour écrire.";
        return;
    }

    QTextStream out(&file);
    out << "Réponses enregistrées :\n";

    if (!isButton1Image) {
        out << "Réponse 1 sélectionnée\n";
    }
    if (!isButton2Image) {
        out << "Réponse 2 sélectionnée\n";
    }
    if (!isButton3Image) {
        out << "Réponse 3 sélectionnée\n";
    }
    if (!isButton4Image) {
        out << "Réponse 4 sélectionnée\n";
    }

    file.close();
    qDebug() << "Réponses enregistrées dans le fichier :" << file.fileName();
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

void InterfaceQCM::loadQuestions(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erreur : impossible d'ouvrir le fichier des questions.";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            questions.append(line);
        }
    }

    file.close();
    qDebug() << "Nombre de questions chargées :" << questions.size();
}

void InterfaceQCM::showCurrentQuestion()
{
    if (questions.isEmpty()) {
        ui->labelQuestion->setText("Aucune question disponible.");
        return;
    }

    if (currentQuestionIndex >= 0 && currentQuestionIndex < questions.size()) {
        ui->labelQuestion->setText(questions[currentQuestionIndex]);
    }
}

