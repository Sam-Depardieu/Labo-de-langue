#ifndef INTERFACEAUDIO_H
#define INTERFACEAUDIO_H

#include <QDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui {
class InterfaceAudio;
}

class InterfaceAudio : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceAudio(QWidget *parent = nullptr);
    ~InterfaceAudio();

private slots:
    void on_pushButton_Avant_clicked();

    void on_pushButton_Play_clicked();

    void on_pushButton_Pause_clicked();

    void on_pushButton_SelectAudio_clicked();

    void on_horizontalSliderSon_actionTriggered(int action);

    void on_pushButton_Apres_clicked();

private:
    Ui::InterfaceAudio *ui;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QAudioOutput *audioOutput;

};

#endif // INTERFACEAUDIO_H
