/********************************************************************************
** Form generated from reading UI file 'interfacevideo.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEVIDEO_H
#define UI_INTERFACEVIDEO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_InterfaceVideo
{
public:
    QPushButton *pushButton_Apres10;
    QPushButton *pushButton_Play;
    QPushButton *pushButton_Pause;
    QPushButton *pushButton_Avant10;
    QPushButton *pushButton_SelectVideo;
    QSlider *horizontalSlider;
    QPushButton *pushButtonReset;
    QLabel *chronoLabel;
    QSlider *verticalSlider_sonVideo;
    QPushButton *pushButton_Son;
    QGraphicsView *graphicsView;
    QLabel *label_3;

    void setupUi(QDialog *InterfaceVideo)
    {
        if (InterfaceVideo->objectName().isEmpty())
            InterfaceVideo->setObjectName("InterfaceVideo");
        InterfaceVideo->resize(800, 480);
        pushButton_Apres10 = new QPushButton(InterfaceVideo);
        pushButton_Apres10->setObjectName("pushButton_Apres10");
        pushButton_Apres10->setGeometry(QRect(500, 430, 45, 45));
        pushButton_Play = new QPushButton(InterfaceVideo);
        pushButton_Play->setObjectName("pushButton_Play");
        pushButton_Play->setGeometry(QRect(400, 430, 45, 45));
        pushButton_Pause = new QPushButton(InterfaceVideo);
        pushButton_Pause->setObjectName("pushButton_Pause");
        pushButton_Pause->setGeometry(QRect(400, 430, 45, 45));
        pushButton_Avant10 = new QPushButton(InterfaceVideo);
        pushButton_Avant10->setObjectName("pushButton_Avant10");
        pushButton_Avant10->setGeometry(QRect(300, 430, 45, 45));
        pushButton_SelectVideo = new QPushButton(InterfaceVideo);
        pushButton_SelectVideo->setObjectName("pushButton_SelectVideo");
        pushButton_SelectVideo->setGeometry(QRect(10, 0, 101, 21));
        horizontalSlider = new QSlider(InterfaceVideo);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(10, 410, 763, 15));
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);
        pushButtonReset = new QPushButton(InterfaceVideo);
        pushButtonReset->setObjectName("pushButtonReset");
        pushButtonReset->setGeometry(QRect(20, 430, 45, 45));
        chronoLabel = new QLabel(InterfaceVideo);
        chronoLabel->setObjectName("chronoLabel");
        chronoLabel->setGeometry(QRect(120, 430, 111, 45));
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
        verticalSlider_sonVideo = new QSlider(InterfaceVideo);
        verticalSlider_sonVideo->setObjectName("verticalSlider_sonVideo");
        verticalSlider_sonVideo->setGeometry(QRect(760, 260, 16, 160));
        verticalSlider_sonVideo->setOrientation(Qt::Orientation::Vertical);
        pushButton_Son = new QPushButton(InterfaceVideo);
        pushButton_Son->setObjectName("pushButton_Son");
        pushButton_Son->setGeometry(QRect(745, 430, 45, 45));
        graphicsView = new QGraphicsView(InterfaceVideo);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(10, 20, 781, 391));
        label_3 = new QLabel(InterfaceVideo);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 425, 800, 55));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */"));
        label_3->raise();
        graphicsView->raise();
        pushButton_Apres10->raise();
        pushButton_Play->raise();
        pushButton_Pause->raise();
        pushButton_Avant10->raise();
        pushButton_SelectVideo->raise();
        horizontalSlider->raise();
        pushButtonReset->raise();
        chronoLabel->raise();
        pushButton_Son->raise();
        verticalSlider_sonVideo->raise();

        retranslateUi(InterfaceVideo);

        QMetaObject::connectSlotsByName(InterfaceVideo);
    } // setupUi

    void retranslateUi(QDialog *InterfaceVideo)
    {
        InterfaceVideo->setWindowTitle(QCoreApplication::translate("InterfaceVideo", "Dialog", nullptr));
        pushButton_Apres10->setText(QString());
        pushButton_Play->setText(QString());
        pushButton_Pause->setText(QString());
        pushButton_Avant10->setText(QString());
        pushButton_SelectVideo->setText(QCoreApplication::translate("InterfaceVideo", "Selectionner Video", nullptr));
        pushButtonReset->setText(QString());
        chronoLabel->setText(QCoreApplication::translate("InterfaceVideo", "00:00", nullptr));
        pushButton_Son->setText(QString());
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InterfaceVideo: public Ui_InterfaceVideo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEVIDEO_H
