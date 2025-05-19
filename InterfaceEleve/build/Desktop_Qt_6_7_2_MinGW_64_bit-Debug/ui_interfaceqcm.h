/********************************************************************************
** Form generated from reading UI file 'interfaceqcm.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACEQCM_H
#define UI_INTERFACEQCM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_InterfaceQCM
{
public:
    QPushButton *pushButtonQuestionSuivante;
    QPushButton *pushButtonEffacerReponse;
    QPushButton *pushButtonQuestionPrecedente;
    QPushButton *pushButton;
    QLabel *labelQuestion;
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QPushButton *pushButton4;
    QPushButton *pushButton3;
    QTextEdit *textEditConsigne;
    QTextEdit *textEditFeedBack;
    QPushButton *pushButtonSoumettre;
    QTextEdit *textEditAffichageQuestion;
    QLabel *chronoLabel;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonAppelProf;

    void setupUi(QDialog *InterfaceQCM)
    {
        if (InterfaceQCM->objectName().isEmpty())
            InterfaceQCM->setObjectName("InterfaceQCM");
        InterfaceQCM->resize(800, 480);
        pushButtonQuestionSuivante = new QPushButton(InterfaceQCM);
        pushButtonQuestionSuivante->setObjectName("pushButtonQuestionSuivante");
        pushButtonQuestionSuivante->setGeometry(QRect(740, 5, 45, 45));
        pushButtonQuestionSuivante->setStyleSheet(QString::fromUtf8(""));
        pushButtonEffacerReponse = new QPushButton(InterfaceQCM);
        pushButtonEffacerReponse->setObjectName("pushButtonEffacerReponse");
        pushButtonEffacerReponse->setGeometry(QRect(670, 5, 45, 45));
        pushButtonEffacerReponse->setStyleSheet(QString::fromUtf8(""));
        pushButtonQuestionPrecedente = new QPushButton(InterfaceQCM);
        pushButtonQuestionPrecedente->setObjectName("pushButtonQuestionPrecedente");
        pushButtonQuestionPrecedente->setGeometry(QRect(10, 5, 45, 45));
        pushButtonQuestionPrecedente->setStyleSheet(QString::fromUtf8(""));
        pushButton = new QPushButton(InterfaceQCM);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 0, 800, 55));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    font-weight: bold; /* Optionnel : texte en gras */\n"
"}"));
        labelQuestion = new QLabel(InterfaceQCM);
        labelQuestion->setObjectName("labelQuestion");
        labelQuestion->setGeometry(QRect(170, 160, 491, 71));
        labelQuestion->setStyleSheet(QString::fromUtf8(" font-weight: bold; /* Optionnel : texte en gras */"));
        pushButton1 = new QPushButton(InterfaceQCM);
        pushButton1->setObjectName("pushButton1");
        pushButton1->setGeometry(QRect(150, 230, 241, 91));
        pushButton1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:blue; /* Fond bleu */\n"
"    border-radius: 20px; /* Optionnel : coins arrondis */\n"
"}"));
        pushButton2 = new QPushButton(InterfaceQCM);
        pushButton2->setObjectName("pushButton2");
        pushButton2->setGeometry(QRect(400, 230, 241, 91));
        pushButton2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:green; /* Fond bleu */\n"
"    border-radius: 20px; /* Optionnel : coins arrondis */\n"
"}"));
        pushButton4 = new QPushButton(InterfaceQCM);
        pushButton4->setObjectName("pushButton4");
        pushButton4->setGeometry(QRect(400, 330, 241, 91));
        pushButton4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:orange; /* Fond bleu */\n"
"    border-radius: 20px; /* Optionnel : coins arrondis */\n"
"}"));
        pushButton3 = new QPushButton(InterfaceQCM);
        pushButton3->setObjectName("pushButton3");
        pushButton3->setGeometry(QRect(150, 330, 241, 91));
        pushButton3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:red; /* Fond bleu */\n"
"    border-radius: 20px; /* Optionnel : coins arrondis */\n"
"}"));
        textEditConsigne = new QTextEdit(InterfaceQCM);
        textEditConsigne->setObjectName("textEditConsigne");
        textEditConsigne->setGeometry(QRect(10, 70, 781, 71));
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
        textEditFeedBack = new QTextEdit(InterfaceQCM);
        textEditFeedBack->setObjectName("textEditFeedBack");
        textEditFeedBack->setGeometry(QRect(10, 230, 131, 241));
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
        pushButtonSoumettre = new QPushButton(InterfaceQCM);
        pushButtonSoumettre->setObjectName("pushButtonSoumettre");
        pushButtonSoumettre->setGeometry(QRect(80, 5, 45, 45));
        pushButtonSoumettre->setStyleSheet(QString::fromUtf8(""));
        textEditAffichageQuestion = new QTextEdit(InterfaceQCM);
        textEditAffichageQuestion->setObjectName("textEditAffichageQuestion");
        textEditAffichageQuestion->setGeometry(QRect(660, 230, 131, 241));
        textEditAffichageQuestion->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background-color: #f5f5f5;\n"
"    border: 2px solid #007a8c;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    font-size: 14px;\n"
"    font-family: \"Segoe UI\", sans-serif;\n"
"    color: #333;\n"
"}\n"
""));
        chronoLabel = new QLabel(InterfaceQCM);
        chronoLabel->setObjectName("chronoLabel");
        chronoLabel->setGeometry(QRect(170, 5, 111, 45));
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
        label = new QLabel(InterfaceQCM);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 210, 141, 16));
        QFont font1;
        font1.setBold(true);
        label->setFont(font1);
        label_2 = new QLabel(InterfaceQCM);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(660, 210, 151, 16));
        label_2->setFont(font1);
        pushButtonAppelProf = new QPushButton(InterfaceQCM);
        pushButtonAppelProf->setObjectName("pushButtonAppelProf");
        pushButtonAppelProf->setGeometry(QRect(600, 5, 45, 45));
        pushButtonAppelProf->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("call-start")));
        pushButtonAppelProf->setIcon(icon);
        pushButton->raise();
        pushButtonQuestionSuivante->raise();
        pushButtonQuestionPrecedente->raise();
        labelQuestion->raise();
        pushButtonEffacerReponse->raise();
        pushButton1->raise();
        pushButton2->raise();
        pushButton4->raise();
        pushButton3->raise();
        textEditConsigne->raise();
        textEditFeedBack->raise();
        pushButtonSoumettre->raise();
        textEditAffichageQuestion->raise();
        chronoLabel->raise();
        label->raise();
        label_2->raise();
        pushButtonAppelProf->raise();

        retranslateUi(InterfaceQCM);

        QMetaObject::connectSlotsByName(InterfaceQCM);
    } // setupUi

    void retranslateUi(QDialog *InterfaceQCM)
    {
        InterfaceQCM->setWindowTitle(QCoreApplication::translate("InterfaceQCM", "Dialog", nullptr));
        pushButtonQuestionSuivante->setText(QString());
        pushButtonEffacerReponse->setText(QString());
        pushButtonQuestionPrecedente->setText(QString());
        pushButton->setText(QCoreApplication::translate("InterfaceQCM", "Interface QCM", nullptr));
        labelQuestion->setText(QCoreApplication::translate("InterfaceQCM", "Question n\302\260", nullptr));
        pushButton1->setText(QCoreApplication::translate("InterfaceQCM", "1 :", nullptr));
        pushButton2->setText(QCoreApplication::translate("InterfaceQCM", "2 :", nullptr));
        pushButton4->setText(QCoreApplication::translate("InterfaceQCM", "4 :", nullptr));
        pushButton3->setText(QCoreApplication::translate("InterfaceQCM", "3 :", nullptr));
        textEditConsigne->setHtml(QCoreApplication::translate("InterfaceQCM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-size:9pt;\">Consignes :</span></p></body></html>", nullptr));
        textEditFeedBack->setHtml(QCoreApplication::translate("InterfaceQCM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        pushButtonSoumettre->setText(QString());
        textEditAffichageQuestion->setHtml(QCoreApplication::translate("InterfaceQCM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Segoe UI'; font-size:9pt;\"><br /></p></body></html>", nullptr));
        chronoLabel->setText(QCoreApplication::translate("InterfaceQCM", "00:00", nullptr));
        label->setText(QCoreApplication::translate("InterfaceQCM", "Messages du professeur", nullptr));
        label_2->setText(QCoreApplication::translate("InterfaceQCM", "Avancement", nullptr));
        pushButtonAppelProf->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InterfaceQCM: public Ui_InterfaceQCM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEQCM_H
