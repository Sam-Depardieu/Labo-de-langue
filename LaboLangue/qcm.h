#ifndef QCM_H
#define QCM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QStandardPaths>
#include <QMessageBox>

class QCM : public QWidget
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
    QVBoxLayout *mainLayout;
    QVBoxLayout *answersLayout;
    QLineEdit *questionEdit;
    QVector<QLineEdit*> answerFields;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *saveButton;
};

#endif // QCM_H
