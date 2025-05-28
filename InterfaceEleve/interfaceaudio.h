#ifndef INTERFACEAUDIO_H
#define INTERFACEAUDIO_H

#include <QDialog>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QAudioOutput>
#include <QPropertyAnimation>
#include <QAbstractAnimation>
#include <QSequentialAnimationGroup>
#include <QUdpSocket>
#include <QTimer>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>

class MainWindow;

namespace Ui {
class InterfaceAudio;
}

class InterfaceAudio : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceAudio(bool CO, MainWindow* parentWindow,QWidget *parent = nullptr);

    void setAudioPause(bool pause);

    ~InterfaceAudio();
private slots:
    void on_pushButton_Play_clicked();
    void on_pushButton_Pause_clicked();
    void on_pushButton_Avant_clicked();
    void on_pushButton_Apres_clicked();
    void on_horizontalSlider_sliderReleased();
    void animateButtonClick(QPushButton* btn);
    void on_pushButtonReset_clicked();
    void on_pushButton_Son_clicked();
    void updateChronoLabel();
    void faireClignoterLabel();

    void receiveCmd();
    void on_pushButtonAppelProf_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::InterfaceAudio *ui;
    MainWindow *mainWindow;

    // Lecture audio
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

    // Mode de fonctionnement
    bool CO = false;
    bool coMode;
    bool clignotementEtat;
    int resetCount = 0;
    static constexpr int maxResets = 3;

    QUdpSocket udpSocketCMD;
    quint16 cmdPort = 5557;

    QUdpSocket udpChrono;
    quint16 chronoPort =5558;
    QTimer *chronoTimer;
    QTime remainingTime;
    QTimer* clignotementTimer;

};

#endif // INTERFACEAUDIO_H
