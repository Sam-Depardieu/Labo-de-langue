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

namespace Ui {
class QCM;
}

class QCM : public QDialog
{
    Q_OBJECT

public:
    explicit QCM(QWidget *parent = nullptr);
    ~QCM();

private slots:
    void addAnswer();
    void removeAnswer();
    void saveQuestion();

private:
    Ui::QCM *ui;
    QVBoxLayout *mainLayout;
    QVBoxLayout *answersLayout;
    QLineEdit *questionEdit;
    QSpinBox *questionNumberSpin;
    QSpinBox *choiceCountSpin;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *saveButton;
    QList<QHBoxLayout *> answerLayouts;
    QList<QLineEdit *> answerFields;
    QList<QCheckBox *> correctAnswers;
};

#endif // QCM_H
