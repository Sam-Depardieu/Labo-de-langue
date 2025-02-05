#include "interfaceqcm.h"
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



    QPixmap image(":/images/1"); // Charge l'image
    if (image.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image); // Crée une icône
        ui->pushButton1->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton1->setIconSize(ui->pushButton1->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
        ui->pushButton1->setStyleSheet("QPushButton { text-align: center; padding: 0px; }");
    }

    QPixmap image2(":/images/2"); // Charge l'image
    if (image2.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image2); // Crée une icône
        ui->pushButton2->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton2->setIconSize(ui->pushButton2->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
        ui->pushButton2->setStyleSheet("QPushButton { text-align: center; padding: 0px; }");
    }

    QPixmap image3(":/images/3"); // Charge l'image
    if (image3.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image3); // Crée une icône
        ui->pushButton3->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton3->setIconSize(ui->pushButton3->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
        ui->pushButton3->setStyleSheet("QPushButton { text-align: center; padding: 0px; }");
    }

    QPixmap image4(":/images/4"); // Charge l'image
    if (image4.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(image4); // Crée une icône
        ui->pushButton4->setIcon(icone); // Définit l'icône du bouton
        ui->pushButton4->setIconSize(ui->pushButton4->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
        ui->pushButton4->setStyleSheet("QPushButton { text-align: center; padding: 0px; }");
    }

    QPixmap imageQuestionPrecedente(":/images/RevenirArriere"); // Charge l'image
    if (imageQuestionPrecedente.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageQuestionPrecedente); // Crée une icône
        ui->pushButtonQuestionPrecedente->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonQuestionPrecedente->setIconSize(ui->pushButtonQuestionPrecedente->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
        ui->pushButtonQuestionPrecedente->setStyleSheet("QPushButton { text-align: center; padding: 0px; }");
    }

    QPixmap imageQuestionSuivante(":/images/Avancer"); // Charge l'image
    if (imageQuestionSuivante.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageQuestionSuivante); // Crée une icône
        ui->pushButtonQuestionSuivante->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonQuestionSuivante->setIconSize(ui->pushButtonQuestionSuivante->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
        ui->pushButtonQuestionSuivante->setStyleSheet("QPushButton { text-align: center; padding: 0px; }");
    }

    QPixmap imageEffacerReponse(":/images/Effacer"); // Charge l'image
    if (imageEffacerReponse.isNull()) {
        qWarning() << "Erreur : image non trouvée !";
    } else {
        QIcon icone(imageEffacerReponse); // Crée une icône
        ui->pushButtonEffacerReponse->setIcon(icone); // Définit l'icône du bouton
        ui->pushButtonEffacerReponse->setIconSize(ui->pushButtonEffacerReponse->size()); // Ajuste la taille de l'icône pour qu'elle corresponde à la taille du bouton
        ui->pushButtonEffacerReponse->setStyleSheet("QPushButton { text-align: center; padding: 0px; }");
    }


}

InterfaceQCM::~InterfaceQCM()
{
    delete ui;
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
    }}
