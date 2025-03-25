#ifndef QCM_H
#define QCM_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QStandardPaths>
#include <QScrollArea>
#include <QGroupBox>
#include <QPropertyAnimation>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileDialog>

using namespace std;

class MainWindow;


namespace Ui {
class QCM;
}

class QCM : public QDialog
{
    Q_OBJECT

    public:
        QCM(QWidget *parent, MainWindow* parentWindow);
        ~QCM();



    private:
        Ui::QCM *ui;
        MainWindow* mainWindow;
        QVBoxLayout *mainLayout;
        int col;
        QScrollArea *scrollArea;
        QWidget *scrollWidget;
        QGridLayout *questionsLayout;
        QGroupBox *addQuestionBox = nullptr;
        QPushButton *addQuestionButton;
        QPushButton *removeQuestionButton;
        QPushButton *saveButton;
        QPushButton *importQuestionButton;
        QLabel *nomQCMLabel;
        QLineEdit *nomQCM;

        array<array<QString, 2>, 4> choices = {{{QString("")}}};


        struct QuestionWidget {
            QSpinBox *questionNumberSpin;
            QLineEdit *questionEdit;
            QSpinBox *choiceCountSpin;
            QVBoxLayout *answersLayout;
            QList<QLineEdit *> answerFields;
            QList<QCheckBox *> correctAnswers;
            QHBoxLayout *buttonLayout;
            QPushButton *addAnswerButton;
            QPushButton *removeAnswerButton;
        };

        QList<QuestionWidget *> questionWidgets;

    private slots:
        void addQuestion(QString *nomQ = new QString("Test"), QString *numQ = new QString("1"), QString *nbRep = new QString("2"));
        void removeQuestion();
        void saveQuestions();
        void addBoxAddQuestion();
        void addAnswers(QuestionWidget* question, QString *choix, QString *correct);
        void importQCM();
};

#endif // QCM_H
