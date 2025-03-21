#include "qcm.h"
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
    int row = questionWidgets.size() / 2;
    int col = questionWidgets.size() % 2;

    QuestionWidget *question = new QuestionWidget;

    QGroupBox *questionBox = new QGroupBox("Question " + QString::number(questionWidgets.size() + 1), this);
    QVBoxLayout *questionBoxLayout = new QVBoxLayout();
    questionBox->setLayout(questionBoxLayout);
    questionBox->setStyleSheet("border: 1px solid gray; border-radius: 5px; padding: 10px;");

    QHBoxLayout *questionHeaderLayout = new QHBoxLayout();
    QHBoxLayout *nbChoixLayout = new QHBoxLayout();

    question->questionNumberSpin = new QSpinBox(this);
    question->questionNumberSpin->setMinimum(1);
    question->questionNumberSpin->setMaximum(100);
    question->questionNumberSpin->setFixedWidth(50);

    QLabel *questionNumberLabel = new QLabel("N° :", this);
    QLabel *questionLabel = new QLabel("Question :", this);
    question->questionEdit = new QLineEdit(this);
    question->questionEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    questionHeaderLayout->addWidget(questionNumberLabel);
    questionHeaderLayout->addWidget(question->questionNumberSpin);
    questionHeaderLayout->addWidget(questionLabel);
    questionHeaderLayout->addWidget(question->questionEdit);
    questionHeaderLayout->addStretch();

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

    connect(question->addAnswerButton, &QPushButton::clicked, [=]() {
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
    });

    questionsLayout->addWidget(questionBox);
    questionWidgets.append(question);

    scrollWidget->adjustSize();
}

void QCM::removeQuestion()
{
    if (questionWidgets.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucune question à supprimer !");
        return;
    }

    QuestionWidget *question = questionWidgets.takeLast();

    delete question;
    scrollWidget->adjustSize();
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
