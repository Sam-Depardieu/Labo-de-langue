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

    void setupUi(QDialog *InterfaceQCM)
    {
        if (InterfaceQCM->objectName().isEmpty())
            InterfaceQCM->setObjectName("InterfaceQCM");
        InterfaceQCM->resize(800, 480);
        pushButtonQuestionSuivante = new QPushButton(InterfaceQCM);
        pushButtonQuestionSuivante->setObjectName("pushButtonQuestionSuivante");
        pushButtonQuestionSuivante->setGeometry(QRect(710, 2, 75, 75));
        pushButtonQuestionSuivante->setStyleSheet(QString::fromUtf8(""));
        pushButtonEffacerReponse = new QPushButton(InterfaceQCM);
        pushButtonEffacerReponse->setObjectName("pushButtonEffacerReponse");
        pushButtonEffacerReponse->setGeometry(QRect(610, 2, 75, 75));
        pushButtonEffacerReponse->setStyleSheet(QString::fromUtf8(""));
        pushButtonQuestionPrecedente = new QPushButton(InterfaceQCM);
        pushButtonQuestionPrecedente->setObjectName("pushButtonQuestionPrecedente");
        pushButtonQuestionPrecedente->setGeometry(QRect(10, 2, 75, 75));
        pushButtonQuestionPrecedente->setStyleSheet(QString::fromUtf8(""));
        pushButton = new QPushButton(InterfaceQCM);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 0, 800, 80));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    font-weight: bold; /* Optionnel : texte en gras */\n"
"}"));
        labelQuestion = new QLabel(InterfaceQCM);
        labelQuestion->setObjectName("labelQuestion");
        labelQuestion->setGeometry(QRect(10, 160, 651, 71));
        labelQuestion->setStyleSheet(QString::fromUtf8(" font-weight: bold; /* Optionnel : texte en gras */"));
        pushButton1 = new QPushButton(InterfaceQCM);
        pushButton1->setObjectName("pushButton1");
        pushButton1->setGeometry(QRect(10, 240, 321, 100));
        pushButton1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:blue; /* Fond bleu */\n"
"    border-radius: 20px; /* Optionnel : coins arrondis */\n"
"}"));
        pushButton2 = new QPushButton(InterfaceQCM);
        pushButton2->setObjectName("pushButton2");
        pushButton2->setGeometry(QRect(340, 240, 321, 100));
        pushButton2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:green; /* Fond bleu */\n"
"    border-radius: 20px; /* Optionnel : coins arrondis */\n"
"}"));
        pushButton4 = new QPushButton(InterfaceQCM);
        pushButton4->setObjectName("pushButton4");
        pushButton4->setGeometry(QRect(340, 350, 321, 91));
        pushButton4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:orange; /* Fond bleu */\n"
"    border-radius: 20px; /* Optionnel : coins arrondis */\n"
"}"));
        pushButton3 = new QPushButton(InterfaceQCM);
        pushButton3->setObjectName("pushButton3");
        pushButton3->setGeometry(QRect(10, 350, 321, 91));
        pushButton3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color:red; /* Fond bleu */\n"
"    border-radius: 20px; /* Optionnel : coins arrondis */\n"
"}"));
        textEditConsigne = new QTextEdit(InterfaceQCM);
        textEditConsigne->setObjectName("textEditConsigne");
        textEditConsigne->setGeometry(QRect(10, 90, 651, 71));
        textEditFeedBack = new QTextEdit(InterfaceQCM);
        textEditFeedBack->setObjectName("textEditFeedBack");
        textEditFeedBack->setGeometry(QRect(670, 80, 121, 391));
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

        retranslateUi(InterfaceQCM);

        QMetaObject::connectSlotsByName(InterfaceQCM);
    } // setupUi

    void retranslateUi(QDialog *InterfaceQCM)
    {
        InterfaceQCM->setWindowTitle(QCoreApplication::translate("InterfaceQCM", "Dialog", nullptr));
        pushButtonQuestionSuivante->setText(QString());
        pushButtonEffacerReponse->setText(QString());
        pushButtonQuestionPrecedente->setText(QString());
        pushButton->setText(QCoreApplication::translate("InterfaceQCM", "Bienvenue sur l'interface de Question \303\240 choix multiple", nullptr));
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
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Consignes :</p></body></html>", nullptr));
        textEditFeedBack->setHtml(QCoreApplication::translate("InterfaceQCM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700; text-decoration: underline;\">Feedback</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">----------------------</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; ma"
                        "rgin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:700;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfaceQCM: public Ui_InterfaceQCM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEQCM_H
