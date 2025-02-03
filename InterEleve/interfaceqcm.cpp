#include "interfaceqcm.h"
#include "ui_interfaceqcm.h"

InterfaceQCM::InterfaceQCM(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceQCM)
    , isButton1BaseImage(true)
    , isButton2BaseImage(true)
    , isButton3BaseImage(true)
    , isButton4BaseImage(true)
{
    ui->setupUi(this);
    this->setWindowTitle("Interface QCM");
    setFixedSize(800,480);

    QPixmap image(":/Image/1"); // Charge l'image
    if (image.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image); // Crée une icône
        ui->pushButton1->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton1->setIconSize(ui->pushButton1->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image2(":/Image/2"); // Charge l'image
    if (image2.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image2); // Crée une icône
        ui->pushButton2->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton2->setIconSize(ui->pushButton2->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image3(":/Image/3"); // Charge l'image
    if (image3.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image3); // Crée une icône
        ui->pushButton3->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton3->setIconSize(ui->pushButton3->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap image4(":/Image/4"); // Charge l'image
    if (image4.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image4); // Crée une icône
        ui->pushButton4->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton4->setIconSize(ui->pushButton4->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imageQuestionPrecedente(":/Image/RevenirArriere"); // Charge l'image
    if (imageQuestionPrecedente.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageQuestionPrecedente); // Crée une icône
        ui->pushButtonQuestionPrecedente->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonQuestionPrecedente->setIconSize(ui->pushButtonQuestionPrecedente->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imageQuestionSuivante(":/Image/Avancer"); // Charge l'image
    if (imageQuestionSuivante.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageQuestionSuivante); // Crée une icône
        ui->pushButtonQuestionSuivante->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonQuestionSuivante->setIconSize(ui->pushButtonQuestionSuivante->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    QPixmap imageEffacerReponse(":/Image/Effacer"); // Charge l'image
    if (imageEffacerReponse.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageEffacerReponse); // Crée une icône
        ui->pushButtonEffacerReponse->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonEffacerReponse->setIconSize(ui->pushButtonEffacerReponse->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
    }
    connect(ui->pushButtonEffacerReponse, &QPushButton::clicked, this, &InterfaceQCM::on_pushButtonEffacerReponse_clicked);

}

InterfaceQCM::~InterfaceQCM()
{
    delete ui;
}

void InterfaceQCM::on_pushButton1_clicked()
{
    if (isButton1BaseImage) {
        QPixmap image1(":/Image/1Selec");
        if (image1.isNull()) {
            qWarning() << "Erreur : image non trouvée !";
        } else {
            QIcon icone(image1);
            ui->pushButton1->setIcon(icone);
            ui->pushButton1->setIconSize(ui->pushButton1->size());
            qDebug() << "Image 2Selec chargée";
        }
    } else {
        QPixmap baseImage(":/Image/1");
        if (baseImage.isNull()) {
            qWarning() << "Erreur : image de base non trouvée !";
        } else {
            QIcon icone(baseImage);
            ui->pushButton1->setIcon(icone);
            ui->pushButton1->setIconSize(ui->pushButton1->size());
            qDebug() << "Image 2 de base chargée";
        }
    }
    isButton1BaseImage = !isButton1BaseImage;
}


void InterfaceQCM::on_pushButton2_clicked()
{
    if (isButton2BaseImage) {
        QPixmap image2(":/Image/2Selec");
        if (image2.isNull()) {
            qWarning() << "Erreur : image non trouvée !";
        } else {
            QIcon icone(image2);
            ui->pushButton2->setIcon(icone);
            ui->pushButton2->setIconSize(ui->pushButton2->size());
            qDebug() << "Image 2Selec chargée";
        }
    } else {
        QPixmap baseImage(":/Image/2");
        if (baseImage.isNull()) {
            qWarning() << "Erreur : image de base non trouvée !";
        } else {
            QIcon icone(baseImage);
            ui->pushButton2->setIcon(icone);
            ui->pushButton2->setIconSize(ui->pushButton2->size());
            qDebug() << "Image 2 de base chargée";
        }
    }
    isButton2BaseImage = !isButton2BaseImage;
}

void InterfaceQCM::on_pushButton3_clicked()
{
    if (isButton3BaseImage) {
        QPixmap image3(":/Image/3Selec");
        if (image3.isNull()) {
            qWarning() << "Erreur : image non trouvée !";
        } else {
            QIcon icone(image3);
            ui->pushButton3->setIcon(icone);
            ui->pushButton3->setIconSize(ui->pushButton3->size());
            qDebug() << "Image 3Selec chargée";
        }
    } else {
        QPixmap baseImage(":/Image/3");
        if (baseImage.isNull()) {
            qWarning() << "Erreur : image de base non trouvée !";
        } else {
            QIcon icone(baseImage);
            ui->pushButton3->setIcon(icone);
            ui->pushButton3->setIconSize(ui->pushButton3->size());
            qDebug() << "Image 3 de base chargée";
        }
    }
    isButton3BaseImage = !isButton3BaseImage;
}



void InterfaceQCM::on_pushButton4_clicked()
{
    if (isButton4BaseImage) {
        QPixmap image4(":/Image/4Selec");
        if (image4.isNull()) {
            qWarning() << "Erreur : image non trouvée !";
        } else {
            QIcon icone(image4);
            ui->pushButton4->setIcon(icone);
            ui->pushButton4->setIconSize(ui->pushButton4->size());
            qDebug() << "Image 3Selec chargée";
        }
    } else {
        QPixmap baseImage(":/Image/4");
        if (baseImage.isNull()) {
            qWarning() << "Erreur : image de base non trouvée !";
        } else {
            QIcon icone(baseImage);
            ui->pushButton4->setIcon(icone);
            ui->pushButton4->setIconSize(ui->pushButton4->size());
            qDebug() << "Image 3 de base chargée";
        }
    }
    isButton4BaseImage = !isButton4BaseImage;
}


void InterfaceQCM::on_pushButtonEffacerReponse_clicked()
{
    // Change l'image de pushButton1
    QPixmap image1(":/Image/1"); // Chemin vers l'image de base pour pushButton1
    if (image1.isNull()) {
        qWarning() << "Erreur : image de base 1 non trouvée !";
    } else {
        QIcon icone(image1);
        ui->pushButton1->setIcon(icone);
        ui->pushButton1->setIconSize(ui->pushButton1->size());
    }

    // Change l'image de pushButton2
    QPixmap image2(":/Image/2"); // Chemin vers l'image de base pour pushButton2
    if (image2.isNull()) {
        qWarning() << "Erreur : image de base 2 non trouvée !";
    } else {
        QIcon icone(image2);
        ui->pushButton2->setIcon(icone);
        ui->pushButton2->setIconSize(ui->pushButton2->size());
    }

    // Change l'image de pushButton3
    QPixmap image3(":/Image/3"); // Chemin vers l'image de base pour pushButton3
    if (image3.isNull()) {
        qWarning() << "Erreur : image de base 3 non trouvée !";
    } else {
        QIcon icone(image3);
        ui->pushButton3->setIcon(icone);
        ui->pushButton3->setIconSize(ui->pushButton3->size());
    }

    // Change l'image de pushButton4
    QPixmap image4(":/Image/4"); // Chemin vers l'image de base pour pushButton4
    if (image4.isNull()) {
        qWarning() << "Erreur : image de base 4 non trouvée !";
    } else {
        QIcon icone(image4);
        ui->pushButton4->setIcon(icone);
        ui->pushButton4->setIconSize(ui->pushButton4->size());
    }}

