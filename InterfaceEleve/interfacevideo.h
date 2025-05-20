#ifndef INTERFACEVIDEO_H
#define INTERFACEVIDEO_H
#include "mainwindow.h"
#include "qgraphicsscene.h"
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
#include <QGraphicsVideoItem>

// === Projet ===
class MainWindow;

namespace Ui {
class InterfaceVideo;
}

class InterfaceVideo : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceVideo(bool co, MainWindow* parentWindow,QWidget *parent = nullptr);

    ~InterfaceVideo();


private slots:
    void on_pushButton_SelectVideo_clicked();
    void on_pushButton_Avant10_clicked();
    void on_pushButton_Play_clicked();
    void on_pushButton_Pause_clicked();
    void on_pushButton_Apres10_clicked();
    //void on_horizontalSlider_sonVideo_actionTriggered(int action);
    void animateButtonClick(QPushButton* btn);
    void on_horizontalSlider_sliderReleased();
    void on_pushButtonReset_clicked();
    void on_verticalSlider_sonVideo_valueChanged(int value);
    void on_pushButton_Son_clicked();
    void updateChronoLabel();
    void faireClignoterLabel();


protected:
    void closeEvent(QCloseEvent *event);

private:
    MainWindow* mainWindow;
    Ui::InterfaceVideo *ui;

    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QSlider *slider;
    QGraphicsScene *scene = nullptr;
    QGraphicsVideoItem *videoItem = nullptr;


    bool CO = false;
    bool coMode;
    bool clignotementEtat;
    int resetCount = 0;
    static constexpr int maxResets = 3;
    QUdpSocket udpChrono;
    quint16 chronoPort =5558;
    QTimer *chronoTimer;
    QTime remainingTime;
    QTimer* clignotementTimer;


};

#endif // INTERFACEVIDEO_H
