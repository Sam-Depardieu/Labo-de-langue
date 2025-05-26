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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *footer;
    QGraphicsView *bottom;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_Loading;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 480);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        footer = new QGraphicsView(centralwidget);
        footer->setObjectName("footer");
        footer->setGeometry(QRect(0, 400, 800, 80));
        footer->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */"));
        bottom = new QGraphicsView(centralwidget);
        bottom->setObjectName("bottom");
        bottom->setGeometry(QRect(0, 0, 801, 81));
        bottom->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(360, 15, 181, 31));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(280, 70, 320, 90));
        label_Loading = new QLabel(centralwidget);
        label_Loading->setObjectName("label_Loading");
        label_Loading->setGeometry(QRect(325, 160, 150, 150));
        label_Loading->setStyleSheet(QString::fromUtf8("background-color : transparent;\n"
"border:none;\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        bottom->raise();
        footer->raise();
        label->raise();
        label_2->raise();
        label_Loading->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Interface El\303\250ve", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:26pt; font-weight:700;\">Attente professeur</span></p></body></html>", nullptr));
        label_Loading->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
