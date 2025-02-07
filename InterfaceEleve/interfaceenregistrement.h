#ifndef INTERFACEENREGISTREMENT_H
#define INTERFACEENREGISTREMENT_H

#include "qmediaplayer.h"
#include <QDialog>
#include <QTimer>

namespace Ui {
class InterfaceEnregistrement;
}

class InterfaceEnregistrement : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceEnregistrement(QWidget *parent = nullptr);
    ~InterfaceEnregistrement();

private slots:
    void on_pushButtonSon_clicked();

    void on_pushButtonSignet_clicked();

    void on_pushButtonFavoris_clicked();

    void on_pushButtonRevenirALaPhrasePrecedente_clicked();

    void on_pushButtonRepeter_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButtonSurveiller_clicked();

    void on_pushButtonRetourArriere_clicked();

    void on_pushButtonPause_clicked();

    void on_pushButtonAvancer_clicked();

    void on_pushButtonSpeak_clicked();

    void on_pushButtonPlay_clicked();

    void on_pushButtonAppelProf_clicked();
    void updateChrono();

private:
    Ui::InterfaceEnregistrement *ui;
    QTimer *timer;
    int initialSecondes;
    int pauseClickCount;
    int pausedSecondes;
    int totalSecondes = 0;
    bool speakButtonClicked = false;
    QString audioFilePath;
    QMediaPlayer *player;
    bool isRewinding = false;
    QTimer *rewindTimer;
    bool isPaused = false;

};

#endif // INTERFACEENREGISTREMENT_H
