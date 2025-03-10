#include <QCoreApplication>
#include <QWebSocket>
#include <QAudioFormat>
#include <QAudioSource>
#include <QAudioSink>
#include <QByteArray>
#include <QIODevice>
#include <QTimer>
#include <QDebug>

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
        format.setSampleRate(16000);              // Fréquence d'échantillonnage (16 kHz)
        format.setChannelCount(1);                // Mono
        format.setSampleFormat(QAudioFormat::Int32);                 // Taille de l'échantillon (16 bits)
        format.setSampleRate(16000); // Type d'échantillon : entier signé

        // Créer l'input et output pour la capture et la lecture audio
        audioSource = new QAudioSource(format, this);
        audioSink = new QAudioSink(format, this);

        // Démarrer la capture et la lecture
        audioDevice = audioSource->start();  // Démarre l'enregistrement audio
        outputDevice = audioSink->start();   // Démarre la lecture audio

        // Timer pour envoyer des données audio à intervalles réguliers
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &AudioCommunicator::sendAudioData);
        timer->start(50);  // Envoie les données toutes les 50ms (20 Hz)
    }

    void sendAudioData() {
        QByteArray audioData = audioDevice->readAll();
        if (!audioData.isEmpty()) {
            int chunkSize = 1024;  // Par exemple, envoyer 1024 octets à la fois
            while (!audioData.isEmpty()) {
                QByteArray chunk = audioData.left(chunkSize);
                webSocket->sendBinaryMessage(chunk);
                audioData = audioData.mid(chunkSize);
            }
        }
    }

    void onAudioReceived(const QByteArray &data) {
        if (!data.isEmpty()) {
            qDebug() << "Received audio data size: " << data.size();
            qint64 bytesWritten = outputDevice->write(data);  // Écrire les données dans le périphérique audio
            if (bytesWritten == -1) {
                qWarning() << "Error writing to output device";
            }
        } else {
            qWarning() << "Received empty audio data";
        }
    }

private slots:
    void onConnected() {
        qDebug() << "WebSocket connecté!";
    }

    void onDisconnected() {
        qDebug() << "WebSocket déconnecté!";
    }

private:
    QWebSocket *webSocket;
    QAudioSource *audioSource;  // Utilisation de QAudioSource pour capturer l'audio
    QAudioSink *audioSink;      // Utilisation de QAudioSink pour la sortie audio
    QIODevice *audioDevice;     // Le périphérique pour lire les données audio
    QIODevice *outputDevice;    // Le périphérique pour écrire les données audio
    QTimer *timer;             // Timer pour envoyer les données audio à intervalles réguliers
};
