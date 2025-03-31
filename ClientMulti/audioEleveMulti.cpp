    #include "audioEleveMulti.h"

    AudioEleveMulti::AudioEleveMulti(const QHostAddress &serverAddr, quint16 port, const QString &group, QObject *parent)
        : QObject(parent), udpSocket(new QUdpSocket(this)), serverAddress(serverAddr), serverPort(port), group(group)
    {

        udpSocket.bind(QHostAddress::AnyIPv4, serverPort, QUdpSocket::ShareAddress);
        udpSocket.joinMulticastGroup(serverAddress);
        connect(&udpSocket, &QUdpSocket::readyRead, this, &AudioEleveMulti::receiveAudio);


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





        // Ajoutez un slot pour gérer les changements d'état
        //connect(inputSource, &QAudioSource::stateChanged, this, &AudioClient::onAudioSourceStateChanged);


        QThread::msleep(2000);
        qDebug() << "Top";
    }


    AudioEleveMulti::~AudioEleveMulti()
    {
        audioOutput->stop();
        audioInput->stop();
        inputDevice->close();
        outputDevice->close();
        delete audioInput;
        delete audioOutput;
    }




    void AudioEleveMulti::receiveAudio() {
        while (udpSocket.hasPendingDatagrams()) {
            QByteArray data;
            data.resize(udpSocket.pendingDatagramSize());
            udpSocket.readDatagram(data.data(), data.size());
            qDebug() << "Paquet audio reçu, taille :" << data.size() << " octets";

            if (!data.isEmpty() && audioOutput) {
                // Vérifier si le périphérique est prêt
                if (audioOutput->state() == QAudio::SuspendedState) {
                    qDebug() << "Reprise de la lecture audio.";
                    audioOutput->resume();
                } else if (audioOutput->state() != QAudio::ActiveState) {
                    qDebug() << "Le périphérique audio n'est pas actif, démarrage.";
                    outputDevice = audioOutput->start();
                }

                // Écriture des données dans le flux audio
                if (outputDevice) {
                    outputDevice->write(data);
                    qDebug() << "Lecture audio en cours...:" + QString::number(data.size());
                } else {
                    qDebug() << "Erreur : Impossible d'écrire dans le périphérique audio.";
                }
            } else {
                qDebug() << "Aucune donnée reçue ou périphérique non initialisé.";
            }
        }
    }



    // Slot pour gérer le changement d'état de QAudioSource

    void AudioEleveMulti::onAudioSourceStateChanged(QAudio::State newState) {
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



