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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditAdresseServeur;
    QLineEdit *lineEditPortServeur;
    QPushButton *pushButtonConnexion;
    QLabel *label_4;
    QLineEdit *lineEditGroupe;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(881, 488);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 40, 49, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 80, 181, 41));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(50, 130, 181, 31));
        lineEditAdresseServeur = new QLineEdit(centralwidget);
        lineEditAdresseServeur->setObjectName("lineEditAdresseServeur");
        lineEditAdresseServeur->setGeometry(QRect(220, 85, 201, 31));
        lineEditPortServeur = new QLineEdit(centralwidget);
        lineEditPortServeur->setObjectName("lineEditPortServeur");
        lineEditPortServeur->setGeometry(QRect(220, 130, 201, 31));
        pushButtonConnexion = new QPushButton(centralwidget);
        pushButtonConnexion->setObjectName("pushButtonConnexion");
        pushButtonConnexion->setGeometry(QRect(50, 210, 371, 29));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 170, 181, 31));
        lineEditGroupe = new QLineEdit(centralwidget);
        lineEditGroupe->setObjectName("lineEditGroupe");
        lineEditGroupe->setGeometry(QRect(220, 170, 201, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 881, 25));
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
        label->setText(QCoreApplication::translate("MainWindow", "CLIENT", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "IP ADRESSE SERVEUR :", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "PORT SERVEUR :", nullptr));
        lineEditAdresseServeur->setText(QCoreApplication::translate("MainWindow", "192.168.64.2", nullptr));
        lineEditPortServeur->setText(QCoreApplication::translate("MainWindow", "12345", nullptr));
        pushButtonConnexion->setText(QCoreApplication::translate("MainWindow", "Connexion", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Groupe \303\240 joindre", nullptr));
        lineEditGroupe->setText(QCoreApplication::translate("MainWindow", "groupe1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
