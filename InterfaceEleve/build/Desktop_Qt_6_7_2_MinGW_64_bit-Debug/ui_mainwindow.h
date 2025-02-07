/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonConnexion;
    QPushButton *pushButton_2;
    QPushButton *pushButtonEnregistrement;
    QPushButton *pushButton;
    QPushButton *pushButtonInterfaceQCM;
    QPushButton *pushButtonInterfaceAudio;
    QPushButton *pushButtonInterfaceVideo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 480);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButtonConnexion = new QPushButton(centralwidget);
        pushButtonConnexion->setObjectName("pushButtonConnexion");
        pushButtonConnexion->setGeometry(QRect(370, 200, 80, 25));
        QFont font;
        font.setBold(false);
        pushButtonConnexion->setFont(font);
        pushButtonConnexion->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        pushButtonConnexion->setStyleSheet(QString::fromUtf8("Black"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(0, 400, 801, 81));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */\n"
"}"));
        pushButtonEnregistrement = new QPushButton(centralwidget);
        pushButtonEnregistrement->setObjectName("pushButtonEnregistrement");
        pushButtonEnregistrement->setGeometry(QRect(10, 400, 161, 51));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 0, 800, 80));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */\n"
"}"));
        pushButtonInterfaceQCM = new QPushButton(centralwidget);
        pushButtonInterfaceQCM->setObjectName("pushButtonInterfaceQCM");
        pushButtonInterfaceQCM->setGeometry(QRect(180, 400, 161, 51));
        pushButtonInterfaceAudio = new QPushButton(centralwidget);
        pushButtonInterfaceAudio->setObjectName("pushButtonInterfaceAudio");
        pushButtonInterfaceAudio->setGeometry(QRect(350, 400, 161, 51));
        pushButtonInterfaceVideo = new QPushButton(centralwidget);
        pushButtonInterfaceVideo->setObjectName("pushButtonInterfaceVideo");
        pushButtonInterfaceVideo->setGeometry(QRect(520, 400, 161, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonConnexion->setText(QCoreApplication::translate("MainWindow", "Connexion", nullptr));
        pushButton_2->setText(QString());
        pushButtonEnregistrement->setText(QCoreApplication::translate("MainWindow", "Interface Enregistrement", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Bienvenue sur l'interface de Connexion", nullptr));
        pushButtonInterfaceQCM->setText(QCoreApplication::translate("MainWindow", "Interface QCM", nullptr));
        pushButtonInterfaceAudio->setText(QCoreApplication::translate("MainWindow", "Interface Audio", nullptr));
        pushButtonInterfaceVideo->setText(QCoreApplication::translate("MainWindow", "Interface Video", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
