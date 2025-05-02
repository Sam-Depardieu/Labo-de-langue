#ifndef INTERFACEAUDIO_H
#define INTERFACEAUDIO_H

#include <QDialog>
#include <QMediaPlayer>
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
    explicit InterfaceAudio(bool CO, QWidget *parent = nullptr);
    ~InterfaceAudio();

private slots:
    void on_pushButton_Avant_clicked();

    void on_pushButton_Play_clicked();

    void on_pushButton_Pause_clicked();

    void on_pushButton_SelectAudio_clicked();

    void on_horizontalSliderSon_actionTriggered(int action);

    void on_pushButton_Apres_clicked();
    void on_horizontalSlider_sliderReleased();

protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::InterfaceAudio *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

    bool CO = false;

};

#endif // INTERFACEAUDIO_H
