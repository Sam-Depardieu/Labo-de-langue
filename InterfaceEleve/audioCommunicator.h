#include <QCoreApplication>
#include <QWebSocket>
#include <QAudioSource>
#include <QAudioSink>
#include <QByteArray>
#include <QIODevice>
#include <QTimer>

class AudioCommunicator : public QObject {
    Q_OBJECT
public:
    AudioCommunicator(QObject* parent = nullptr) : QObject(parent) {
        // Initialisation du WebSocket
        webSocket = new QWebSocket();
        webSocket->open(QUrl("ws://192.168.64.36:12345")); // Connexion au serveur WebSocket

        connect(webSocket, &QWebSocket::connected, this, &AudioCommunicator::onConnected);
        connect(webSocket, &QWebSocket::disconnected, this, &AudioCommunicator::onDisconnected);
        connect(webSocket, &QWebSocket::binaryMessageReceived, this, &AudioCommunicator::onAudioReceived);

        // Configuration de l'audio (capture et sortie)
        QAudioFormat format;
        format.setSampleRate(16000);               // Fréquence d'échantillonnage (16 kHz)
        format.setChannelCount(1);                 // Mono
        format.setSampleRate(16);                  // Taille de l'échantillon (16 bits)
        format.setSampleFormat(QAudioFormat::Int16);  // Type d'échantillon : entier signé

        audioSource = new QAudioSource(format, this); // Utilisation de QAudioSource pour la capture audio
        audioSink = new QAudioSink(format, this);     // Utilisation de QAudioSink pour la sortie audio

        audioDevice = audioSource->start();  // Démarre l'enregistrement audio
        outputDevice = audioSink->start();   // Démarre la lecture audio
    }

    void sendAudioData() {
        // Lire les données audio capturées et envoyer au serveur WebSocket
        QByteArray audioData = audioDevice->readAll();
        webSocket->sendBinaryMessage(audioData);
    }

private slots:
    void onConnected() {
        qDebug() << "WebSocket connecté!";
    }

    void onDisconnected() {
        qDebug() << "WebSocket déconnecté!";
    }

    void onAudioReceived(const QByteArray &data) {
        // Lire l'audio reçu depuis le WebSocket et le jouer
        outputDevice->write(data);
    }



private:
    QWebSocket *webSocket;
    QAudioSource *audioSource;  // Utilisation de QAudioSource pour capturer l'audio
    QAudioSink *audioSink;
    QIODevice *audioDevice;
    QIODevice *outputDevice;
};
