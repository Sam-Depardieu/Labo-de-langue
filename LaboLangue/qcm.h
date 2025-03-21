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


QT_BEGIN_NAMESPACE
namespace Ui {
class QCM;
}
QT_END_NAMESPACE

class QCM : public QDialog
{
    Q_OBJECT

public:
    explicit QCM(QWidget *parent = nullptr);
    ~QCM();

private slots:
    void addQuestion();
    void removeQuestion();
    void saveQuestions();
    void addBoxAddQuestion();

private:
    Ui::QCM *ui;
    QVBoxLayout *mainLayout;
    int col;
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QGridLayout *questionsLayout;
    QPushButton *addQuestionButton;
    QPushButton *removeQuestionButton;
    QPushButton *saveButton;

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
};

#endif // QCM_H
