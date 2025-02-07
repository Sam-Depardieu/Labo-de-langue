#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customgraphicsitemgroup.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class VoiceChat : public QObject {
    Q_OBJECT
public:
    VoiceChat(const QHostAddress &peerAddress, quint16 peerPort, quint16 localPort, QObject *parent = nullptr)
        : QObject(parent), peerAddress(peerAddress), peerPort(peerPort) {
        // 📌 Définition des paramètres audio
        QAudioFormat format;
        format.setSampleRate(44100);
        format.setChannelCount(1);  // Mono pour économiser la bande passante
        format.setSampleFormat(QAudioFormat::Int16); // Format PCM 16 bits
        // 📌 Vérifier si le format est supporté
        QAudioDevice inputDevice = QMediaDevices::defaultAudioInput();
        QAudioDevice outputDevice = QMediaDevices::defaultAudioOutput();
        if (!inputDevice.isFormatSupported(format) || !outputDevice.isFormatSupported(format)) {
            qWarning() << "Format audio non supporté";
            return;
        }
        // 🎤 Configurer la source audio (microphone)
        audioSource = new QAudioSource(inputDevice, format, this);
        audioDeviceIn = audioSource->start();  // Démarrer la capture
        // 🔊 Configurer la sortie audio (haut-parleur)
        audioSink = new QAudioSink(outputDevice, format, this);
        audioDeviceOut = audioSink->start(); // Préparer la lecture
        // 📡 Initialiser le socket UDP
        udpSocket = new QUdpSocket(this);
        udpSocket->bind(QHostAddress::AnyIPv4, localPort); // Écoute sur un port local
        // 🔄 Connecter les signaux
        connect(audioDeviceIn, &QIODevice::readyRead, this, &VoiceChat::sendAudioData);
        connect(udpSocket, &QUdpSocket::readyRead, this, &VoiceChat::receiveAudioData);
    }
public slots:
    // Envoie l'audio
    void sendAudioData() {
        QByteArray data = audioDeviceIn->readAll();  // Lire les données du micro
        udpSocket->writeDatagram(data, peerAddress, peerPort);  // Envoyer via UDP
    }
    // Lecture de l'audio reçu
    void receiveAudioData() {
        while (udpSocket->hasPendingDatagrams()) {
            QByteArray buffer;
            buffer.resize(udpSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;
            udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
            audioDeviceOut->write(buffer);  // Jouer l'audio reçu en temps réel
        }
    }
private:
    QAudioSource *audioSource;
    QAudioSink *audioSink;
    QIODevice *audioDeviceIn;
    QIODevice *audioDeviceOut;
    QUdpSocket *udpSocket;
    QHostAddress peerAddress;
    quint16 peerPort;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    int idActivite = 0;
    std::vector<CustomGraphicsItemGroup*> listeRasp = {};
    std::vector<CustomGraphicsItemGroup*> listeParticipant = {};

    ~MainWindow();

private slots:
    void on_PlanButton_clicked();
    void keyPressEvent(QKeyEvent *event);
    void loadImagesFromDB();
    bool connectToDatabase();
    void onImageGroupDoubleClicked();
    void setupActivitiesComboBox();
    void setupClassesComboBox();
    void on_SessionButton_clicked();
    void on_ChoixActivite_currentIndexChanged(int index);
    void on_selectManuel_clicked();
    void editStatusButton(QPushButton *button, bool status);
    void addHorizontalLayout(QVBoxLayout *layout, QWidget *widget1, QWidget *widget2);
    void addHorizontalLayout(QVBoxLayout *layout, QWidget *widget1, QWidget *widget2, QWidget *widget3);
    void addButtonRow(QVBoxLayout *layout, QWidget *button1, QWidget *button2, QWidget *button3);

    void on_selectAll_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QSqlDatabase db;
    QGraphicsPixmapItem *item;
    int typeActivite;

public:
    bool selectionParticipants;

};
#endif // MAINWINDOW_H
