#ifndef INTERFACEENREGISTREMENT_H
#define INTERFACEENREGISTREMENT_H

#include <QDialog>
#include <QTimer>
#include <QFile>
#include <QMediaPlayer>
#include <QMediaRecorder>
#include <QAudioInput>
#include <QKeyEvent>
#include <QDebug>
#include <QMediaRecorder>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QStandardPaths>
#include <QFile>
#include <QTimer>
#include <QDebug>
#include <QMediaFormat>
#include <QUdpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMediaCaptureSession>

namespace Ui {
class InterfaceEnregistrement;
}

class InterfaceEnregistrement : public QDialog {
    Q_OBJECT

public:
    explicit InterfaceEnregistrement(QWidget *parent = nullptr);
    ~InterfaceEnregistrement();

private slots:
    void on_pushButtonSpeak_clicked();
    void on_pushButtonPause_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonSon_clicked();
    void on_pushButtonRetourArriere_clicked();
    void on_pushButtonAppelProf_clicked();
    void updateChrono();
    void rewindChrono();
    void checkPlaybackPosition(qint64 position);
    void onRecorderStateChanged(QMediaRecorder::RecorderState state);
    void onRecorderErrorOccurred(QMediaRecorder::Error error, const QString &errorString);
    void on_pushButtonPlay_clicked();
    void on_pushButtonAvancer_clicked();

private:
    Ui::InterfaceEnregistrement *ui;
    QMediaRecorder *mediaRecorder;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QAudioInput *audioInput;
    QTimer *timer;
    QTimer *rewindTimer;
    QMediaCaptureSession captureSession;
    bool isRewinding;
    int totalSecondes;
    bool speakButtonClicked;
    QString audioFilePath;
    int studentId;
    bool isPaused = false;  // Indique si la lecture est en pause
    qint64 pauseTime = 0;
    int lastRecordedTime = 0;
    bool isRecordingPaused = false;  // Indique si l'enregistrement est en pause
    qint64 pausedTime = 0;           // Sauvegarde le temps de pause


    void resetTimer();  // Déclaration de la fonction resetTimer
};

#endif // INTERFACEENREGISTREMENT_H
