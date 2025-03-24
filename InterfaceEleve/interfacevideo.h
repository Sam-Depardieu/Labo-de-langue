#ifndef INTERFACEVIDEO_H
#define INTERFACEVIDEO_H

#include <QDialog>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QCloseEvent>
#include <QProcess>

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
protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::InterfaceVideo *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};

#endif // INTERFACEVIDEO_H
