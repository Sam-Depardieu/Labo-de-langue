#ifndef INTERFACEQCM_H
#define INTERFACEQCM_H

#include "qudpsocket.h"
#include <QDialog>

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

    //void on_pushButtonEnregistrer_clicked();

    void on_pushButtonQuestionSuivante_clicked();




    void on_textEditFeedBack_2_copyAvailable(bool b);

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

    QStringList questions;
    int currentQuestionIndex = 0;

    void loadQuestions(const QString &filePath);
    void showCurrentQuestion();
};

#endif // INTERFACEQCM_H
