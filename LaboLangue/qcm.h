#ifndef QCM_H
#define QCM_H

// === Qt Widgets / Layout ===
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QMessageBox>

// === Qt JSON / Fichiers ===
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>
#include <QPropertyAnimation>

#include <array>
#include <QString>
#include <QList>

class MainWindow;

namespace Ui {
class QCM;
}

using namespace std;

class QCM : public QDialog {
    Q_OBJECT

public:
    explicit QCM(QWidget *parent, MainWindow* parentWindow);
    ~QCM();

    int getSize() const { return questionWidgets.size(); }

signals:
    void fermetureQCM();

private:
    Ui::QCM *ui;
    MainWindow* mainWindow;

    // === Interface principale ===
    QVBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QGridLayout *questionsLayout;

    // === Zone d'ajout de question ===
    QGroupBox *addQuestionBox = nullptr;
    QPushButton *addQuestionButton;
    QPushButton *removeQuestionButton;
    QPushButton *saveButton;
    QPushButton *importQuestionButton;
    QLabel *nomQCMLabel;
    QLineEdit *nomQCM;

    // === Structure de question ===
    struct QuestionWidget {
        QSpinBox *questionNumberSpin;
        QLineEdit *questionEdit;
        QSpinBox *choiceCountSpin;
        QVBoxLayout *answersLayout;
        QList<QLineEdit*> answerFields;
        QList<QCheckBox*> correctAnswers;
        QHBoxLayout *buttonLayout;
        QPushButton *addAnswerButton;
        QPushButton *removeAnswerButton;
    };

    QList<QuestionWidget*> questionWidgets;

private slots:
    void addQuestion(QString *nomQ = new QString("Test"),
                     QString *numQ = new QString("1"),
                     QString *nbRep = new QString("2"),
                     std::array<std::array<QString, 2>, 4> choices = {{{QString("")}}});
    void removeQuestion();
    void saveQuestions();
    void addBoxAddQuestion();
    void addAnswers(QuestionWidget *question, QString *choix, QString *correct);
    void importQCM();
};

#endif // QCM_H
