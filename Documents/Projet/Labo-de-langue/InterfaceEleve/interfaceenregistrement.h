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
#include <QMessageBox>
#include <QAudioOutput>  // Utiliser QAudioOutput pour la sortie audio
#include <QUrl>
#include <QStandardPaths>
#include <QFile>
#include <QTimer>
#include <QDebug>
#include <QMediaFormat>
#include <QUdpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QApplication>
#include <QVBoxLayout>
#include <QSlider>
#include <windows.h>  // Nécessaire pour modifier le volume système
#include <mmsystem.h> // 📌 Nécessaire pour waveOutSetVolume
#pragma comment(lib, "winmm.lib") // 📌 Ajoute la bibliothèque winmm.lib


namespace Ui {
class InterfaceEnregistrement;
}

class InterfaceEnregistrement : public QDialog
{
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

private:
    Ui::InterfaceEnregistrement *ui;
    QMediaRecorder *mediaRecorder;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;  // Déclaration de QAudioOutput ici
    QAudioInput *audioInput;    // Optionnel, si vous en avez besoin pour l'entrée audio
    QTimer *timer;
    QTimer *rewindTimer;
    bool isRewinding;
    int totalSecondes;
    bool speakButtonClicked;
    QString audioFilePath;
    int studentId;
    static void setSystemVolume(int volume); // 🔹 Déclaration de la fonction ici
};

#endif // INTERFACEENREGISTREMENT_H
