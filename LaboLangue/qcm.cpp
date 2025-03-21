#include "qcm.h"
#include "qscrollbar.h"
#include "ui_qcm.h"

QCM::QCM(QWidget *parent)
    : QDialog(parent), ui(new Ui::QCM)
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

    // Boutons pour gérer les questions
    addQuestionButton = new QPushButton("Ajouter une question", this);
    removeQuestionButton = new QPushButton("Supprimer la dernière question", this);
    saveButton = new QPushButton("Enregistrer", this);

    connect(addQuestionButton, &QPushButton::clicked, this, &QCM::addQuestion);
    connect(removeQuestionButton, &QPushButton::clicked, this, &QCM::removeQuestion);
    connect(saveButton, &QPushButton::clicked, this, &QCM::saveQuestions);

    mainLayout->addWidget(addQuestionButton);
    mainLayout->addWidget(removeQuestionButton);
    mainLayout->addWidget(saveButton);

    // Ajouter une première question par défaut
    addQuestion();


    setLayout(mainLayout);
}

void QCM::addQuestion()
{
    QuestionWidget *question = new QuestionWidget;
    QString nbQ = QString::number(questionWidgets.size() + 1);
    QGroupBox *questionBox = new QGroupBox("Question " + nbQ, this);
    QVBoxLayout *questionBoxLayout = new QVBoxLayout();
    questionBox->setLayout(questionBoxLayout);
    questionBox->setStyleSheet("border: 1px solid gray; border-radius: 5px; padding: 10px;");

    QHBoxLayout *questionHeaderLayout = new QHBoxLayout();
    QHBoxLayout *nbChoixLayout = new QHBoxLayout();

    question->questionNumberSpin = new QSpinBox(this);
    question->questionNumberSpin->setMinimum(1);
    question->questionNumberSpin->setMaximum(100);
    question->questionNumberSpin->setFixedWidth(75);
    question->questionNumberSpin->setValue(nbQ.toInt());

    QLabel *questionNumberLabel = new QLabel("N° :", this);
    QLabel *questionLabel = new QLabel("Question :", this);
    question->questionEdit = new QLineEdit(this);
    question->questionEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    questionHeaderLayout->addWidget(questionNumberLabel);
    questionHeaderLayout->addWidget(question->questionNumberSpin);
    questionHeaderLayout->addWidget(questionLabel);
    questionHeaderLayout->addWidget(question->questionEdit);

    questionBoxLayout->addLayout(questionHeaderLayout);

    QLabel *choiceCountLabel = new QLabel("Nombre de choix possibles :", this);
    question->choiceCountSpin = new QSpinBox(this);
    question->choiceCountSpin->setRange(1, 4);

    nbChoixLayout->addWidget(choiceCountLabel);
    nbChoixLayout->addWidget(question->choiceCountSpin);
    questionBoxLayout->addLayout(nbChoixLayout);

    question->answersLayout = new QVBoxLayout();
    questionBoxLayout->addLayout(question->answersLayout);

    question->addAnswerButton = new QPushButton("+", this);
    question->addAnswerButton->setStyleSheet("background-color: #28a745; color: white; border-radius: 5px;");
    question->removeAnswerButton = new QPushButton("-", this);
    question->removeAnswerButton->setStyleSheet("background-color: #dc3545; color: white; border-radius: 5px;");

    question->buttonLayout = new QHBoxLayout();
    question->buttonLayout->addWidget(question->addAnswerButton);
    question->buttonLayout->addWidget(question->removeAnswerButton);
    questionBoxLayout->addLayout(question->buttonLayout);

    addAnswers(question);
    addAnswers(question);

    // Correction de la connexion du bouton d'ajout de réponse
    connect(question->addAnswerButton, &QPushButton::clicked, this, [=]() { addAnswers(question); });

    connect(question->removeAnswerButton, &QPushButton::clicked, [=]() {
        if (question->answerFields.size() <= 2) {
            QMessageBox::warning(this, "Limite atteinte", "Vous ne pouvez pas avoir moins de 2 réponses !");
            return;
        }

        delete question->answerFields.takeLast();
        delete question->correctAnswers.takeLast();

        scrollWidget->adjustSize();
        scrollWidget->update();
    });

    // Calculer la ligne et la colonne pour ajouter dans le QGridLayout
    int row = questionWidgets.size() / 2;  // Ligne (deux questions par ligne)
    int column = questionWidgets.size() % 2;  // Colonne (alternance entre 0 et 1)

    questionsLayout->addWidget(questionBox, row, column);

    questionWidgets.append(question);
    scrollWidget->adjustSize();

    // Descendre la scrollbar jusqu'à la dernière question ajoutée
    scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum());

    addBoxAddQuestion();
}

void QCM::addAnswers(QuestionWidget* question)
{
    if (question->answerFields.size() >= 4) {
        QMessageBox::warning(this, "Limite atteinte", "Vous ne pouvez pas ajouter plus de 4 réponses !");
        return;
    }

    QLineEdit *answerEdit = new QLineEdit(this);
    answerEdit->setPlaceholderText("Réponse " + QString::number(question->answerFields.size() + 1));
    QCheckBox *correctAnswerCheck = new QCheckBox("Bonne réponse", this);

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

    connect(addButton, &QPushButton::clicked, this, &QCM::addQuestion);

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

    for (const auto &question : questionWidgets) {
        if (question->questionEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer une question !");
            return;
        }

        QJsonObject questionData;
        questionData["number"] = question->questionNumberSpin->value();
        questionData["question"] = question->questionEdit->text();
        questionData["choicesAllowed"] = question->choiceCountSpin->value();

        QJsonArray answersArray;
        QJsonArray correctArray;

        for (int i = 0; i < question->answerFields.size(); i++) {
            if (!question->answerFields[i]->text().isEmpty()) {
                answersArray.append(question->answerFields[i]->text());
                if (question->correctAnswers[i]->isChecked()) {
                    correctArray.append(i);
                }
            }
        }

        questionData["answers"] = answersArray;
        questionData["correct"] = correctArray;
        questionsArray.append(questionData);
    }

    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/questions.json");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(QJsonDocument(questionsArray).toJson(QJsonDocument::Indented));
    file.close();
}

QCM::~QCM()
{
    delete ui;
}
