#include "interfaceqcm.h"
#include "ui_interfaceqcm.h"

InterfaceQCM::InterfaceQCM(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceQCM)
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
