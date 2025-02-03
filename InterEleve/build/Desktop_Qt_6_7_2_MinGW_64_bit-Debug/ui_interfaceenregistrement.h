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
    QPushButton *pushButtonSignet;
    QPushButton *pushButtonFavoris;
    QPushButton *pushButtonSpeak;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonRetourArriere;
    QPushButton *pushButtonPause;
    QPushButton *pushButtonAvancer;
    QPushButton *pushButtonAppelProf;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonRepeter;
    QPushButton *pushButtonRevenirALaPhrasePrecedente;
    QLabel *labelAppelProf;
    QLabel *labelChrono;

    void setupUi(QDialog *InterfaceEnregistrement)
    {
        if (InterfaceEnregistrement->objectName().isEmpty())
            InterfaceEnregistrement->setObjectName("InterfaceEnregistrement");
        InterfaceEnregistrement->resize(800, 480);
        pushButtonSon = new QPushButton(InterfaceEnregistrement);
        pushButtonSon->setObjectName("pushButtonSon");
        pushButtonSon->setGeometry(QRect(10, 340, 130, 130));
        pushButtonSurveiller = new QPushButton(InterfaceEnregistrement);
        pushButtonSurveiller->setObjectName("pushButtonSurveiller");
        pushButtonSurveiller->setGeometry(QRect(20, 240, 110, 90));
        pushButtonSignet = new QPushButton(InterfaceEnregistrement);
        pushButtonSignet->setObjectName("pushButtonSignet");
        pushButtonSignet->setGeometry(QRect(20, 140, 70, 90));
        pushButtonFavoris = new QPushButton(InterfaceEnregistrement);
        pushButtonFavoris->setObjectName("pushButtonFavoris");
        pushButtonFavoris->setGeometry(QRect(20, 40, 70, 90));
        pushButtonSpeak = new QPushButton(InterfaceEnregistrement);
        pushButtonSpeak->setObjectName("pushButtonSpeak");
        pushButtonSpeak->setGeometry(QRect(300, 350, 90, 90));
        pushButtonPlay = new QPushButton(InterfaceEnregistrement);
        pushButtonPlay->setObjectName("pushButtonPlay");
        pushButtonPlay->setGeometry(QRect(420, 350, 90, 90));
        pushButtonRetourArriere = new QPushButton(InterfaceEnregistrement);
        pushButtonRetourArriere->setObjectName("pushButtonRetourArriere");
        pushButtonRetourArriere->setGeometry(QRect(250, 220, 90, 90));
        pushButtonPause = new QPushButton(InterfaceEnregistrement);
        pushButtonPause->setObjectName("pushButtonPause");
        pushButtonPause->setGeometry(QRect(370, 220, 90, 90));
        pushButtonAvancer = new QPushButton(InterfaceEnregistrement);
        pushButtonAvancer->setObjectName("pushButtonAvancer");
        pushButtonAvancer->setGeometry(QRect(490, 220, 90, 90));
        pushButtonAppelProf = new QPushButton(InterfaceEnregistrement);
        pushButtonAppelProf->setObjectName("pushButtonAppelProf");
        pushButtonAppelProf->setGeometry(QRect(700, 20, 70, 90));
        pushButtonClear = new QPushButton(InterfaceEnregistrement);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(700, 140, 70, 70));
        pushButtonRepeter = new QPushButton(InterfaceEnregistrement);
        pushButtonRepeter->setObjectName("pushButtonRepeter");
        pushButtonRepeter->setGeometry(QRect(690, 240, 90, 70));
        pushButtonRevenirALaPhrasePrecedente = new QPushButton(InterfaceEnregistrement);
        pushButtonRevenirALaPhrasePrecedente->setObjectName("pushButtonRevenirALaPhrasePrecedente");
        pushButtonRevenirALaPhrasePrecedente->setGeometry(QRect(690, 320, 90, 70));
        labelAppelProf = new QLabel(InterfaceEnregistrement);
        labelAppelProf->setObjectName("labelAppelProf");
        labelAppelProf->setGeometry(QRect(680, 110, 111, 21));
        labelChrono = new QLabel(InterfaceEnregistrement);
        labelChrono->setObjectName("labelChrono");
        labelChrono->setGeometry(QRect(320, 160, 181, 51));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        labelChrono->setFont(font);
        labelChrono->setAlignment(Qt::AlignCenter);

        retranslateUi(InterfaceEnregistrement);

        QMetaObject::connectSlotsByName(InterfaceEnregistrement);
    } // setupUi

    void retranslateUi(QDialog *InterfaceEnregistrement)
    {
        InterfaceEnregistrement->setWindowTitle(QCoreApplication::translate("InterfaceEnregistrement", "Dialog", nullptr));
        pushButtonSon->setText(QString());
        pushButtonSurveiller->setText(QString());
        pushButtonSignet->setText(QString());
        pushButtonFavoris->setText(QString());
        pushButtonSpeak->setText(QString());
        pushButtonPlay->setText(QString());
        pushButtonRetourArriere->setText(QString());
        pushButtonPause->setText(QString());
        pushButtonAvancer->setText(QString());
        pushButtonAppelProf->setText(QString());
        pushButtonClear->setText(QString());
        pushButtonRepeter->setText(QString());
        pushButtonRevenirALaPhrasePrecedente->setText(QString());
        labelAppelProf->setText(QCoreApplication::translate("InterfaceEnregistrement", "Le prof a \303\251t\303\251 appel\303\251", nullptr));
        labelChrono->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InterfaceEnregistrement: public Ui_InterfaceEnregistrement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEENREGISTREMENT_H
