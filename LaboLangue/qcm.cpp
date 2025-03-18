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

    // Numéro de la question
    QLabel *questionNumberLabel = new QLabel("Numéro de question :", this);
    questionNumberSpin = new QSpinBox(this);
    questionNumberSpin->setMinimum(1);
    mainLayout->addWidget(questionNumberLabel);
    mainLayout->addWidget(questionNumberSpin);

    // Champ de la question
    QLabel *questionLabel = new QLabel("Question :", this);
    questionEdit = new QLineEdit(this);
    mainLayout->addWidget(questionLabel);
    mainLayout->addWidget(questionEdit);

    // Nombre de choix possibles
    QLabel *choiceCountLabel = new QLabel("Nombre de choix possibles :", this);
    choiceCountSpin = new QSpinBox(this);
    choiceCountSpin->setRange(1, 4);
    mainLayout->addWidget(choiceCountLabel);
    mainLayout->addWidget(choiceCountSpin);

    // Layout pour les réponses
    answersLayout = new QVBoxLayout();
    mainLayout->addLayout(answersLayout);

    // Boutons Ajouter/Supprimer
    addButton = new QPushButton("+", this);
    removeButton = new QPushButton("-", this);
    saveButton = new QPushButton("Enregistrer", this);

    connect(addButton, &QPushButton::clicked, this, &QCM::addAnswer);
    connect(removeButton, &QPushButton::clicked, this, &QCM::removeAnswer);
    connect(saveButton, &QPushButton::clicked, this, &QCM::saveQuestion);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(saveButton);

    // Ajouter 2 réponses par défaut
    for (int i = 0; i < 2; i++) {
        addAnswer();
    }

    setLayout(mainLayout);
}

void QCM::addAnswer()
{
    if (answerFields.size() >= 4) {
        QMessageBox::warning(this, "Limite atteinte", "Vous ne pouvez pas ajouter plus de 4 réponses !");
        return;
    }

    // Créer le layout pour la réponse
    QHBoxLayout *answerLayout = new QHBoxLayout();
    QLineEdit *answerEdit = new QLineEdit(this);
    answerEdit->setPlaceholderText("Réponse " + QString::number(answerFields.size() + 1));
    QCheckBox *correctAnswerCheck = new QCheckBox("Bonne réponse", this);

    answerLayout->addWidget(answerEdit);
    answerLayout->addWidget(correctAnswerCheck);
    answersLayout->addLayout(answerLayout);

    // Ajouter aux listes pour gestion mémoire
    answerFields.append(answerEdit);
    correctAnswers.append(correctAnswerCheck);
    answerLayouts.append(answerLayout);
}

void QCM::removeAnswer()
{
    if (answerFields.size() <= 2) {
        QMessageBox::warning(this, "Minimum atteint", "Vous devez avoir au moins 2 réponses !");
        return;
    }

    // Supprimer proprement le dernier élément ajouté
    delete answerFields.takeLast();
    delete correctAnswers.takeLast();

    // Supprimer le layout associé
    QLayout *layout = answerLayouts.takeLast();
    delete layout;
}

void QCM::saveQuestion()
{
    if (questionEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une question !");
        return;
    }

    QJsonObject questionData;
    questionData["number"] = questionNumberSpin->value();
    questionData["question"] = questionEdit->text();
    questionData["choicesAllowed"] = choiceCountSpin->value();

    QJsonArray answersArray;
    QJsonArray correctArray;

    for (int i = 0; i < answerFields.size(); i++) {
        if (!answerFields[i]->text().isEmpty()) {
            answersArray.append(answerFields[i]->text());
            if (correctAnswers[i]->isChecked()) {
                correctArray.append(i);
            }
        }
    }

    if (answersArray.size() < 2 || correctArray.size() == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer au moins 2 réponses et sélectionner au moins une bonne réponse !");
        return;
    }

    questionData["answers"] = answersArray;
    questionData["correct"] = correctArray;

    QJsonDocument jsonDoc(questionData);
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/question.json");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(jsonDoc.toJson(QJsonDocument::Indented));
        file.close();
        QMessageBox::information(this, "Succès", "Question enregistrée avec succès !");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de sauvegarder la question !");
    }
}

QCM::~QCM()
{
    delete ui;
    // Nettoyage mémoire des réponses
    for (auto layout : answerLayouts) {
        delete layout;
    }
}
