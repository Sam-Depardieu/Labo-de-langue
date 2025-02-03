#ifndef INTERFACEVIDEO_H
#define INTERFACEVIDEO_H

#include <QDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui {
class InterfaceVideo;
}

class InterfaceVideo : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceVideo(QWidget *parent = nullptr);
    ~InterfaceVideo();

private slots:
    void on_pushButton_SelectVideo_clicked();

    void on_pushButton_Avant10_clicked();

    void on_pushButton_Play_clicked();

    void on_pushButton_Pause_clicked();

    void on_pushButton_Apres10_clicked();

    void on_horizontalSlider_sonVideo_actionTriggered(int action);

private:
    Ui::InterfaceVideo *ui;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QAudioOutput *audioOutput;
};

#endif // INTERFACEVIDEO_H
