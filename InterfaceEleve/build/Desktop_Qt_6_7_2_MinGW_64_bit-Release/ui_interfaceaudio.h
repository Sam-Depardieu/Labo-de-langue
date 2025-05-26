/********************************************************************************
** Form generated from reading UI file 'interfaceaudio.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEAUDIO_H
#define UI_INTERFACEAUDIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_InterfaceAudio
{
public:
    QPushButton *pushButton_Play;
    QPushButton *pushButton_Avant;
    QPushButton *pushButton_Apres;
    QPushButton *pushButton_Pause;
    QPushButton *pushButton_SelectAudio;
    QSlider *horizontalSlider;
    QPushButton *pushButtonReset;
    QPushButton *pushButton_Son;
    QGraphicsView *graphicsView;
    QSlider *verticalSlider_sonVideo;
    QLabel *chronoLabel;
    QLabel *label_3;

    void setupUi(QDialog *InterfaceAudio)
    {
        if (InterfaceAudio->objectName().isEmpty())
            InterfaceAudio->setObjectName("InterfaceAudio");
        InterfaceAudio->resize(800, 480);
        pushButton_Play = new QPushButton(InterfaceAudio);
        pushButton_Play->setObjectName("pushButton_Play");
        pushButton_Play->setGeometry(QRect(420, 430, 45, 45));
        pushButton_Avant = new QPushButton(InterfaceAudio);
        pushButton_Avant->setObjectName("pushButton_Avant");
        pushButton_Avant->setGeometry(QRect(310, 430, 45, 45));
        pushButton_Apres = new QPushButton(InterfaceAudio);
        pushButton_Apres->setObjectName("pushButton_Apres");
        pushButton_Apres->setGeometry(QRect(520, 430, 45, 45));
        pushButton_Pause = new QPushButton(InterfaceAudio);
        pushButton_Pause->setObjectName("pushButton_Pause");
        pushButton_Pause->setGeometry(QRect(420, 430, 45, 45));
        pushButton_SelectAudio = new QPushButton(InterfaceAudio);
        pushButton_SelectAudio->setObjectName("pushButton_SelectAudio");
        pushButton_SelectAudio->setGeometry(QRect(0, 0, 111, 24));
        horizontalSlider = new QSlider(InterfaceAudio);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(10, 400, 781, 20));
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);
        pushButtonReset = new QPushButton(InterfaceAudio);
        pushButtonReset->setObjectName("pushButtonReset");
        pushButtonReset->setGeometry(QRect(10, 430, 45, 45));
        pushButton_Son = new QPushButton(InterfaceAudio);
        pushButton_Son->setObjectName("pushButton_Son");
        pushButton_Son->setGeometry(QRect(740, 430, 45, 45));
        graphicsView = new QGraphicsView(InterfaceAudio);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(10, 30, 781, 361));
        verticalSlider_sonVideo = new QSlider(InterfaceAudio);
        verticalSlider_sonVideo->setObjectName("verticalSlider_sonVideo");
        verticalSlider_sonVideo->setGeometry(QRect(760, 240, 16, 160));
        verticalSlider_sonVideo->setOrientation(Qt::Orientation::Vertical);
        chronoLabel = new QLabel(InterfaceAudio);
        chronoLabel->setObjectName("chronoLabel");
        chronoLabel->setGeometry(QRect(110, 430, 111, 45));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setBold(true);
        chronoLabel->setFont(font);
        chronoLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: #0097a7; /* m\303\252me ton bleu-vert que ta barre */\n"
"    color: white;\n"
"    border: 2px solid white;\n"
"    border-radius: 8px;\n"
"    font-family: \"Segoe UI\", \"Arial\", sans-serif;\n"
"    font-weight: bold;\n"
"    font-size: 28px;\n"
"    padding: 5px 15px;\n"
"    qproperty-alignment: 'AlignCenter';\n"
"}\n"
""));
        label_3 = new QLabel(InterfaceAudio);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(-10, 425, 831, 61));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */"));
        label_3->raise();
        pushButton_Play->raise();
        pushButton_Avant->raise();
        pushButton_Apres->raise();
        pushButton_Pause->raise();
        pushButton_SelectAudio->raise();
        horizontalSlider->raise();
        pushButtonReset->raise();
        pushButton_Son->raise();
        graphicsView->raise();
        verticalSlider_sonVideo->raise();
        chronoLabel->raise();

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
        pushButton_SelectAudio->setText(QCoreApplication::translate("InterfaceAudio", "Selectionner Audio", nullptr));
        pushButtonReset->setText(QString());
        pushButton_Son->setText(QString());
        chronoLabel->setText(QCoreApplication::translate("InterfaceAudio", "00:00", nullptr));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InterfaceAudio: public Ui_InterfaceAudio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEAUDIO_H
