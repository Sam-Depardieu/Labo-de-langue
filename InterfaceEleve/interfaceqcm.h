#ifndef INTERFACEQCM_H
#define INTERFACEQCM_H

#include <QDialog>
#include <QJsonArray>
#include <QUdpSocket>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QDir>
#include <QStandardPaths>
#include <QString>

namespace Ui {
class InterfaceQCM;
}

class InterfaceQCM : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceQCM(QWidget *parent = nullptr, const QString &filePath = "");
    ~InterfaceQCM();
    void receiveResponse();
    QString getConsigne() { return consigne; }

private slots:
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();
    void on_pushButton4_clicked();
    void on_pushButtonSoumettre_clicked();
    void on_pushButtonEffacerReponse_clicked();
    void on_pushButtonQuestionSuivante_clicked();
    void on_pushButtonQuestionPrecedente_clicked();

    void onUdpNomFichierRecu();
    void updateChronoLabel();
    void faireClignoterLabel();


    void on_pushButtonAppelProf_clicked();

private:
    Ui::InterfaceQCM *ui;
    bool isButton1Image;
    bool isButton2Image;
    bool isButton3Image;
    bool isButton4Image;
    bool isButtonAppelProfImage;
    void setButtonIcons();

    QUdpSocket udpSocketConsigne;
    quint16 consignePort = 5558;

    QString consigne = "";
    bool Professor = false;
    bool clignotementEtat;

    QJsonArray questionArray;
    int currentQuestionIndex;

    void loadQuestionsJson(const QString &filePath);
    void showCurrentQuestion();
    QUdpSocket udpChrono;
    quint16 chronoPort = 5558;

    QUdpSocket udpSocketNomFichier;
    quint16 portNomFichier = 5561;
    QString fichierRecu;
    QTimer *chronoTimer;
    QTime remainingTime;
    QTimer* clignotementTimer;


};

#endif // INTERFACEQCM_H
