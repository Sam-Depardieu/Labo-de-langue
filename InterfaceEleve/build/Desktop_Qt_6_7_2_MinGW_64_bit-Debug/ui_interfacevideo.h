/********************************************************************************
** Form generated from reading UI file 'interfacevideo.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEVIDEO_H
#define UI_INTERFACEVIDEO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceVideo
{
public:
    QPushButton *pushButton_Apres10;
    QPushButton *pushButton_Play;
    QPushButton *pushButton_Pause;
    QPushButton *pushButton_Avant10;
    QPushButton *pushButton_SelectVideo;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSlider *horizontalSlider_sonVideo;
    QPushButton *pushButton_3;

    void setupUi(QDialog *InterfaceVideo)
    {
        if (InterfaceVideo->objectName().isEmpty())
            InterfaceVideo->setObjectName("InterfaceVideo");
        InterfaceVideo->resize(800, 480);
        pushButton_Apres10 = new QPushButton(InterfaceVideo);
        pushButton_Apres10->setObjectName("pushButton_Apres10");
        pushButton_Apres10->setGeometry(QRect(460, 430, 45, 45));
        pushButton_Play = new QPushButton(InterfaceVideo);
        pushButton_Play->setObjectName("pushButton_Play");
        pushButton_Play->setGeometry(QRect(300, 430, 45, 45));
        pushButton_Pause = new QPushButton(InterfaceVideo);
        pushButton_Pause->setObjectName("pushButton_Pause");
        pushButton_Pause->setGeometry(QRect(380, 430, 45, 45));
        pushButton_Avant10 = new QPushButton(InterfaceVideo);
        pushButton_Avant10->setObjectName("pushButton_Avant10");
        pushButton_Avant10->setGeometry(QRect(220, 430, 45, 45));
        pushButton_SelectVideo = new QPushButton(InterfaceVideo);
        pushButton_SelectVideo->setObjectName("pushButton_SelectVideo");
        pushButton_SelectVideo->setGeometry(QRect(0, 0, 101, 21));
        verticalLayoutWidget = new QWidget(InterfaceVideo);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 20, 781, 391));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSlider_sonVideo = new QSlider(InterfaceVideo);
        horizontalSlider_sonVideo->setObjectName("horizontalSlider_sonVideo");
        horizontalSlider_sonVideo->setGeometry(QRect(610, 450, 160, 16));
        horizontalSlider_sonVideo->setOrientation(Qt::Horizontal);
        pushButton_3 = new QPushButton(InterfaceVideo);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(0, 420, 801, 61));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */\n"
"}"));
        pushButton_3->raise();
        pushButton_Apres10->raise();
        pushButton_Play->raise();
        pushButton_Pause->raise();
        pushButton_Avant10->raise();
        pushButton_SelectVideo->raise();
        verticalLayoutWidget->raise();
        horizontalSlider_sonVideo->raise();

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
        pushButton_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InterfaceVideo: public Ui_InterfaceVideo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEVIDEO_H
