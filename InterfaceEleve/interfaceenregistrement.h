#ifndef INTERFACEENREGISTREMENT_H
#define INTERFACEENREGISTREMENT_H

#include <QDialog>
#include <QTimer>
<<<<<<< HEAD
#include <QFile>
=======
#include <QMediaPlayer>
>>>>>>> a785a414c4110abf11314b48660e0405a7d6a541
#include <QAudioInput>
#include <QKeyEvent>
#include <QDebug>
#include <QMediaRecorder>
#include <QAudioOutput>
#include <QUrl>
#include <QStandardPaths>
<<<<<<< HEAD
=======
#include <QFile>
>>>>>>> a785a414c4110abf11314b48660e0405a7d6a541
#include <QMediaFormat>
#include <QUdpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMediaCaptureSession>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidgetAction>
#include <QLabel>
//#include <QAudioRecorder>
//#include <QAudioProbe>
//#include <QAudioEncoderSettings>
//#include <QtMultimedia>


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
    void on_pushButtonAvancer_clicked();

    void on_pushButtonEnregistrer_clicked();

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
    QMenu *volumeMenu;  // Menu pour les sliders de volume
    QSlider *sliderPrincipal;  // Slider pour le volume principal
    QSlider *sliderSecondaire;  // Slider pour le volume secondaire
    void setupVolumeMenu();  // Fonction pour configurer le menu de volume
    bool isButtonSpeak = false;  // Déclaration et initialisation


    void resetTimer();  // Déclaration de la fonction resetTimer
};

#endif // INTERFACEENREGISTREMENT_H
