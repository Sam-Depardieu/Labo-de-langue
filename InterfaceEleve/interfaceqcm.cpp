#include "interfaceqcm.h"
#include "mainwindow.h"
#include "avancementqcm.h"
#include <QStandardItemModel>


#include "ui_interfaceqcm.h"

InterfaceQCM::InterfaceQCM(MainWindow *parentWindow ,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceQCM)
    , mainWindow(parentWindow)
    , isButtonAppelProfImage(true)
{
    ui->setupUi(this);
    setFixedSize(800, 480);
    setWindowTitle("Page de QCM");

    sessionPATH = mainWindow->getSessionPATH();


    setButtonIcons();

    if (!Professor) {
        ui->textEditFeedBack->setReadOnly(true);
        ui->textEditFeedBack->setPlaceholderText("Accès réservé aux professeurs");
        ui->textEditConsigne->setReadOnly(true);
    }

    if (!QFile::exists(sessionPATH)) {
        qWarning() << "❌ Fichier non trouvé :" << sessionPATH;
    }

    loadQuestionsJson(sessionPATH);

    loadConsigneJson(sessionPATH);


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

    auto *model = new QStandardItemModel(this);

    for (int i = 0; i < questionArray.size(); ++i) {
        QStandardItem *item = new QStandardItem();
        item->setData(QColor(Qt::gray), Qt::UserRole + 1);  // statut initial
        model->appendRow(item);
    }

    ui->listViewAvancement->setModel(model);
    ui->listViewAvancement->setItemDelegate(new AvancementQCM(this));
    ui->listViewAvancement->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

void InterfaceQCM::loadQuestionsJson(QString &filePath)
{
    //QFile file("//CIEL-T171-05/Activites/erytz_2025-05-20_17-37");
    QString chemin = R"(%1/questions.qcmlabo)";
    QFile file(chemin.arg(filePath));
    qDebug() << "📂 Ouverture du fichier JSON :" << file.fileName();

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

    ui->pushButtonQuestionPrecedente->setEnabled(false);
}

void InterfaceQCM::showCurrentQuestion()
{
    if (currentQuestionIndex < 0 || currentQuestionIndex >= questionArray.size()) {
        qWarning() << "❌ Index de question invalide.";
        return;
    }

    QJsonObject currentQuestion = questionArray[currentQuestionIndex].toObject();

    // Récupérer le texte avec la clé "text"
    QString questionText = currentQuestion.value("text").toString();

    // Si vide, garder le texte déjà affiché (ex: au lancement)
    if (questionText.isEmpty()) {
        questionText = ui->labelQuestion->text();
    }

    // Ajouter le préfixe "Question n°X: "
    QString displayText = QString("Question n°%1: %2").arg(currentQuestionIndex + 1).arg(questionText);
    ui->labelQuestion->setText(displayText);

    // -- suite du code pour les réponses et boutons --
    QJsonArray answers = currentQuestion.value("answers").toArray();

    ui->pushButton1->setVisible(answers.size() > 0);
    ui->pushButton2->setVisible(answers.size() > 1);
    ui->pushButton3->setVisible(answers.size() > 2);
    ui->pushButton4->setVisible(answers.size() > 3);

    if (answers.size() > 0) ui->pushButton1->setText(answers[0].toObject().value("text").toString());
    if (answers.size() > 1) ui->pushButton2->setText(answers[1].toObject().value("text").toString());
    if (answers.size() > 2) ui->pushButton3->setText(answers[2].toObject().value("text").toString());
    if (answers.size() > 3) ui->pushButton4->setText(answers[3].toObject().value("text").toString());

    QVector<bool> reponses = userAnswers.value(currentQuestionIndex, QVector<bool>());

    isButton1Image = (reponses.size() > 0) ? reponses[0] : false;
    isButton2Image = (reponses.size() > 1) ? reponses[1] : false;
    isButton3Image = (reponses.size() > 2) ? reponses[2] : false;
    isButton4Image = (reponses.size() > 3) ? reponses[3] : false;

    ui->pushButton1->setStyleSheet(isButton1Image ? "background-color:blue; border:3px solid white; border-radius:20px;" : "background-color:blue; border-radius:20px;");
    ui->pushButton2->setStyleSheet(isButton2Image ? "background-color:green; border:3px solid white; border-radius:20px;" : "background-color:green; border-radius:20px;");
    ui->pushButton3->setStyleSheet(isButton3Image ? "background-color:red; border:3px solid white; border-radius:20px;" : "background-color:red; border-radius:20px;");
    ui->pushButton4->setStyleSheet(isButton4Image ? "background-color:orange; border:3px solid white; border-radius:20px;" : "background-color:orange; border-radius:20px;");

    if (currentQuestionIndex == questionArray.size() - 1) {
        ui->pushButtonSoumettre->show();
        ui->pushButtonQuestionSuivante->hide();
        ui->pushButtonSoumettre->setEnabled(true);
    } else {
        ui->pushButtonSoumettre->hide();
        ui->pushButtonQuestionSuivante->show();
    }
}


void InterfaceQCM::loadConsigneJson(QString &filePath)
{
    QString cheminConsigne = QString("%1/config.labo").arg(filePath);
    QFile file(cheminConsigne);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier consigne JSON.");
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull() || !doc.isObject()) {
        QMessageBox::warning(this, "Erreur", "Le fichier consigne JSON n'est pas valide.");
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
    setIcon(ui->pushButtonAppelProf, ":/images/CallProf");
}

void InterfaceQCM::onAnswerClicked(QPushButton *bouton, bool /*status*/)
{
    QString color;
    bool *isButtonImage = nullptr;

    if (bouton == ui->pushButton1) {
        color = "blue";
        isButtonImage = &isButton1Image;
    }
    else if (bouton == ui->pushButton2) {
        color = "green";
        isButtonImage = &isButton2Image;
    }
    else if (bouton == ui->pushButton3) {
        color = "red";
        isButtonImage = &isButton3Image;
    }
    else if (bouton == ui->pushButton4) {
        color = "orange";
        isButtonImage = &isButton4Image;
    }

    if (isButtonImage) {
        // Inverser la sélection
        *isButtonImage = !(*isButtonImage);

        // Appliquer style selon la nouvelle valeur
        if (*isButtonImage) {
            bouton->setStyleSheet(QString("background-color:%1; border:3px solid white; border-radius:20px;").arg(color));
        } else {
            bouton->setStyleSheet(QString("background-color:%1; border-radius:20px;").arg(color));
        }
    }

    // Mettre à jour les réponses utilisateur avec les nouvelles valeurs
    userAnswers[currentQuestionIndex] = {
        isButton1Image,
        isButton2Image,
        isButton3Image,
        isButton4Image
    };

    //updateAvancement(currentQuestionIndex);
}
void InterfaceQCM::updateAvancement(int questionIndex)
{
    auto model = qobject_cast<QStandardItemModel*>(ui->listViewAvancement->model());
    if (!model) return;

    QStandardItem *item = model->item(questionIndex);
    if (!item) return;

    // Si l'utilisateur a répondu à cette question (au moins une réponse sélectionnée)
    bool repondu = false;
    QVector<bool> reponses = userAnswers.value(questionIndex);
    for (bool rep : reponses) {
        if (rep) {
            repondu = true;
            break;
        }
    }

    if (repondu) {
        item->setData(QColor(Qt::green), Qt::UserRole + 1);
    } else {
        item->setData(QColor(Qt::gray), Qt::UserRole + 1);
    }

    // Forcer la vue à rafraîchir cet item
    QModelIndex idx = model->index(questionIndex, 0);
    model->dataChanged(idx, idx);
}


void InterfaceQCM::on_pushButton1_clicked()
{
    onAnswerClicked(ui->pushButton1, isButton1Image);
}

void InterfaceQCM::on_pushButton2_clicked()
{
    onAnswerClicked(ui->pushButton2, isButton2Image);
}

void InterfaceQCM::on_pushButton3_clicked()
{
    onAnswerClicked(ui->pushButton3, isButton3Image);
}

void InterfaceQCM::on_pushButton4_clicked()
{
    onAnswerClicked(ui->pushButton4, isButton4Image);
}

void InterfaceQCM::on_pushButtonEffacerReponse_clicked()
{
    ui->pushButton1->setStyleSheet("background-color:blue; border-radius:20px;");
    ui->pushButton2->setStyleSheet("background-color:green; border-radius:20px;");
    ui->pushButton3->setStyleSheet("background-color:red; border-radius:20px;");
    ui->pushButton4->setStyleSheet("background-color:orange; border-radius:20px;");

    isButton1Image = false;
    isButton2Image = false;
    isButton3Image = false;
    isButton4Image = false;

    // Met à jour la structure userAnswers aussi (important)
    userAnswers[currentQuestionIndex] = {false, false, false, false};

    updateAvancement(currentQuestionIndex);

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
    // Mettre à jour l'avancement de la question courante **uniquement ici**
    updateAvancement(currentQuestionIndex);

    ui->pushButtonQuestionPrecedente->setEnabled(true);
    if (currentQuestionIndex < questionArray.size() - 1) {
        currentQuestionIndex++;
        showCurrentQuestion();
    }

    if (currentQuestionIndex == questionArray.size() - 1)
        ui->pushButtonQuestionSuivante->setEnabled(false);
}


void InterfaceQCM::on_pushButtonQuestionPrecedente_clicked()
{
    if (currentQuestionIndex > 0) {
        currentQuestionIndex--;
        showCurrentQuestion();
    }
    if(currentQuestionIndex != questionArray.size() -1)
        ui->pushButtonQuestionSuivante->setEnabled(true);

    if(currentQuestionIndex == 0)
        ui->pushButtonQuestionPrecedente->setEnabled(false);
}

void InterfaceQCM::on_pushButtonSoumettre_clicked()
{
    // Demander confirmation à l'utilisateur
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Voulez-vous enregistrer vos réponses ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        // L'utilisateur ne veut pas enregistrer, on retourne simplement
        return;
    }

    // Sinon, continuer l'enregistrement
    const QString docs = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    const QString folder = QDir(docs).filePath("Travail");
    if (!QDir(folder).exists()) QDir().mkpath(folder);

    const QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    const QString filePath = QDir(folder).filePath(timestamp + ".txt");

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "❌ Impossible d’écrire dans le fichier.");
        return;
    }

    QTextStream out(&file);

    for (int i = 0; i < questionArray.size(); ++i) {
        QJsonObject question = questionArray[i].toObject();
        QJsonArray answers = question["answers"].toArray();
        out << QString("Question %1: %2\n").arg(i + 1).arg(question["text"].toString());

        QVector<bool> etats = userAnswers.value(i, QVector<bool>());

        for (int j = 0; j < answers.size(); ++j) {
            if (j < etats.size() && etats[j]) {
                QJsonObject answer = answers[j].toObject();
                QString text = answer["text"].toString();
                bool isCorrect = answer["isCorrect"].toBool();
                out << QString("- %1 %2\n").arg(text, isCorrect ? "✅" : "❌");
            }
        }

        out << "\n";
    }

    file.close();

    // Confirmer à l'utilisateur que le fichier a bien été enregistré
    QMessageBox::information(this, "Réponses enregistrées",
                             "✅ Vos réponses ont été enregistrées avec succès dans:\n\n" + filePath);

    // Fermer la fenêtre
    accept();
}


void InterfaceQCM::on_pushButtonAppelProf_clicked()
{
    ui->pushButtonAppelProf->setStyleSheet(" border:1px solid white; border-radius:20px;");
    isButtonAppelProfImage = false;
    mainWindow->sendCommandToProf(mainWindow->getIpProf(), 5557, "help");
}

