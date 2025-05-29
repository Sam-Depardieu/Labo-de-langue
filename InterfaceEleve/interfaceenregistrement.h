#ifndef INTERFACEENREGISTREMENT_H
#define INTERFACEENREGISTREMENT_H

#include <QDialog>
#include <QTimer>
#include <QFile>
#include <QMediaPlayer>
#include <QAudioInput>
#include <QKeyEvent>
#include <QDebug>
#include <QMediaRecorder>
#include <QAudioOutput>
#include <QUrl>
#include <QStandardPaths>
#include <QMediaFormat>
#include <QUdpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMediaCaptureSession>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidgetAction>
#include <QLabel>
#include <QTextEdit>
#include <QSpinBox>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>
#include <QMediaFormat>
#include <QUrl>
#include <QPropertyAnimation>
#include <QAbstractAnimation>
#include <QSequentialAnimationGroup>
#include <QUdpSocket>
#include <QTimer>
#include "mainwindow.h"

namespace Ui {
class InterfaceEnregistrement;

}

class InterfaceEnregistrement : public QDialog {
    Q_OBJECT

public:
    explicit InterfaceEnregistrement(MainWindow* parentWindow, QWidget *parent = nullptr);
    ~InterfaceEnregistrement();
    void receiveResponse();

private slots: 
    void on_pushButtonSon_clicked();
    void on_pushButtonAppelProf_clicked();
    void on_pushButtonEnregistrer_clicked();
    void on_pushButtonSpeak_clicked();
    void on_pushButtonPlay_clicked();
    void on_pushButtonRetourArriere_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonPause_clicked();
    void animateButtonClick(QPushButton* btn);
    void updateChrono();
    void rewindChrono();
    void updateChronoLabel();
    void updateChronoGlobal();
    void faireClignoterLabel();
    void onRecorderErrorOccurred(QMediaRecorder::Error error, const QString &errorString);
    void onRecorderStateChanged(QMediaRecorder::RecorderState state);
    void checkPlaybackPosition(qint64 position);



private:
    Ui::InterfaceEnregistrement *ui;
    MainWindow *mainWindow;

    bool isButtonAppelProfImage;

    QMediaRecorder *mediaRecorder;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QAudioInput *audioInput;
    QMediaCaptureSession captureSession;

    // Fichier et chrono
    QString audioFilePath;
    QString workspace;
    int studentId;
    int totalSecondes = 0;
    int lastRecordedTime = 0;
    int    elapsedSeconds;
    QString outputFile;
    QMediaRecorder*audioRecorder;


    qint64 pausedTime = 0;
    qint64 pauseTime = 0;
    bool isRewinding = false;
    bool isPaused = false;
    bool isRecordingPaused = false;
    bool speakButtonClicked = false;
    bool isButtonSpeak = false;
    bool Professor = false;
    bool clignotementEtat;

    // Timers
    QTimer *timer;
    QTimer *rewindTimer;

    // Widgets et UI
    QMenu *volumeMenu;
    QSlider *sliderPrincipal;
    QSlider *sliderSecondaire;
    QTextEdit *textedit;
    QMessageBox *messagebox;
    QSpinBox *spinbox;

    // Réseau
    QUdpSocket udpSocket;
    quint16 responsePort = 5559;

    // Fonctions internes
    void setupVolumeMenu();
    void setButtonIcons();
    void setButtonIcon(QPushButton *button, const QString &imagePath);

    QUdpSocket udpChrono;
    quint16 chronoPort =5558;
    QString lastAudioFilePath;
    QTimer *chronoTimer;
    QTime remainingTime;
    QTimer* clignotementTimer;
    QString sessionPATH = "";
    QString nomEleve = "";

};

#endif // INTERFACEENREGISTREMENT_H
