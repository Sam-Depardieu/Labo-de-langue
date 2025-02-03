/********************************************************************************
** Form generated from reading UI file 'interfaceaudioco.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEAUDIOCO_H
#define UI_INTERFACEAUDIOCO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InterfaceAudioCO
{
public:
    QPushButton *pushButtonEnregistrement;
    QPushButton *pushButtonAppelProf;
    QPushButton *pushButtonSon;
    QLabel *labelAppelProf;

    void setupUi(QDialog *InterfaceAudioCO)
    {
        if (InterfaceAudioCO->objectName().isEmpty())
            InterfaceAudioCO->setObjectName("InterfaceAudioCO");
        InterfaceAudioCO->resize(800, 480);
        pushButtonEnregistrement = new QPushButton(InterfaceAudioCO);
        pushButtonEnregistrement->setObjectName("pushButtonEnregistrement");
        pushButtonEnregistrement->setGeometry(QRect(60, 370, 161, 51));
        pushButtonAppelProf = new QPushButton(InterfaceAudioCO);
        pushButtonAppelProf->setObjectName("pushButtonAppelProf");
        pushButtonAppelProf->setEnabled(true);
        pushButtonAppelProf->setGeometry(QRect(340, 20, 90, 130));
        pushButtonAppelProf->setIconSize(QSize(32, 32));
        pushButtonSon = new QPushButton(InterfaceAudioCO);
        pushButtonSon->setObjectName("pushButtonSon");
        pushButtonSon->setEnabled(true);
        pushButtonSon->setGeometry(QRect(320, 180, 130, 130));
        pushButtonSon->setIconSize(QSize(32, 32));
        labelAppelProf = new QLabel(InterfaceAudioCO);
        labelAppelProf->setObjectName("labelAppelProf");
        labelAppelProf->setEnabled(true);
        labelAppelProf->setGeometry(QRect(330, 160, 111, 16));

        retranslateUi(InterfaceAudioCO);

        QMetaObject::connectSlotsByName(InterfaceAudioCO);
    } // setupUi

    void retranslateUi(QDialog *InterfaceAudioCO)
    {
        InterfaceAudioCO->setWindowTitle(QCoreApplication::translate("InterfaceAudioCO", "Dialog", nullptr));
        pushButtonEnregistrement->setText(QCoreApplication::translate("InterfaceAudioCO", "Interface Enregistrement", nullptr));
        pushButtonAppelProf->setText(QString());
        pushButtonSon->setText(QString());
        labelAppelProf->setText(QCoreApplication::translate("InterfaceAudioCO", "Le prof a \303\251t\303\251 appel\303\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfaceAudioCO: public Ui_InterfaceAudioCO {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEAUDIOCO_H
