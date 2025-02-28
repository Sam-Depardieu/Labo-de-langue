#include "qcm.h"

QCM::QCM(QWidget *parent) : QWidget(parent)
{
    // Layout principal
    mainLayout = new QVBoxLayout(this);

    // Champ pour la question
    questionEdit = new QLineEdit(this);
    questionEdit->setPlaceholderText("Entrez votre question ici...");
    mainLayout->addWidget(questionEdit);

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

    // Ajouter les boutons dans un layout
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

// Ajouter une réponse (max 4)
void QCM::addAnswer()
{
    if (answerFields.size() >= 4) {
        QMessageBox::warning(this, "Limite atteinte", "Vous ne pouvez pas ajouter plus de 4 réponses !");
        return;
    }

    QLineEdit *answerEdit = new QLineEdit(this);
    answerEdit->setPlaceholderText("Réponse " + QString::number(answerFields.size() + 1));
    answersLayout->addWidget(answerEdit);
    answerFields.append(answerEdit);
}

// Supprimer une réponse (min 2)
void QCM::removeAnswer()
{
    if (answerFields.size() <= 2) {
        QMessageBox::warning(this, "Minimum atteint", "Vous devez avoir au moins 2 réponses !");
        return;
    }

    QLineEdit *answerEdit = answerFields.takeLast();
    answersLayout->removeWidget(answerEdit);
    delete answerEdit;
}

// Sauvegarde de la question et des réponses
void QCM::saveQuestion()
{
    if (questionEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une question !");
        return;
    }

    QJsonObject questionData;
    questionData["question"] = questionEdit->text();

    QJsonArray answersArray;
    for (auto answerEdit : answerFields) {
        if (!answerEdit->text().isEmpty()) {
            answersArray.append(answerEdit->text());
        }
    }

    if (answersArray.size() < 2) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer au moins 2 réponses !");
        return;
    }

    questionData["answers"] = answersArray;

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

QCM::~QCM() {}
