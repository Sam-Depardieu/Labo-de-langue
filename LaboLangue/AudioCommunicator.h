#include <QCoreApplication>
#include <QWebSocket>
#include <QAudioFormat>
#include <QAudioSource>
#include <QAudioSink>
#include <QByteArray>
#include <QIODevice>
#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>

class AudioCommunicator : public QObject {
    Q_OBJECT
public:
    AudioCommunicator(QObject* parent = nullptr) : QObject(parent), isConnected(false) {
        // Initialisation du WebSocket
        webSocket = new QWebSocket();
        webSocket->open(QUrl("ws://192.168.64.36:12345"));  // Connexion au serveur WebSocket

        connect(webSocket, &QWebSocket::connected, this, &AudioCommunicator::onConnected);
        connect(webSocket, &QWebSocket::disconnected, this, &AudioCommunicator::onDisconnected);
        connect(webSocket, &QWebSocket::binaryMessageReceived, this, &AudioCommunicator::onAudioReceived);

        // Configuration de l'audio (capture et sortie)
        QAudioFormat format;
        format.setSampleRate(16000);              // Fréquence d'échantillonnage (16 kHz)
        format.setChannelCount(1);                // Mono
        format.setSampleFormat(QAudioFormat::Int16);  // Taille de l'échantillon (16 bits)
        format.setSampleRate(16000);              // Type d'échantillon : entier signé

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

    ~AudioCommunicator() {
        // Nettoyer les ressources
        if (webSocket) {
            webSocket->close();
            delete webSocket;
        }
        if (audioSource) {
            audioSource->stop();
            delete audioSource;
        }
        if (audioSink) {
            audioSink->stop();
            delete audioSink;
        }
        if (audioDevice) {
            delete audioDevice;
        }
        if (outputDevice) {
            delete outputDevice;
        }
    }

    void sendAudioData() {
        // Verrouiller pour éviter les interférences avec l'écriture dans la même ressource
        QMutexLocker locker(&mutex);

        QByteArray audioData = audioDevice->readAll();
        if (!audioData.isEmpty()) {
            // Envoyer des blocs plus grands pour réduire la fréquence des messages
            const int chunkSize = 4096;  // Par exemple, envoyer 4096 octets à la fois
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
        isConnected = true;
    }

    void onDisconnected() {
        qDebug() << "WebSocket déconnecté!";
        isConnected = false;
        // Tentative de reconnexion après un délai
        QTimer::singleShot(1000, this, &AudioCommunicator::reconnect);
    }

    void reconnect() {
        if (!isConnected) {
            qDebug() << "Tentative de reconnexion...";
            webSocket->open(QUrl("ws://192.168.64.36:12345"));
        }
    }

private:
    QWebSocket *webSocket;
    QAudioSource *audioSource;
    QAudioSink *audioSink;
    QIODevice *audioDevice;
    QIODevice *outputDevice;
    QTimer *timer;
    QMutex mutex;  // Mutex pour sécuriser l'accès aux ressources partagées
    bool isConnected;  // Indique si la connexion WebSocket est active
};
