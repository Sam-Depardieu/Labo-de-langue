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


    loadQuestionsJson(R"(\\CIEL-T171-05\Activites\uykfjkfhjl_2025-05-06_10-47\questions.qcmlabo)");


    currentQuestionIndex = 0;
    showCurrentQuestion();


}

InterfaceQCM::~InterfaceQCM()
{
    delete ui;
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
    ui->labelQuestion->setText(questionText);  // Affiche la question dans le label

    QJsonArray answers = currentQuestion["answers"].toArray(); // Récupère les réponses

    // Réinitialiser les boutons (cacher les boutons non utilisés)
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

    // Réinitialiser le style des boutons
    on_pushButtonEffacerReponse_clicked();
}




void InterfaceQCM::on_pushButtonQuestionSuivante_clicked()
{
    // Vérifier si l'index est valide
    if (currentQuestionIndex >= questionArray.size()) {
        qDebug() << "❌ Aucune question suivante à afficher.";
        return;
    }

    // Récupérer la question actuelle
    QJsonObject currentQuestion = questionArray[currentQuestionIndex].toObject();
    QJsonArray answers = currentQuestion["answers"].toArray();  // Récupère les réponses de la question actuelle

    // Enregistrement des réponses actuelles dans le fichier
    QString fileName = "C:/Users/Quentin/Documents/Projet/responses.txt";
    QFile file(fileName);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {  // Mode Append pour ne pas écraser le fichier
        qWarning() << "Erreur : impossible d'ouvrir le fichier pour écrire.";
        return;
    }

    QTextStream out(&file);
    out << QString("Question %1:\n").arg(currentQuestionIndex + 1);  // Question actuelle

    // Vérifier chaque réponse sélectionnée et enregistrer avec l'emoji et le texte
    if (!isButton1Image) {
        QString emoji = answers[0].toObject()["isCorrect"].toBool() ? "✅" : "❌";
        QString buttonText = ui->pushButton1->text();  // Récupère le texte du bouton 1
        out << QString("- %1 %2\n").arg(buttonText).arg(emoji);
    }
    if (!isButton2Image) {
        QString emoji = answers[1].toObject()["isCorrect"].toBool() ? "✅" : "❌";
        QString buttonText = ui->pushButton2->text();  // Récupère le texte du bouton 2
        out << QString("- %1 %2\n").arg(buttonText).arg(emoji);
    }
    if (!isButton3Image) {
        QString emoji = answers[2].toObject()["isCorrect"].toBool() ? "✅" : "❌";
        QString buttonText = ui->pushButton3->text();  // Récupère le texte du bouton 3
        out << QString("- %1 %2\n").arg(buttonText).arg(emoji);
    }
    if (!isButton4Image) {
        QString emoji = answers[3].toObject()["isCorrect"].toBool() ? "✅" : "❌";
        QString buttonText = ui->pushButton4->text();  // Récupère le texte du bouton 4
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
        // Optionnel : désactiver les boutons ou afficher un message
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
/* il y en a deux
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
*/
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

/*void InterfaceQCM::loadQuestions(const QString &filePath)
{

}
*/
void InterfaceQCM::on_pushButtonQuestionPrecedente_clicked()

{
    // Vérifier si l'index est valide (on ne peut pas aller avant la première question)
    if (currentQuestionIndex <= 0) {
        qDebug() << "❌ Pas de question précédente.";
        return;
    }

    // Décrémenter l'index pour revenir à la question précédente
    currentQuestionIndex--;

    // Mettre à jour l'affichage avec la question précédente
    showCurrentQuestion();
}



