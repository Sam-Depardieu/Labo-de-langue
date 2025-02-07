/********************************************************************************
** Form generated from reading UI file 'interfaceenregistrement.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEENREGISTREMENT_H
#define UI_INTERFACEENREGISTREMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InterfaceEnregistrement
{
public:
    QPushButton *pushButtonSon;
    QPushButton *pushButtonSurveiller;
    QPushButton *pushButtonAvancer;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonAppelProf;
    QPushButton *pushButton_2;
    QLabel *labelChrono;
    QPushButton *pushButtonSpeak;
    QPushButton *pushButton;
    QPushButton *pushButtonPause;
    QPushButton *pushButtonRepeter;
    QPushButton *pushButtonSignet;
    QLabel *labelAppelProf;
    QPushButton *pushButtonFavoris;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonRevenirALaPhrasePrecedente;
    QPushButton *pushButtonRetourArriere;

    void setupUi(QDialog *InterfaceEnregistrement)
    {
        if (InterfaceEnregistrement->objectName().isEmpty())
            InterfaceEnregistrement->setObjectName("InterfaceEnregistrement");
        InterfaceEnregistrement->resize(800, 480);
        pushButtonSon = new QPushButton(InterfaceEnregistrement);
        pushButtonSon->setObjectName("pushButtonSon");
        pushButtonSon->setGeometry(QRect(20, 400, 80, 80));
        pushButtonSon->setAutoFillBackground(false);
        pushButtonSon->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        pushButtonSurveiller = new QPushButton(InterfaceEnregistrement);
        pushButtonSurveiller->setObjectName("pushButtonSurveiller");
        pushButtonSurveiller->setGeometry(QRect(710, 410, 80, 60));
        pushButtonSurveiller->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        pushButtonAvancer = new QPushButton(InterfaceEnregistrement);
        pushButtonAvancer->setObjectName("pushButtonAvancer");
        pushButtonAvancer->setGeometry(QRect(470, 160, 70, 70));
        pushButtonAvancer->setStyleSheet(QString::fromUtf8(""));
        pushButtonClear = new QPushButton(InterfaceEnregistrement);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(630, 405, 70, 70));
        pushButtonClear->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        pushButtonAppelProf = new QPushButton(InterfaceEnregistrement);
        pushButtonAppelProf->setObjectName("pushButtonAppelProf");
        pushButtonAppelProf->setGeometry(QRect(710, 3, 60, 75));
        pushButtonAppelProf->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        pushButton_2 = new QPushButton(InterfaceEnregistrement);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(0, 400, 801, 81));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */\n"
"}"));
        labelChrono = new QLabel(InterfaceEnregistrement);
        labelChrono->setObjectName("labelChrono");
        labelChrono->setGeometry(QRect(310, 100, 181, 51));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        labelChrono->setFont(font);
        labelChrono->setAlignment(Qt::AlignCenter);
        pushButtonSpeak = new QPushButton(InterfaceEnregistrement);
        pushButtonSpeak->setObjectName("pushButtonSpeak");
        pushButtonSpeak->setGeometry(QRect(320, 290, 70, 70));
        pushButtonSpeak->setStyleSheet(QString::fromUtf8(""));
        pushButton = new QPushButton(InterfaceEnregistrement);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 0, 800, 80));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */\n"
"}"));
        pushButtonPause = new QPushButton(InterfaceEnregistrement);
        pushButtonPause->setObjectName("pushButtonPause");
        pushButtonPause->setGeometry(QRect(370, 160, 70, 70));
        pushButtonPause->setStyleSheet(QString::fromUtf8(""));
        pushButtonRepeter = new QPushButton(InterfaceEnregistrement);
        pushButtonRepeter->setObjectName("pushButtonRepeter");
        pushButtonRepeter->setGeometry(QRect(520, 405, 90, 70));
        pushButtonRepeter->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        pushButtonSignet = new QPushButton(InterfaceEnregistrement);
        pushButtonSignet->setObjectName("pushButtonSignet");
        pushButtonSignet->setGeometry(QRect(130, 400, 60, 80));
        pushButtonSignet->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        labelAppelProf = new QLabel(InterfaceEnregistrement);
        labelAppelProf->setObjectName("labelAppelProf");
        labelAppelProf->setGeometry(QRect(690, 80, 111, 21));
        pushButtonFavoris = new QPushButton(InterfaceEnregistrement);
        pushButtonFavoris->setObjectName("pushButtonFavoris");
        pushButtonFavoris->setGeometry(QRect(220, 400, 80, 80));
        pushButtonFavoris->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        pushButtonPlay = new QPushButton(InterfaceEnregistrement);
        pushButtonPlay->setObjectName("pushButtonPlay");
        pushButtonPlay->setGeometry(QRect(420, 290, 70, 70));
        pushButtonPlay->setStyleSheet(QString::fromUtf8(""));
        pushButtonRevenirALaPhrasePrecedente = new QPushButton(InterfaceEnregistrement);
        pushButtonRevenirALaPhrasePrecedente->setObjectName("pushButtonRevenirALaPhrasePrecedente");
        pushButtonRevenirALaPhrasePrecedente->setGeometry(QRect(420, 405, 90, 70));
        pushButtonRevenirALaPhrasePrecedente->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        pushButtonRetourArriere = new QPushButton(InterfaceEnregistrement);
        pushButtonRetourArriere->setObjectName("pushButtonRetourArriere");
        pushButtonRetourArriere->setGeometry(QRect(270, 160, 70, 70));
        pushButtonRetourArriere->setStyleSheet(QString::fromUtf8(""));
        pushButton->raise();
        pushButton_2->raise();
        pushButtonSon->raise();
        pushButtonSurveiller->raise();
        pushButtonAvancer->raise();
        pushButtonClear->raise();
        pushButtonAppelProf->raise();
        labelChrono->raise();
        pushButtonSpeak->raise();
        pushButtonPause->raise();
        pushButtonRepeter->raise();
        pushButtonSignet->raise();
        labelAppelProf->raise();
        pushButtonFavoris->raise();
        pushButtonPlay->raise();
        pushButtonRevenirALaPhrasePrecedente->raise();
        pushButtonRetourArriere->raise();

        retranslateUi(InterfaceEnregistrement);

        QMetaObject::connectSlotsByName(InterfaceEnregistrement);
    } // setupUi

    void retranslateUi(QDialog *InterfaceEnregistrement)
    {
        InterfaceEnregistrement->setWindowTitle(QCoreApplication::translate("InterfaceEnregistrement", "Dialog", nullptr));
        pushButtonSon->setText(QString());
        pushButtonSurveiller->setText(QString());
        pushButtonAvancer->setText(QString());
        pushButtonClear->setText(QString());
        pushButtonAppelProf->setText(QString());
        pushButton_2->setText(QString());
        labelChrono->setText(QString());
        pushButtonSpeak->setText(QString());
        pushButton->setText(QCoreApplication::translate("InterfaceEnregistrement", "Bienvenue sur l'interface pour un Enregistrement", nullptr));
        pushButtonPause->setText(QString());
        pushButtonRepeter->setText(QString());
        pushButtonSignet->setText(QString());
        labelAppelProf->setText(QCoreApplication::translate("InterfaceEnregistrement", "Le prof a \303\251t\303\251 appel\303\251", nullptr));
        pushButtonFavoris->setText(QString());
        pushButtonPlay->setText(QString());
        pushButtonRevenirALaPhrasePrecedente->setText(QString());
        pushButtonRetourArriere->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InterfaceEnregistrement: public Ui_InterfaceEnregistrement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEENREGISTREMENT_H
