#include "qcm.h"
#include "qscrollbar.h"
#include "ui_qcm.h"
#include "mainwindow.h"

QCM::QCM(QWidget *parent, MainWindow* parentWindow)
    : QDialog(parent), ui(new Ui::QCM), mainWindow(parentWindow)
{
    ui->setupUi(this);
    setWindowTitle("Création de QCM");
    setAttribute(Qt::WA_DeleteOnClose);

    // Layout principal
    mainLayout = new QVBoxLayout(this);

    // Création du QScrollArea
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollWidget = new QWidget();

    // Utilisation du QGridLayout pour les questions
    questionsLayout = new QGridLayout(scrollWidget);
    scrollWidget->setLayout(questionsLayout);
    scrollArea->setWidget(scrollWidget);

    mainLayout->addWidget(scrollArea);

    // Layouts pour le footer
    QVBoxLayout *footer = new QVBoxLayout();
    QHBoxLayout *footerButton = new QHBoxLayout();
    QHBoxLayout *footerInformation = new QHBoxLayout();
    QVBoxLayout *footerInformationNom = new QVBoxLayout();

    // Boutons pour gérer les questions
    addQuestionButton = new QPushButton("Ajouter une question", this);
    addQuestionButton->setStyleSheet("background-color: #28a745");
    removeQuestionButton = new QPushButton("Supprimer la dernière question", this);
    removeQuestionButton->setStyleSheet("background-color: #dc3545");
    importQuestionButton = new QPushButton("Importer un QCM", this);
    saveButton = new QPushButton("Enregistrer", this);

    footerButton->addWidget(addQuestionButton);
    footerButton->addWidget(removeQuestionButton);
    footerButton->addWidget(importQuestionButton);

    nomQCMLabel = new QLabel("Nom du QCM :");
    nomQCM = new QLineEdit(this);
    footerInformationNom->addWidget(nomQCMLabel);
    footerInformationNom->addWidget(nomQCM);
    footerInformation->addLayout(footerInformationNom);

    footer->addLayout(footerButton);
    footer->addLayout(footerInformation);

    // Connexions des signaux
    connect(addQuestionButton, &QPushButton::clicked, this, [this]() {

        this->addQuestion(nullptr, nullptr, nullptr);
    });
    connect(removeQuestionButton, &QPushButton::clicked, this, &QCM::removeQuestion);
    connect(saveButton, &QPushButton::clicked, this, &QCM::saveQuestions);
    connect(importQuestionButton, &QPushButton::clicked, this, &QCM::importQCM);

    // Ajout du boutton save en dessous de tout
    footer->addWidget(saveButton);

    // Ajout du footer au layout principal
    mainLayout->addLayout(footer);

    // Ajouter une première question par défaut
    addQuestion(nullptr);

    // Définir le layout principal
    setLayout(mainLayout);
}

void QCM::importQCM()
{
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Sélectionner un fichier QCM",
        documentsPath,
        "Labo QCM (*.qcmlabo)"
        );

    if (!fileName.isNull()) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Confirmation",
            "Souhaitez-vous écraser les QCM existants ?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (reply == QMessageBox::Yes) {
            // Supprime les questions existantes
            for (QuestionWidget *question : questionWidgets) {
                delete question;
            }
            questionWidgets.clear();
            scrollWidget->adjustSize();
        }

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier sélectionné !");
            return;
        }

        QByteArray fileContent = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileContent);
        if (jsonDoc.isNull() || !jsonDoc.isObject()) {
            QMessageBox::critical(this, "Erreur", "Le fichier n'est pas un format JSON valide !");
            return;
        }

        QJsonObject rootObj = jsonDoc.object();
        if (!rootObj.contains("questions") || !rootObj.value("questions").isArray()) {
            QMessageBox::critical(this, "Erreur", "Le fichier JSON doit contenir un tableau de questions !");
            return;
        }

        QJsonArray questionsArray = rootObj.value("questions").toArray();

        for (const QJsonValue &questionValue : questionsArray) {
            QJsonObject questionObj = questionValue.toObject();
            QString questionText = questionObj.value("text").toString();
            QString numberQuestion = questionObj.value("number").toString();
            QString numberChoice = questionObj.value("choicesAllowed").toString();
            QJsonArray answersArray = questionObj.value("answers").toArray();

            // Déclaration locale de choices pour éviter la persistance des données précédentes
            array<array<QString, 2>, 4> choices = {{{QString(""), QString("")}}};

            for (int i = 0; i < answersArray.size() && i < 4; ++i) {
                QJsonObject answerObj = answersArray[i].toObject();
                choices[i][0] = answerObj.value("text").toString();
                choices[i][1] = answerObj.value("isCorrect").toBool() ? "true" : "false";
            }

            addQuestion(&questionText, &numberQuestion, &numberChoice, choices);
        }

        QMessageBox::information(this, "Importation terminée", "Les questions ont été importées avec succès !");
    }
}


void QCM::addQuestion(QString *nomQ, QString *numQ, QString *nbRep, array<array<QString, 2>, 4> choices)
{
    QuestionWidget *question = new QuestionWidget;
    QString nbQ = QString::number(questionWidgets.size() + 1);
    QGroupBox *questionBox = new QGroupBox("Question " + nbQ, this);
    QVBoxLayout *questionBoxLayout = new QVBoxLayout();
    questionBox->setLayout(questionBoxLayout);
    questionBox->setStyleSheet("border: 1px solid gray; border-radius: 5px; padding: 10px;");

    // ---- Ajout de l'icône croix en haut à droite ----
    QPixmap crossIcon("../img/cross-qcm.png");
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(crossIcon.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QHBoxLayout *iconLayout = new QHBoxLayout();
    iconLayout->addStretch();  // Pousse l'icône vers la droite
    iconLayout->addWidget(imageLabel);
    questionBoxLayout->addLayout(iconLayout);

    // ---- Layout pour le numéro et la question ----
    QHBoxLayout *questionHeaderLayout = new QHBoxLayout();
    QLabel *questionNumberLabel = new QLabel("N° :", this);
    question->questionNumberSpin = new QSpinBox(this);
    question->questionNumberSpin->setMinimum(1);
    question->questionNumberSpin->setMaximum(100);
    question->questionNumberSpin->setFixedWidth(75);
    question->questionNumberSpin->setValue((numQ && !numQ->isEmpty()) ? numQ->toInt() : nbQ.toInt());

    QLabel *questionLabel = new QLabel("Question :", this);
    question->questionEdit = new QLineEdit(this);
    question->questionEdit->setText(nomQ ? *nomQ : "");
    question->questionEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    questionHeaderLayout->addWidget(questionNumberLabel);
    questionHeaderLayout->addWidget(question->questionNumberSpin);
    questionHeaderLayout->addWidget(questionLabel);
    questionHeaderLayout->addWidget(question->questionEdit);

    questionBoxLayout->addLayout(questionHeaderLayout);

    // ---- Nombre de choix possibles ----
    QHBoxLayout *nbChoixLayout = new QHBoxLayout();
    QLabel *choiceCountLabel = new QLabel("Nombre de choix possibles :", this);
    question->choiceCountSpin = new QSpinBox(this);
    question->choiceCountSpin->setRange(1, 4);
    question->choiceCountSpin->setValue((nbRep && !nbRep->isEmpty()) ? nbRep->toInt() : 2);

    nbChoixLayout->addWidget(choiceCountLabel);
    nbChoixLayout->addWidget(question->choiceCountSpin);
    questionBoxLayout->addLayout(nbChoixLayout);

    // ---- Réponses ----
    question->answersLayout = new QVBoxLayout();
    questionBoxLayout->addLayout(question->answersLayout);

    // ---- Boutons d'ajout et suppression de réponses ----
    question->addAnswerButton = new QPushButton("+", this);
    question->addAnswerButton->setStyleSheet("background-color: #28a745; color: white; border-radius: 5px;");
    question->removeAnswerButton = new QPushButton("-", this);
    question->removeAnswerButton->setStyleSheet("background-color: #dc3545; color: white; border-radius: 5px;");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(question->addAnswerButton);
    buttonLayout->addWidget(question->removeAnswerButton);
    questionBoxLayout->addLayout(buttonLayout);

    // ---- Ajout des réponses ----
    for (int i = 0; i < 4; ++i) {
        if (!choices[i][0].isEmpty() || i < 2) {
            addAnswers(question, &choices[i][0], &choices[i][1]);
        }
    }

    // ---- Connexions des boutons ----
    connect(question->addAnswerButton, &QPushButton::clicked, this, [=]() {
        addAnswers(question, new QString(""), new QString(""));
    });

    connect(question->removeAnswerButton, &QPushButton::clicked, this, [=]() {
        if (question->answerFields.size() <= 2) {
            QMessageBox::warning(this, "Limite atteinte", "Vous ne pouvez pas avoir moins de 2 réponses !");
            return;
        }

        delete question->answerFields.takeLast();
        delete question->correctAnswers.takeLast();

        scrollWidget->adjustSize();
        scrollWidget->update();
    });

    // ---- Placement dans la grille ----
    int row = questionWidgets.size() / 2;
    int column = questionWidgets.size() % 2;

    questionsLayout->addWidget(questionBox, row, column);
    questionWidgets.append(question);
    scrollWidget->adjustSize();

    addBoxAddQuestion();
    scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum());
}

void QCM::addAnswers(QuestionWidget* question, QString *choix, QString *correct) {
    if (!question || question->answerFields.size() >= 4) {
        QMessageBox::warning(this, "Limite atteinte", "Vous ne pouvez pas ajouter plus de 4 réponses !");
        return;
    }

    QLineEdit *answerEdit = new QLineEdit(this);
    answerEdit->setText(choix ? *choix : QString(""));
    answerEdit->setPlaceholderText("Réponse " + QString::number(question->answerFields.size() + 1));

    bool statusCorrect = (correct->toLower() == "true" ? true : false);

    QCheckBox *correctAnswerCheck = new QCheckBox("Bonne réponse", this);
    correctAnswerCheck->setChecked(statusCorrect);

    QHBoxLayout *answerLayout = new QHBoxLayout();
    answerLayout->addWidget(answerEdit);
    answerLayout->addWidget(correctAnswerCheck);
    question->answersLayout->addLayout(answerLayout);

    question->answerFields.append(answerEdit);
    question->correctAnswers.append(correctAnswerCheck);
}


void QCM::addBoxAddQuestion()
{
    // Si la boîte existe déjà, la supprimer avant de la recréer
    if (addQuestionBox != nullptr) {
        questionsLayout->removeWidget(addQuestionBox);
        delete addQuestionBox;
    }

    // Créer la boîte d'ajout de question
    addQuestionBox = new QGroupBox(this);
    addQuestionBox->setStyleSheet("border: 2px dashed rgb(0, 151, 178); border-radius: 5px; padding: 20px;");

    QVBoxLayout *boxLayout = new QVBoxLayout(addQuestionBox);
    QLabel *descriptionLabel = new QLabel("Cliquez pour ajouter une nouvelle question", this);
    QPushButton *addButton = new QPushButton("+", this);
    addButton->setStyleSheet("font-size: 24px; font-weight: bold; padding: 10px; background-color: transparent; border: none;");

    boxLayout->addWidget(addButton, 0, Qt::AlignCenter);
    boxLayout->addWidget(descriptionLabel, 0, Qt::AlignCenter);

    connect(addButton, &QPushButton::clicked, this, [this]() {
        this->addQuestion(nullptr, nullptr, nullptr);
    });

    // Calculer la ligne et la colonne où la boîte doit être placée
    int row = questionWidgets.size() / 2;  // Chaque ligne contient 2 questions
    int column = questionWidgets.size() % 2;  // Alternance entre 0 et 1 (deux colonnes par ligne)

    // Ajouter la boîte d'ajout de question dans le layout, après la dernière question
    questionsLayout->addWidget(addQuestionBox, row, column);

    // Ajuster la taille du widget après ajout
    scrollWidget->adjustSize();
}


void QCM::removeQuestion()
{
    if (questionWidgets.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucune question à supprimer !");
        return;
    }

    // Récupérer la dernière question et son QGroupBox
    QuestionWidget *question = questionWidgets.takeLast();
    QGroupBox *questionBox = nullptr;

    // Trouver le QGroupBox correspondant à la dernière question
    for (int i = 0; i < questionsLayout->count(); ++i) {
        QLayoutItem *item = questionsLayout->itemAt(i);
        QWidget *widget = item->widget();

        if (QGroupBox *box = qobject_cast<QGroupBox*>(widget)) {
            if (box->title().contains("Question")) {  // Identifier un QGroupBox question
                questionBox = box;
            }
        }
    }

    if (questionBox) {
        questionsLayout->removeWidget(questionBox);
        delete questionBox;  // Supprimer l'affichage de la question
    }

    // Supprimer l'objet question
    delete question;

    // Repositionner la boîte d'ajout de question
    addBoxAddQuestion();

    // Mise à jour de l'affichage
    scrollWidget->adjustSize();
    scrollWidget->update();
}




void QCM::saveQuestions()
{
    QJsonArray questionsArray;

    // Tri des questions par leur numéro, si nécessaire
    std::sort(questionWidgets.begin(), questionWidgets.end(), [](const QuestionWidget *a, const QuestionWidget *b) {
        return a->questionNumberSpin->value() < b->questionNumberSpin->value();
    });

    for (const auto &question : questionWidgets) {
        if (question->questionEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer une question !");
            return;
        }

        QJsonObject questionData;
        questionData["number"] = question->questionNumberSpin->value(); // Numéro de la question
        questionData["text"] = question->questionEdit->text();          // Texte de la question
        questionData["choicesAllowed"] = question->choiceCountSpin->value(); // Nombre de choix possibles

        QJsonArray answersArray; // Contient les réponses (avec "text" et "isCorrect")

        for (int i = 0; i < question->answerFields.size(); i++) {
            if (!question->answerFields[i]->text().isEmpty()) {
                QJsonObject answerData;
                answerData["isCorrect"] = question->correctAnswers[i]->isChecked(); // Bonne réponse ou non
                answerData["text"] = question->answerFields[i]->text();             // Texte de la réponse
                answersArray.append(answerData); // Ajoute la réponse au tableau
            }
        }

        questionData["answers"] = answersArray; // Ajoute les réponses à la question
        questionsArray.append(questionData);   // Ajoute la question au tableau des questions
    }

    // Crée un objet principal pour inclure les questions
    QJsonObject rootObject;
    rootObject["questions"] = questionsArray;

    // Chemin du fichier de sauvegarde
    QString savePath = mainWindow->getSessionFolder() + "/questions.qcmlabo";
    QFile file(savePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible de sauvegarder les questions !");
        return;
    }

    // Sauvegarde du JSON formaté avec indentation
    file.write(QJsonDocument(rootObject).toJson(QJsonDocument::Indented));
    file.close();

    QMessageBox::information(this, "Sauvegarde terminée", "Les questions ont été sauvegardées avec succès dans :\n" + savePath);
}


QCM::~QCM()
{
    delete ui;

}
