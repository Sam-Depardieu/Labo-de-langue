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

namespace Ui {
class InterfaceAudio;
}

class InterfaceAudio : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceAudio(bool CO, QWidget *parent = nullptr);
    ~InterfaceAudio();

public slots:
    void mettreAJourChrono(const QString &temps);
    void chronoTermine();

private slots:
    void on_pushButton_SelectAudio_clicked();
    void on_pushButton_Play_clicked();
    void on_pushButton_Pause_clicked();
    void on_pushButton_Avant_clicked();
    void on_pushButton_Apres_clicked();
    void on_horizontalSlider_sliderReleased();
    void animateButtonClick(QPushButton* btn);

    void on_pushButtonReset_clicked();

    void receiveChrono();
    void on_pushButton_Son_clicked();



protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::InterfaceAudio *ui;

    // Lecture audio
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

    // Mode de fonctionnement
    bool CO = false;
    bool coMode;
    int resetCount = 0;
    static constexpr int maxResets = 3;

    QUdpSocket udpChrono;
    quint16 chronoPort =5558;
};

#endif // INTERFACEAUDIO_H
