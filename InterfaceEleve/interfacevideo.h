#ifndef INTERFACEVIDEO_H
#define INTERFACEVIDEO_H
#include "qslider.h"
#include <QDialog>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QCloseEvent>
#include <QProcess>
#include <QVideoWidget>
#include <QPropertyAnimation>
#include <QAbstractAnimation>
#include <QSequentialAnimationGroup>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QUdpSocket>
#include <QTimer>
namespace Ui {
class InterfaceVideo;
}

class InterfaceVideo : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceVideo(bool co, QWidget *parent = nullptr);
    ~InterfaceVideo();

private slots:
    void on_pushButton_SelectVideo_clicked();
    void on_pushButton_Avant10_clicked();
    void on_pushButton_Play_clicked();
    void on_pushButton_Pause_clicked();
    void on_pushButton_Apres10_clicked();
    void on_horizontalSlider_sonVideo_actionTriggered(int action);
    void animateButtonClick(QPushButton* btn);
    void on_horizontalSlider_sliderReleased();
<<<<<<< HEAD
=======

>>>>>>> 6136a2c945ee1c817e08a9391efe918c1eb4f976
    void on_pushButtonReset_clicked();
    void onUdpTimeout();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::InterfaceVideo *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QSlider *slider;

    bool CO = false;
    bool coMode;
    int resetCount = 0;
    static constexpr int maxResets = 3;
    QUdpSocket udpChrono;
    quint16 chronoPort =5558;

};

#endif // INTERFACEVIDEO_H
