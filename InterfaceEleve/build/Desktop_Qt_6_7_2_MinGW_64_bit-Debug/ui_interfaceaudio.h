/********************************************************************************
** Form generated from reading UI file 'interfaceaudio.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEAUDIO_H
#define UI_INTERFACEAUDIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceAudio
{
public:
    QPushButton *pushButton_Play;
    QPushButton *pushButton_Avant;
    QPushButton *pushButton_Apres;
    QPushButton *pushButton_Pause;
    QPushButton *pushButton_2;
    QPushButton *pushButton_SelectAudio;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSlider *horizontalSliderSon;

    void setupUi(QDialog *InterfaceAudio)
    {
        if (InterfaceAudio->objectName().isEmpty())
            InterfaceAudio->setObjectName("InterfaceAudio");
        InterfaceAudio->resize(800, 480);
        pushButton_Play = new QPushButton(InterfaceAudio);
        pushButton_Play->setObjectName("pushButton_Play");
        pushButton_Play->setGeometry(QRect(300, 420, 45, 45));
        pushButton_Avant = new QPushButton(InterfaceAudio);
        pushButton_Avant->setObjectName("pushButton_Avant");
        pushButton_Avant->setGeometry(QRect(240, 420, 45, 45));
        pushButton_Apres = new QPushButton(InterfaceAudio);
        pushButton_Apres->setObjectName("pushButton_Apres");
        pushButton_Apres->setGeometry(QRect(420, 420, 45, 45));
        pushButton_Pause = new QPushButton(InterfaceAudio);
        pushButton_Pause->setObjectName("pushButton_Pause");
        pushButton_Pause->setGeometry(QRect(360, 420, 45, 45));
        pushButton_2 = new QPushButton(InterfaceAudio);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(-10, 390, 811, 90));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */\n"
"}"));
        pushButton_SelectAudio = new QPushButton(InterfaceAudio);
        pushButton_SelectAudio->setObjectName("pushButton_SelectAudio");
        pushButton_SelectAudio->setGeometry(QRect(0, 0, 111, 24));
        horizontalLayoutWidget = new QWidget(InterfaceAudio);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(9, 30, 781, 341));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSliderSon = new QSlider(InterfaceAudio);
        horizontalSliderSon->setObjectName("horizontalSliderSon");
        horizontalSliderSon->setGeometry(QRect(570, 430, 160, 16));
        horizontalSliderSon->setOrientation(Qt::Horizontal);
        pushButton_2->raise();
        pushButton_Play->raise();
        pushButton_Avant->raise();
        pushButton_Apres->raise();
        pushButton_Pause->raise();
        pushButton_SelectAudio->raise();
        horizontalLayoutWidget->raise();
        horizontalSliderSon->raise();

        retranslateUi(InterfaceAudio);

        QMetaObject::connectSlotsByName(InterfaceAudio);
    } // setupUi

    void retranslateUi(QDialog *InterfaceAudio)
    {
        InterfaceAudio->setWindowTitle(QCoreApplication::translate("InterfaceAudio", "Dialog", nullptr));
        pushButton_Play->setText(QString());
        pushButton_Avant->setText(QString());
        pushButton_Apres->setText(QString());
        pushButton_Pause->setText(QString());
        pushButton_2->setText(QString());
        pushButton_SelectAudio->setText(QCoreApplication::translate("InterfaceAudio", "Selectionner Audio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfaceAudio: public Ui_InterfaceAudio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEAUDIO_H
