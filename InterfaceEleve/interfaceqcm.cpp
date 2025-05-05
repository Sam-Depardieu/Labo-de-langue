#include "interfaceqcm.h"
#include "interfaceenregistrement.h"
#include "ui_interfaceqcm.h"

InterfaceQCM::InterfaceQCM(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceQCM)
    //Declaration des Image de base des ronds
    , isButton1Image(true)
    , isButton2Image(true)
    , isButton3Image(true)
    , isButton4Image(true)
{
    ui->setupUi(this);
    setFixedSize(800,480);
    this->setWindowTitle("Page de QCM");
    // Affichage des Images
    setButtonIcons();


    udpSocketConsigne.bind(QHostAddress::Any, consignePort);
    connect(&udpSocketConsigne, &QUdpSocket::readyRead, this, &InterfaceQCM::receiveResponse);
}

InterfaceQCM::~InterfaceQCM()
{
    delete ui;
}

void InterfaceQCM::setButtonIcons()
{
    auto setIcon = [&](QPushButton *button, const QString &imagePath) {
        QPixmap image(imagePath);
        if (image.isNull()) {
            qWarning() << "Erreur : image non trouvée !";
        } else {
            QIcon icon(image);
            button->setIcon(icon);
            button->setIconSize(button->size());
        }
    };

    setIcon(ui->pushButtonEffacerReponse, ":/images/Effacer");
    setIcon(ui->pushButtonQuestionSuivante, ":/images/Avancer");
    setIcon(ui->pushButtonQuestionPrecedente, ":/images/RevenirArriere");
    setIcon(ui->pushButton4, ":/images/4");
    setIcon(ui->pushButton3, ":/images/3");
    setIcon(ui->pushButton2, ":/images/2");
    setIcon(ui->pushButton1, ":/images/1");
}

void InterfaceQCM::on_pushButton1_clicked()
{
    if (isButton1Image) {
        QPixmap image1(":/images/1Selec");
        if (image1.isNull()) {
            qWarning() << "Erreur : image non trouvée !";
        } else {
            QIcon icone(image1);
            ui->pushButton1->setIcon(icone);
            ui->pushButton1->setIconSize(ui->pushButton1->size());
            qDebug() << "Image 2Selec chargée";
        }
    } else {
        QPixmap Image(":/images/1");
        if (Image.isNull()) {
            qWarning() << "Erreur : image de base non trouvée !";
        } else {
            QIcon icone(Image);
            ui->pushButton1->setIcon(icone);
            ui->pushButton1->setIconSize(ui->pushButton1->size());
            qDebug() << "Image 1 de base chargée";
        }
    }
    isButton1Image = !isButton1Image;
}


void InterfaceQCM::on_pushButton2_clicked()
{
    if (isButton2Image) {
        QPixmap image1(":/images/2Selec");
        if (image1.isNull()) {
            qWarning() << "Erreur : image non trouvée !";
        } else {
            QIcon icone(image1);
            ui->pushButton2->setIcon(icone);
            ui->pushButton2->setIconSize(ui->pushButton2->size());
            qDebug() << "Image 2Selec chargée";
        }
    } else {
        QPixmap Image(":/images/2");
        if (Image.isNull()) {
            qWarning() << "Erreur : image de base non trouvée !";
        } else {
            QIcon icone(Image);
            ui->pushButton2->setIcon(icone);
            ui->pushButton2->setIconSize(ui->pushButton2->size());
            qDebug() << "Image 2 de base chargée";
        }
    }
    isButton2Image = !isButton2Image;
}


void InterfaceQCM::on_pushButton3_clicked()
{
    if (isButton3Image) {
        QPixmap image1(":/images/3Selec");
        if (image1.isNull()) {
            qWarning() << "Erreur : image non trouvée !";
        } else {
            QIcon icone(image1);
            ui->pushButton3->setIcon(icone);
            ui->pushButton3->setIconSize(ui->pushButton3->size());
            qDebug() << "Image 3Selec chargée";
        }
    } else {
        QPixmap Image(":/images/3");
        if (Image.isNull()) {
            qWarning() << "Erreur : image de base non trouvée !";
        } else {
            QIcon icone(Image);
            ui->pushButton3->setIcon(icone);
            ui->pushButton3->setIconSize(ui->pushButton3->size());
            qDebug() << "Image 3 de base chargée";
        }
    }
    isButton3Image = !isButton3Image;
}


void InterfaceQCM::on_pushButton4_clicked()
{
    if (isButton4Image) {
        QPixmap image1(":/images/4Selec");
        if (image1.isNull()) {
            qWarning() << "Erreur : image non trouvée !";
        } else {
            QIcon icone(image1);
            ui->pushButton4->setIcon(icone);
            ui->pushButton4->setIconSize(ui->pushButton4->size());
            qDebug() << "Image 4Selec chargée";
        }
    } else {
        QPixmap Image(":/images/4");
        if (Image.isNull()) {
            qWarning() << "Erreur : image de base non trouvée !";
        } else {
            QIcon icone(Image);
            ui->pushButton4->setIcon(icone);
            ui->pushButton4->setIconSize(ui->pushButton4->size());
            qDebug() << "Image 4 de base chargée";
        }
    }
    isButton4Image = !isButton4Image;
}

void InterfaceQCM::on_pushButtonEffacerReponse_clicked()
{
    // Change l'image de pushButton1
    QPixmap image1(":/images/1"); // Chemin vers l'image de base pour pushButton1
    if (image1.isNull()) {
        qWarning() << "Erreur : image de base 1 non trouvée !";
    } else {
        QIcon icone(image1);
        ui->pushButton1->setIcon(icone);
        ui->pushButton1->setIconSize(ui->pushButton1->size());
    }

    // Change l'image de pushButton2
    QPixmap image2(":/images/2"); // Chemin vers l'image de base pour pushButton2
    if (image2.isNull()) {
        qWarning() << "Erreur : image de base 2 non trouvée !";
    } else {
        QIcon icone(image2);
        ui->pushButton2->setIcon(icone);
        ui->pushButton2->setIconSize(ui->pushButton2->size());
    }

    // Change l'image de pushButton3
    QPixmap image3(":/images/3"); // Chemin vers l'image de base pour pushButton3
    if (image3.isNull()) {
        qWarning() << "Erreur : image de base 3 non trouvée !";
    } else {
        QIcon icone(image3);
        ui->pushButton3->setIcon(icone);
        ui->pushButton3->setIconSize(ui->pushButton3->size());
    }



    // Change l'image de pushButton4
    QPixmap image4(":/images/4"); // Chemin vers l'image de base pour pushButton4
    if (image4.isNull()) {
        qWarning() << "Erreur : image de base 4 non trouvée !";
    } else {
        QIcon icone(image4);
        ui->pushButton4->setIcon(icone);
        ui->pushButton4->setIconSize(ui->pushButton4->size());
    }
    // Réinitialiser les images des boutons
    setButtonIcons();

    // Réinitialiser les flags
    isButton1Image = true;
    isButton2Image = true;
    isButton3Image = true;
    isButton4Image = true;
}



void InterfaceQCM::on_pushButtonQuestionSuivante_clicked()
{
    // Chemin relatif
    QString fileName = "C:/Users/Quentin/Documents/Projet/responses.txt";
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Erreur : impossible d'ouvrir le fichier pour écrire.";
        return;
    }

    QTextStream out(&file);
    out << "Réponses enregistrées :\n";

    if (!isButton1Image) {
        out << "Réponse 1 sélectionnée\n";
    }
    if (!isButton2Image) {
        out << "Réponse 2 sélectionnée\n";
    }
    if (!isButton3Image) {
        out << "Réponse 3 sélectionnée\n";
    }
    if (!isButton4Image) {
        out << "Réponse 4 sélectionnée\n";
    }

    file.close();
    qDebug() << "Réponses enregistrées dans le fichier :" << file.fileName();
}



void InterfaceQCM::receiveResponse()
{
    while (udpSocketConsigne.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocketConsigne.pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udpSocketConsigne.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString response = QString::fromUtf8(datagram).trimmed();
        qDebug() << "📢 Réponse reçue de" << sender.toString() << ":" << response;

        if (!response.isEmpty()) {
            consigne = response;
        }
    }
}
