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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_InterfaceEnregistrement
{
public:
    QPushButton *pushButtonSon;
    QPushButton *pushButtonAvancer;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonAppelProf;
    QPushButton *pushButton_2;
    QLabel *labelChrono;
    QPushButton *pushButtonSpeak;
    QPushButton *pushButton;
    QPushButton *pushButtonPause;
    QLabel *labelAppelProf;
    QPushButton *pushButtonRetourArriere;
    QPushButton *pushButtonEnregistrer;
    QPushButton *pushButtonEnregistrer_2;
    QPushButton *pushButtonEnregistrer_3;
    QPushButton *pushButtonEnregistrer_4;
    QTextEdit *textEditFeedBack;
    QPushButton *pushButtonPlay;
    QTextEdit *textEditConsigne;

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
        pushButtonAvancer = new QPushButton(InterfaceEnregistrement);
        pushButtonAvancer->setObjectName("pushButtonAvancer");
        pushButtonAvancer->setGeometry(QRect(480, 160, 70, 70));
        pushButtonAvancer->setStyleSheet(QString::fromUtf8(""));
        pushButtonClear = new QPushButton(InterfaceEnregistrement);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(610, 405, 70, 70));
        pushButtonClear->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        pushButtonAppelProf = new QPushButton(InterfaceEnregistrement);
        pushButtonAppelProf->setObjectName("pushButtonAppelProf");
        pushButtonAppelProf->setGeometry(QRect(730, 0, 60, 75));
        pushButtonAppelProf->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("call-start")));
        pushButtonAppelProf->setIcon(icon);
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
        labelChrono->setGeometry(QRect(310, 100, 180, 51));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        labelChrono->setFont(font);
        labelChrono->setAlignment(Qt::AlignCenter);
        pushButtonSpeak = new QPushButton(InterfaceEnregistrement);
        pushButtonSpeak->setObjectName("pushButtonSpeak");
        pushButtonSpeak->setGeometry(QRect(370, 270, 70, 70));
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
        labelAppelProf = new QLabel(InterfaceEnregistrement);
        labelAppelProf->setObjectName("labelAppelProf");
        labelAppelProf->setGeometry(QRect(690, 80, 111, 21));
        pushButtonRetourArriere = new QPushButton(InterfaceEnregistrement);
        pushButtonRetourArriere->setObjectName("pushButtonRetourArriere");
        pushButtonRetourArriere->setGeometry(QRect(260, 160, 70, 70));
        pushButtonRetourArriere->setStyleSheet(QString::fromUtf8(""));
        pushButtonEnregistrer = new QPushButton(InterfaceEnregistrement);
        pushButtonEnregistrer->setObjectName("pushButtonEnregistrer");
        pushButtonEnregistrer->setGeometry(QRect(500, 405, 70, 70));
        pushButtonEnregistrer->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        pushButtonEnregistrer_2 = new QPushButton(InterfaceEnregistrement);
        pushButtonEnregistrer_2->setObjectName("pushButtonEnregistrer_2");
        pushButtonEnregistrer_2->setGeometry(QRect(550, 450, 70, 70));
        pushButtonEnregistrer_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        pushButtonEnregistrer_3 = new QPushButton(InterfaceEnregistrement);
        pushButtonEnregistrer_3->setObjectName("pushButtonEnregistrer_3");
        pushButtonEnregistrer_3->setGeometry(QRect(480, 450, 70, 70));
        pushButtonEnregistrer_3->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        pushButtonEnregistrer_4 = new QPushButton(InterfaceEnregistrement);
        pushButtonEnregistrer_4->setObjectName("pushButtonEnregistrer_4");
        pushButtonEnregistrer_4->setGeometry(QRect(350, 405, 70, 70));
        pushButtonEnregistrer_4->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        textEditFeedBack = new QTextEdit(InterfaceEnregistrement);
        textEditFeedBack->setObjectName("textEditFeedBack");
        textEditFeedBack->setGeometry(QRect(0, 80, 151, 321));
        pushButtonPlay = new QPushButton(InterfaceEnregistrement);
        pushButtonPlay->setObjectName("pushButtonPlay");
        pushButtonPlay->setGeometry(QRect(370, 160, 70, 70));
        pushButtonPlay->setStyleSheet(QString::fromUtf8(""));
        textEditConsigne = new QTextEdit(InterfaceEnregistrement);
        textEditConsigne->setObjectName("textEditConsigne");
        textEditConsigne->setGeometry(QRect(640, 110, 151, 161));
        pushButton_2->raise();
        pushButton->raise();
        pushButtonSon->raise();
        pushButtonAvancer->raise();
        pushButtonClear->raise();
        labelChrono->raise();
        pushButtonSpeak->raise();
        pushButtonPause->raise();
        labelAppelProf->raise();
        pushButtonRetourArriere->raise();
        pushButtonAppelProf->raise();
        pushButtonEnregistrer->raise();
        pushButtonEnregistrer_2->raise();
        pushButtonEnregistrer_3->raise();
        pushButtonEnregistrer_4->raise();
        textEditFeedBack->raise();
        pushButtonPlay->raise();
        textEditConsigne->raise();

        retranslateUi(InterfaceEnregistrement);

        QMetaObject::connectSlotsByName(InterfaceEnregistrement);
    } // setupUi

    void retranslateUi(QDialog *InterfaceEnregistrement)
    {
        InterfaceEnregistrement->setWindowTitle(QCoreApplication::translate("InterfaceEnregistrement", "Dialog", nullptr));
        pushButtonSon->setText(QString());
        pushButtonAvancer->setText(QString());
        pushButtonClear->setText(QString());
        pushButtonAppelProf->setText(QString());
        pushButton_2->setText(QString());
        labelChrono->setText(QString());
        pushButtonSpeak->setText(QString());
        pushButton->setText(QCoreApplication::translate("InterfaceEnregistrement", "Bienvenue sur l'interface pour un Enregistrement", nullptr));
        pushButtonPause->setText(QString());
        labelAppelProf->setText(QCoreApplication::translate("InterfaceEnregistrement", "Le prof a \303\251t\303\251 appel\303\251", nullptr));
        pushButtonRetourArriere->setText(QString());
        pushButtonEnregistrer->setText(QString());
        pushButtonEnregistrer_2->setText(QString());
        pushButtonEnregistrer_3->setText(QString());
        pushButtonEnregistrer_4->setText(QString());
        textEditFeedBack->setHtml(QCoreApplication::translate("InterfaceEnregistrement", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700; text-decoration: underline;\">Feedback</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">--------------------------</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px"
                        "; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:700;\"><br /></p></body></html>", nullptr));
        pushButtonPlay->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InterfaceEnregistrement: public Ui_InterfaceEnregistrement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEENREGISTREMENT_H
