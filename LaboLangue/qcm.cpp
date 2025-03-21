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
    questionsLayout = new QVBoxLayout(scrollWidget);
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
    // Créer un widget pour la nouvelle question
    QuestionWidget *question = new QuestionWidget;

    QVBoxLayout *questionLayout = new QVBoxLayout();

    // **Séparateur**
    QFrame *separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet("background-color: gray; height: 2px;");

    // **Nouvelle ligne pour Numéro + Question**
    QHBoxLayout *questionHeaderLayout = new QHBoxLayout();
    QHBoxLayout *nbChoixLayout = new QHBoxLayout();

    // Numéro de la question (petit sur la gauche)
    question->questionNumberSpin = new QSpinBox(this);
    question->questionNumberSpin->setMinimum(1);
    question->questionNumberSpin->setMaximum(100);
    question->questionNumberSpin->setFixedWidth(50);  // Réduit la largeur du spinbox

    // Label du numéro de question
    QLabel *questionNumberLabel = new QLabel("N° :", this);

    // Champ de la question
    QLabel *questionLabel = new QLabel("Question :", this);
    question->questionEdit = new QLineEdit(this);

    // **Ajout des éléments dans le layout horizontal**
    questionHeaderLayout->addWidget(questionNumberLabel);
    questionHeaderLayout->addWidget(question->questionNumberSpin);
    questionHeaderLayout->addWidget(questionLabel);
    questionHeaderLayout->addWidget(question->questionEdit);
    questionHeaderLayout->addStretch();  // Ajoute un espace flexible à droite

    questionLayout->addLayout(questionHeaderLayout);

    // Nombre de choix possibles
    QLabel *choiceCountLabel = new QLabel("Nombre de choix possibles :", this);
    question->choiceCountSpin = new QSpinBox(this);
    question->choiceCountSpin->setRange(1, 4);

    nbChoixLayout->addWidget(choiceCountLabel);
    nbChoixLayout->addWidget(question->choiceCountSpin);

    questionLayout->addLayout(nbChoixLayout);

    // Layout pour les réponses
    question->answersLayout = new QVBoxLayout();
    questionLayout->addLayout(question->answersLayout);

    // Boutons pour ajouter/supprimer une réponse
    question->addAnswerButton = new QPushButton("+", this);
    question->addAnswerButton->setStyleSheet("background-color: green;");
    question->removeAnswerButton = new QPushButton("-", this);
    question->removeAnswerButton->setStyleSheet("background-color: red;");
    question->buttonLayout = new QHBoxLayout();
    question->buttonLayout->addWidget(question->addAnswerButton);
    question->buttonLayout->addWidget(question->removeAnswerButton);
    questionLayout->addLayout(question->buttonLayout);

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

    connect(question->removeAnswerButton, &QPushButton::clicked, [=]() {
        if (question->answerFields.size() <= 2) {
            QMessageBox::warning(this, "Minimum atteint", "Vous devez avoir au moins 2 réponses !");
            return;
        }

        delete question->answerFields.takeLast();
        delete question->correctAnswers.takeLast();
    });

    // Ajouter 2 réponses par défaut
    for (int i = 0; i < 2; i++) {
        question->addAnswerButton->click();
    }

    // **Ajout du layout de la question et du séparateur**
    questionsLayout->addWidget(separator);  // Ajoute le séparateur entre les questions
    questionsLayout->addLayout(questionLayout);
    questionWidgets.append(question);

    // Mise à jour du scroll
    scrollWidget->adjustSize();
}

void QCM::removeQuestion()
{
    if (questionWidgets.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucune question à supprimer !");
        return;
    }

    QuestionWidget *question = questionWidgets.takeLast();

    // Nettoyage mémoire
    delete question->questionNumberSpin;
    delete question->questionEdit;
    delete question->choiceCountSpin;
    delete question->addAnswerButton;
    delete question->removeAnswerButton;
    delete question->buttonLayout;

    for (auto answer : question->answerFields) {
        delete answer;
    }
    for (auto correct : question->correctAnswers) {
        delete correct;
    }

    delete question->answersLayout;
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
