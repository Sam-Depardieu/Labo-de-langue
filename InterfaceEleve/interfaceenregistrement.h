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
#include <QFile>
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
    bool isPaused = false;
    qint64 pauseTime = 0;
    int lastRecordedTime = 0;
    bool isRecordingPaused = false;
    qint64 pausedTime = 0;
    QMenu *volumeMenu;
    QSlider *sliderPrincipal;
    QSlider *sliderSecondaire;
    void setupVolumeMenu();
    bool isButtonSpeak = false;
    QTextEdit *textedit;
    QMessageBox *messagebox;
    QSpinBox *spinbox;
    void showFeedbackDialog();
    void resetTimer();
    void setButtonIcons();
    void updateChronoLabel();
    void setButtonIcon(QPushButton *button, const QString &imagePath);
    bool isTeacher = false; // Flag pour vérifier si l'utilisateur est un professeur
};

#endif // INTERFACEENREGISTREMENT_H
