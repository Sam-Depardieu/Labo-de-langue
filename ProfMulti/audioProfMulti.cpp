    #include "audioProfMulti.h"

    AudioProfMulti::AudioProfMulti(const QHostAddress &serverAddr, quint16 port, const QString &group, QObject *parent)
        : QObject(parent), udpSocket(new QUdpSocket(this)), serverAddress(serverAddr), serverPort(port), group(group)
    {

        // Lister les périphériques d'entrée audio (microphones) disponibles
        auto inputDevices = QMediaDevices::audioInputs();

        qDebug() << "Périphériques d'entrée disponibles :";

        // Afficher les noms des périphériques d'entrée audio
        for (const QAudioDevice &device : inputDevices) {
            qDebug() << "ENTREE :" << device.id() << "," << device.description();
        }
        for (const QAudioDevice &device : inputDevices) {
            qDebug() << "Périphérique d'entrée : " << device.description();

            QAudioDevice deviceInfo(device);
            QAudioFormat format;

            // Vérification de plusieurs configurations de format
            QList<QAudioFormat::SampleFormat> formatsToTest = {
                QAudioFormat::Int16,
                QAudioFormat::Int32,
                QAudioFormat::Float,
                QAudioFormat::UInt8
            };

            for (QAudioFormat::SampleFormat formatType : formatsToTest) {
                format.setSampleFormat(formatType);
                format.setSampleRate(44100);  // Fréquence d'échantillonnage à 44.1 kHz
                format.setChannelCount(2);    // Mono

                if (deviceInfo.isFormatSupported(format)) {
                    qDebug() << "Format supporté :"
                             << "SampleRate:" << format.sampleRate()
                             << "Channels:" << format.channelCount()
                             << "SampleFormat:" << format.sampleFormat();
                } else {
                    qDebug() << "Format non supporté :"
                             << "SampleRate:" << format.sampleRate()
                             << "Channels:" << format.channelCount()
                             << "SampleFormat:" << format.sampleFormat();
                }
            }
        }
        // Lister les périphériques d'entrée audio (microphones) disponibles
        auto outputDevices = QMediaDevices::audioOutputs();


        qDebug() << "Périphériques de sortie disponibles :";

        // Afficher les noms des périphériques d'entrée audio
        for (const QAudioDevice &device : outputDevices) {
            qDebug() << "SORTIE :" << device.id() << "," << device.description();
        }
        for (const QAudioDevice &device : outputDevices) {
            qDebug() << "Périphérique de sortie : " << device.description();

            QAudioDevice deviceInfo(device);
            QAudioFormat format;

            // Vérification de plusieurs configurations de format
            QList<QAudioFormat::SampleFormat> formatsToTest = {
                QAudioFormat::Int16,
                QAudioFormat::Int32,
                QAudioFormat::Float,
                QAudioFormat::UInt8
            };

            for (QAudioFormat::SampleFormat formatType : formatsToTest) {
                format.setSampleFormat(formatType);
                format.setSampleRate(44100);  // Fréquence d'échantillonnage à 44.1 kHz
                format.setChannelCount(2);    // Mono

                if (deviceInfo.isFormatSupported(format)) {
                    qDebug() << "Format supporté :"
                             << "SampleRate:" << format.sampleRate()
                             << "Channels:" << format.channelCount()
                             << "SampleFormat:" << format.sampleFormat();
                } else {
                    qDebug() << "Format non supporté :"
                             << "SampleRate:" << format.sampleRate()
                             << "Channels:" << format.channelCount()
                             << "SampleFormat:" << format.sampleFormat();
                }
            }
        }
        if (inputDevices.isEmpty() || outputDevices.isEmpty()) {
            qDebug() << "Aucun périphérique audio disponible.";
            return;
        }
        // Choisir le périphérique d'entrée et de sortie (par exemple, le premier périphérique)
        int inputSelectedDeviceIndex = 0;  // Modifier l'index ici pour choisir un autre périphérique
        int outputSelectedDeviceIndex = 0;  // Modifier l'index ici pour choisir un autre périphérique

        // Utiliser le périphérique sélectionné pour créer un QAudioInput
        //audioInput = new QAudioInput(inputDevices[selectedDeviceIndex],this);




        inputAudioDevice = QMediaDevices::defaultAudioInput(); // Périphérique de sortie par défaut
        outputAudioDevice = QMediaDevices::defaultAudioOutput(); // Périphérique de sortie par défaut
        //inputAudioDevice = inputDevices[inputSelectedDeviceIndex];
        //outputAudioDevice = outputDevices[outputSelectedDeviceIndex];

        qDebug() << "Périphérique de sortie sélectionné : " << outputAudioDevice.description();
        qDebug() << "Périphérique d'entrée :" << inputAudioDevice.description();
        QAudioFormat formatPreferred = inputAudioDevice.preferredFormat();
        qDebug() << "Format préféré en entrée: "
                 << "SampleRate:" << formatPreferred.sampleRate()
                 << " Channels:" << formatPreferred.channelCount()
                 << " SampleFormat:" << formatPreferred.sampleFormat();
        formatPreferred = outputAudioDevice.preferredFormat();
        qDebug() << "Format préféré en sortie: "
                 << "SampleRate:" << formatPreferred.sampleRate()
                 << " Channels:" << formatPreferred.channelCount()
                 << " SampleFormat:" << formatPreferred.sampleFormat();


        // Configuration audio
        QAudioFormat inputFormat;
        inputFormat.setSampleRate(44100);  // Fréquence d'échantillonnage (44,1 kHz)
        inputFormat.setChannelCount(1);    // Mono (1 canal), 2 pour stéréo
        inputFormat.setSampleFormat(QAudioFormat::Int16);
        if (!inputAudioDevice.isFormatSupported(inputFormat)) {
            qWarning() << "Format non supporté par ce périphérique en entrée :"
                       << "SampleRate:" << inputFormat.sampleRate()
                       << "Channels:" << inputFormat.channelCount()
                       << "SampleFormat:" << inputFormat.sampleFormat();
            return;
        }
        // Configuration audio
        QAudioFormat outputFormat;
        outputFormat.setSampleRate(44100);  // Fréquence d'échantillonnage (44,1 kHz)
        outputFormat.setChannelCount(1);    // Mono (1 canal), 2 pour stéréo
        outputFormat.setSampleFormat(QAudioFormat::Int16);
        if (!outputAudioDevice.isFormatSupported(outputFormat)) {
            qWarning() << "Format non supporté par ce périphérique en sortie :"
                       << "SampleRate:" << outputFormat.sampleRate()
                       << "Channels:" << outputFormat.channelCount()
                       << "SampleFormat:" << outputFormat.sampleFormat();
            return;
        }



        audioInput = new QAudioSource(inputAudioDevice,inputFormat);
        audioOutput = new QAudioSink(outputAudioDevice,outputFormat);
        //audioOutput = new QAudioOutput(outputSink);
        if (!audioOutput->volume()) {
            qWarning() << "Le contrôle du volume n'est pas supporté par ce backend audio.";
            return;
        }
        else qDebug() << " Volume : " << audioOutput->volume();
        // Ajuster le volume entre 0.0 et 1.0 (0 est muet, 1 est le volume maximal)
        audioOutput->setVolume(0.7); // Volume à 50%
        qDebug() << " Volume : " << audioOutput->volume();





        // Lire et envoyer en continu
        //connect(&timer, &QTimer::timeout, this, &AudioClient::sendAudio);
        //timer.start(20); // 20ms pour minimiser la latence


        // Utiliser QThread pour la capture audio continue
        //QThread *audioThread = new QThread(this);
        //connect(audioThread, &QThread::started, this, &AudioClient::captureAndSendAudio);
        //audioThread->start();
        // Utilisation d'un QTimer pour éviter la boucle infinie
        //QTimer *sendTimer = new QTimer(this);
        sendTimer.setInterval(5);  // 20ms pour limiter la fréquence d'envoi (envoyer tous les 20ms)
        connect(&sendTimer, &QTimer::timeout, this, &AudioProfMulti::captureAndSendAudio);
        QThread::msleep(2000);
        sendAudio();
        qDebug() << "Top";
    }

    void AudioProfMulti::setServeurParameters(QHostAddress serverAddress, quint16 serverPort)
    {
        this->serverAddress = serverAddress;
        this->serverPort = serverPort;
    }

    AudioProfMulti::~AudioProfMulti()
    {
        audioOutput->stop();
        audioInput->stop();
        inputDevice->close();
        outputDevice->close();
        delete audioInput;
        delete audioOutput;
    }

    void AudioProfMulti::sendAudio()
    {
        outputDevice = audioOutput->start();
        inputDevice = audioInput->start();
        sendTimer.start();
    }

    void AudioProfMulti::captureAndSendAudio()
    {

          // Démarrer la capture audio

          if (audioInput->state() == QAudio::SuspendedState) {
              qDebug() << "Reprise de la lecture audio.";
              audioInput->resume();
          } else if (audioInput->state() != QAudio::ActiveState) {
              qDebug() << "Le périphérique audio n'est pas actif, démarrage.";
              inputDevice = audioInput->start();
          }

        if (!inputDevice) {
            qWarning() << "Impossible de démarrer l'enregistrement audio.";
            return;
        }
        // Assurez-vous que la capture audio est prête avant de démarrer
        if(audioInput->state() != QAudio::IdleState) {
            qWarning() << "La source audio n'est pas prête.";
        }

        //QThread::msleep(0);  // Attendre un peu pour que le buffer se remplisse



        qint16 availableBytes = audioInput->bytesAvailable();
        qDebug() << "Octets disponibles :" << availableBytes;
        if (1){//inputSource->state() == QAudio::ActiveState){
            if (availableBytes >0) {
                QByteArray data = inputDevice->read(availableBytes); // Lire les données capturées

                if (!data.isEmpty()) {
                    qDebug() << "Audio capturé, taille :" << data.size();
                    udpSocket.writeDatagram(data, serverAddress, serverPort);
                    qDebug() << "Audio envoyé, taille :" << data.size();
                } else {
                    qDebug() << "data is empty !.";
                }
            } else {
                qDebug() << "Aucune donnée disponible dans le buffer audio.";
            }
        }
        else {
            qDebug() << "Aucune donnée capturée, état :" << audioInput->state();
        }


    }






    // Slot pour gérer le changement d'état de QAudioSource

    void AudioProfMulti::onAudioSourceStateChanged(QAudio::State newState) {
        switch (newState) {
        case QAudio::StoppedState:
            qWarning() << "La capture audio est arrêtée.";
            break;
        case QAudio::IdleState:
            qDebug() << "La capture audio est en mode inactif.";
            break;
        case QAudio::ActiveState:
            qDebug() << "La capture audio est active.";
            break;
        default:
            qWarning() << "État inconnu de la capture audio.";
            break;
        }
    }

