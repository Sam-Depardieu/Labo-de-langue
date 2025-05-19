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
    QTextEdit *textEditFeedBack;
    QPushButton *pushButtonPlay;
    QTextEdit *textEditConsigne;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *InterfaceEnregistrement)
    {
        if (InterfaceEnregistrement->objectName().isEmpty())
            InterfaceEnregistrement->setObjectName("InterfaceEnregistrement");
        InterfaceEnregistrement->resize(800, 480);
        pushButtonSon = new QPushButton(InterfaceEnregistrement);
        pushButtonSon->setObjectName("pushButtonSon");
        pushButtonSon->setGeometry(QRect(20, 435, 45, 45));
        pushButtonSon->setAutoFillBackground(false);
        pushButtonSon->setStyleSheet(QString::fromUtf8(""));
        pushButtonAvancer = new QPushButton(InterfaceEnregistrement);
        pushButtonAvancer->setObjectName("pushButtonAvancer");
        pushButtonAvancer->setGeometry(QRect(500, 90, 81, 81));
        pushButtonAvancer->setStyleSheet(QString::fromUtf8(""));
        pushButtonClear = new QPushButton(InterfaceEnregistrement);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(610, 435, 45, 45));
        pushButtonClear->setStyleSheet(QString::fromUtf8(""));
        pushButtonAppelProf = new QPushButton(InterfaceEnregistrement);
        pushButtonAppelProf->setObjectName("pushButtonAppelProf");
        pushButtonAppelProf->setGeometry(QRect(740, 5, 45, 45));
        pushButtonAppelProf->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("call-start")));
        pushButtonAppelProf->setIcon(icon);
        pushButton_2 = new QPushButton(InterfaceEnregistrement);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(0, 430, 801, 55));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */\n"
"}"));
        labelChrono = new QLabel(InterfaceEnregistrement);
        labelChrono->setObjectName("labelChrono");
        labelChrono->setGeometry(QRect(280, 340, 221, 61));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        labelChrono->setFont(font);
        labelChrono->setAlignment(Qt::AlignCenter);
        pushButtonSpeak = new QPushButton(InterfaceEnregistrement);
        pushButtonSpeak->setObjectName("pushButtonSpeak");
        pushButtonSpeak->setGeometry(QRect(350, 250, 81, 81));
        pushButtonSpeak->setStyleSheet(QString::fromUtf8(""));
        pushButton = new QPushButton(InterfaceEnregistrement);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 0, 800, 55));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */\n"
"}"));
        pushButtonPause = new QPushButton(InterfaceEnregistrement);
        pushButtonPause->setObjectName("pushButtonPause");
        pushButtonPause->setGeometry(QRect(350, 90, 81, 81));
        pushButtonPause->setStyleSheet(QString::fromUtf8(""));
        labelAppelProf = new QLabel(InterfaceEnregistrement);
        labelAppelProf->setObjectName("labelAppelProf");
        labelAppelProf->setGeometry(QRect(690, 80, 111, 21));
        pushButtonRetourArriere = new QPushButton(InterfaceEnregistrement);
        pushButtonRetourArriere->setObjectName("pushButtonRetourArriere");
        pushButtonRetourArriere->setGeometry(QRect(200, 90, 81, 81));
        pushButtonRetourArriere->setStyleSheet(QString::fromUtf8(""));
        pushButtonEnregistrer = new QPushButton(InterfaceEnregistrement);
        pushButtonEnregistrer->setObjectName("pushButtonEnregistrer");
        pushButtonEnregistrer->setGeometry(QRect(540, 435, 45, 45));
        pushButtonEnregistrer->setStyleSheet(QString::fromUtf8(""));
        textEditFeedBack = new QTextEdit(InterfaceEnregistrement);
        textEditFeedBack->setObjectName("textEditFeedBack");
        textEditFeedBack->setGeometry(QRect(10, 210, 211, 201));
        textEditFeedBack->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background-color: #f5f5f5;\n"
"    border: 2px solid #007a8c;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-size: 14px;\n"
"    font-family: \"Segoe UI\", sans-serif;\n"
"    color: #333;\n"
"}\n"
""));
        pushButtonPlay = new QPushButton(InterfaceEnregistrement);
        pushButtonPlay->setObjectName("pushButtonPlay");
        pushButtonPlay->setGeometry(QRect(350, 90, 81, 81));
        pushButtonPlay->setStyleSheet(QString::fromUtf8(""));
        textEditConsigne = new QTextEdit(InterfaceEnregistrement);
        textEditConsigne->setObjectName("textEditConsigne");
        textEditConsigne->setGeometry(QRect(580, 210, 211, 201));
        textEditConsigne->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background-color: #f5f5f5;\n"
"    border: 2px solid #007a8c;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-size: 14px;\n"
"    font-family: \"Segoe UI\", sans-serif;\n"
"    color: #333;\n"
"}\n"
""));
        label = new QLabel(InterfaceEnregistrement);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 190, 151, 16));
        QFont font1;
        font1.setBold(true);
        label->setFont(font1);
        label_2 = new QLabel(InterfaceEnregistrement);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(590, 190, 151, 16));
        label_2->setFont(font1);
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
        textEditFeedBack->raise();
        pushButtonPlay->raise();
        textEditConsigne->raise();
        label->raise();
        label_2->raise();

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
        pushButton->setText(QCoreApplication::translate("InterfaceEnregistrement", "Interface Enregistrement", nullptr));
        pushButtonPause->setText(QString());
        labelAppelProf->setText(QCoreApplication::translate("InterfaceEnregistrement", "Le prof a \303\251t\303\251 appel\303\251", nullptr));
        pushButtonRetourArriere->setText(QString());
        pushButtonEnregistrer->setText(QString());
        textEditFeedBack->setHtml(QCoreApplication::translate("InterfaceEnregistrement", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe UI'; font-size:9pt;\"><br /></p></body></html>", nullptr));
        pushButtonPlay->setText(QString());
        textEditConsigne->setHtml(QCoreApplication::translate("InterfaceEnregistrement", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("InterfaceEnregistrement", "Messages du professeur", nullptr));
        label_2->setText(QCoreApplication::translate("InterfaceEnregistrement", "Consignes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfaceEnregistrement: public Ui_InterfaceEnregistrement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEENREGISTREMENT_H
