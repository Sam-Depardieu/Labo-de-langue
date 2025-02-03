#ifndef INTERFACEAUDIO_H
#define INTERFACEAUDIO_H


#include <QDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui {
class interfaceaudio;
}

class interfaceaudio : public QDialog
{
    Q_OBJECT

public:
    explicit interfaceaudio(QWidget *parent = nullptr);
    ~interfaceaudio();

private slots:
    void on_pushButton_Avant_clicked();

    void on_pushButton_Play_clicked();

    void on_pushButton_Pause_clicked();

    void on_pushButton_Apres_clicked();

    void on_horizontalSlider_son_actionTriggered(int action);

    void on_pushButton_SelectionnerAudio_clicked();

private:
    Ui::interfaceaudio *ui;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QAudioOutput *audioOutput;
};

#endif // INTERFACEAUDIO_H
