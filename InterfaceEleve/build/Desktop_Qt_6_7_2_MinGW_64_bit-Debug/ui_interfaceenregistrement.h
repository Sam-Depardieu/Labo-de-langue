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
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_InterfaceEnregistrement
{
public:
    QPushButton *pushButtonSon;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonAppelProf;
    QPushButton *pushButton_2;
    QLabel *chrono_enregistrement;
    QPushButton *pushButtonSpeak;
    QPushButton *pushButtonPause;
    QPushButton *pushButtonRetourArriere;
    QPushButton *pushButtonEnregistrer;
    QTextEdit *textEditFeedBack;
    QPushButton *pushButtonPlay;
    QTextEdit *textEditConsigne;
    QLabel *label;
    QLabel *label_2;
    QSlider *verticalSlider_son;
    QLabel *chronoLabel;
    QLabel *label_3;
    QSlider *verticalSlider_sonVideo;

    void setupUi(QDialog *InterfaceEnregistrement)
    {
        if (InterfaceEnregistrement->objectName().isEmpty())
            InterfaceEnregistrement->setObjectName("InterfaceEnregistrement");
        InterfaceEnregistrement->resize(800, 480);
        pushButtonSon = new QPushButton(InterfaceEnregistrement);
        pushButtonSon->setObjectName("pushButtonSon");
        pushButtonSon->setGeometry(QRect(730, 430, 45, 45));
        pushButtonSon->setAutoFillBackground(false);
        pushButtonSon->setStyleSheet(QString::fromUtf8(""));
        pushButtonClear = new QPushButton(InterfaceEnregistrement);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(610, 430, 45, 45));
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
        pushButton_2->setGeometry(QRect(0, 425, 801, 61));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    font-weight: bold; /* Optionnel : texte en gras */"));
        chrono_enregistrement = new QLabel(InterfaceEnregistrement);
        chrono_enregistrement->setObjectName("chrono_enregistrement");
        chrono_enregistrement->setGeometry(QRect(320, 340, 221, 61));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        chrono_enregistrement->setFont(font);
        chrono_enregistrement->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButtonSpeak = new QPushButton(InterfaceEnregistrement);
        pushButtonSpeak->setObjectName("pushButtonSpeak");
        pushButtonSpeak->setGeometry(QRect(390, 240, 81, 81));
        pushButtonSpeak->setStyleSheet(QString::fromUtf8(""));
        pushButtonPause = new QPushButton(InterfaceEnregistrement);
        pushButtonPause->setObjectName("pushButtonPause");
        pushButtonPause->setGeometry(QRect(390, 90, 81, 81));
        pushButtonPause->setStyleSheet(QString::fromUtf8(""));
        pushButtonRetourArriere = new QPushButton(InterfaceEnregistrement);
        pushButtonRetourArriere->setObjectName("pushButtonRetourArriere");
        pushButtonRetourArriere->setGeometry(QRect(210, 90, 81, 81));
        pushButtonRetourArriere->setStyleSheet(QString::fromUtf8(""));
        pushButtonEnregistrer = new QPushButton(InterfaceEnregistrement);
        pushButtonEnregistrer->setObjectName("pushButtonEnregistrer");
        pushButtonEnregistrer->setGeometry(QRect(540, 430, 45, 45));
        pushButtonEnregistrer->setStyleSheet(QString::fromUtf8(""));
        textEditFeedBack = new QTextEdit(InterfaceEnregistrement);
        textEditFeedBack->setObjectName("textEditFeedBack");
        textEditFeedBack->setGeometry(QRect(10, 220, 211, 201));
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
        pushButtonPlay->setGeometry(QRect(390, 90, 81, 81));
        pushButtonPlay->setStyleSheet(QString::fromUtf8(""));
        textEditConsigne = new QTextEdit(InterfaceEnregistrement);
        textEditConsigne->setObjectName("textEditConsigne");
        textEditConsigne->setGeometry(QRect(580, 220, 211, 201));
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
        label->setGeometry(QRect(30, 171, 171, 31));
        QFont font1;
        font1.setBold(true);
        label->setFont(font1);
        label_2 = new QLabel(InterfaceEnregistrement);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(590, 200, 151, 16));
        label_2->setFont(font1);
        verticalSlider_son = new QSlider(InterfaceEnregistrement);
        verticalSlider_son->setObjectName("verticalSlider_son");
        verticalSlider_son->setGeometry(QRect(760, 250, 16, 160));
        verticalSlider_son->setOrientation(Qt::Orientation::Vertical);
        chronoLabel = new QLabel(InterfaceEnregistrement);
        chronoLabel->setObjectName("chronoLabel");
        chronoLabel->setGeometry(QRect(110, 430, 111, 45));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setBold(true);
        chronoLabel->setFont(font2);
        chronoLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: rgb(0, 151, 178); /* m\303\252me ton bleu-vert que ta barre */\n"
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
        label_3 = new QLabel(InterfaceEnregistrement);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 800, 55));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    font-weight: bold; /* Optionnel : texte en gras */"));
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        verticalSlider_sonVideo = new QSlider(InterfaceEnregistrement);
        verticalSlider_sonVideo->setObjectName("verticalSlider_sonVideo");
        verticalSlider_sonVideo->setGeometry(QRect(780, 60, 16, 160));
        verticalSlider_sonVideo->setOrientation(Qt::Orientation::Vertical);
        label_3->raise();
        verticalSlider_son->raise();
        pushButton_2->raise();
        pushButtonSon->raise();
        pushButtonClear->raise();
        chrono_enregistrement->raise();
        pushButtonSpeak->raise();
        pushButtonPause->raise();
        pushButtonRetourArriere->raise();
        pushButtonAppelProf->raise();
        pushButtonEnregistrer->raise();
        textEditFeedBack->raise();
        pushButtonPlay->raise();
        textEditConsigne->raise();
        label->raise();
        label_2->raise();
        chronoLabel->raise();
        verticalSlider_sonVideo->raise();

        retranslateUi(InterfaceEnregistrement);

        QMetaObject::connectSlotsByName(InterfaceEnregistrement);
    } // setupUi

    void retranslateUi(QDialog *InterfaceEnregistrement)
    {
        InterfaceEnregistrement->setWindowTitle(QCoreApplication::translate("InterfaceEnregistrement", "Dialog", nullptr));
        pushButtonSon->setText(QString());
        pushButtonClear->setText(QString());
        pushButtonAppelProf->setText(QString());
        pushButton_2->setText(QString());
        chrono_enregistrement->setText(QString());
        pushButtonSpeak->setText(QString());
        pushButtonPause->setText(QString());
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
        label->setText(QCoreApplication::translate("InterfaceEnregistrement", "<p><center>Messages du professeur</center></p>", nullptr));
        label_2->setText(QCoreApplication::translate("InterfaceEnregistrement", "Consignes", nullptr));
        chronoLabel->setText(QCoreApplication::translate("InterfaceEnregistrement", "00:00", nullptr));
        label_3->setText(QCoreApplication::translate("InterfaceEnregistrement", "Interface Enregistrement", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfaceEnregistrement: public Ui_InterfaceEnregistrement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEENREGISTREMENT_H
