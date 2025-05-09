#ifndef INTERFACEQCM_H
#define INTERFACEQCM_H

#include "qudpsocket.h"
#include <QDialog>
#include <QJsonArray>

namespace Ui {
class InterfaceQCM;
}

class InterfaceQCM : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceQCM(QWidget *parent = nullptr);
    ~InterfaceQCM();
    void receiveResponse();

    QString getConsigne() {return consigne;};

private slots:
    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

    void on_pushButtonEffacerReponse_clicked();

    void on_pushButtonQuestionSuivante_clicked();


<<<<<<< HEAD
=======
    void on_pushButtonQuestionPrecedente_clicked();
>>>>>>> ab00f03050a4c34c7a0a34ada0a0bd2614051d8f

private:
    Ui::InterfaceQCM *ui;
    bool isButton1Image; // Déclaration pour Button 1
    bool isButton2Image; // Déclaration pour Button 2
    bool isButton3Image; // Déclaration pour Button 3
    bool isButton4Image;
    void setButtonIcons();
    void setButtonIcon(QPushButton *button, const QString &imagePath);

    QUdpSocket udpSocketConsigne;
    quint16 consignePort = 5558;

    QString consigne = "";
    bool isTeacher = false;

    QJsonArray questionArray;
    int currentQuestionIndex;

    void loadQuestionsJson(const QString &filePath);
    void showCurrentQuestion();
};

#endif // INTERFACEQCM_H
