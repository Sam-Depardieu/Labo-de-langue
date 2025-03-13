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
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InterfaceQCM
{
public:
    QPushButton *pushButton1;
    QPushButton *pushButton4;
    QPushButton *pushButtonQuestionSuivante;
    QPushButton *pushButtonEffacerReponse;
    QPushButton *pushButton2;
    QPushButton *pushButton3;
    QPushButton *pushButtonQuestionPrecedente;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButtonSon;

    void setupUi(QDialog *InterfaceQCM)
    {
        if (InterfaceQCM->objectName().isEmpty())
            InterfaceQCM->setObjectName("InterfaceQCM");
        InterfaceQCM->resize(800, 480);
        pushButton1 = new QPushButton(InterfaceQCM);
        pushButton1->setObjectName("pushButton1");
        pushButton1->setGeometry(QRect(360, 160, 65, 65));
        pushButton1->setStyleSheet(QString::fromUtf8(""));
        pushButton4 = new QPushButton(InterfaceQCM);
        pushButton4->setObjectName("pushButton4");
        pushButton4->setGeometry(QRect(290, 230, 65, 65));
        pushButtonQuestionSuivante = new QPushButton(InterfaceQCM);
        pushButtonQuestionSuivante->setObjectName("pushButtonQuestionSuivante");
        pushButtonQuestionSuivante->setGeometry(QRect(430, 403, 75, 75));
        pushButtonQuestionSuivante->setStyleSheet(QString::fromUtf8(""));
        pushButtonEffacerReponse = new QPushButton(InterfaceQCM);
        pushButtonEffacerReponse->setObjectName("pushButtonEffacerReponse");
        pushButtonEffacerReponse->setGeometry(QRect(670, 403, 75, 75));
        pushButtonEffacerReponse->setStyleSheet(QString::fromUtf8(""));
        pushButton2 = new QPushButton(InterfaceQCM);
        pushButton2->setObjectName("pushButton2");
        pushButton2->setGeometry(QRect(430, 230, 65, 65));
        pushButton3 = new QPushButton(InterfaceQCM);
        pushButton3->setObjectName("pushButton3");
        pushButton3->setGeometry(QRect(360, 300, 65, 65));
        pushButtonQuestionPrecedente = new QPushButton(InterfaceQCM);
        pushButtonQuestionPrecedente->setObjectName("pushButtonQuestionPrecedente");
        pushButtonQuestionPrecedente->setGeometry(QRect(290, 403, 75, 75));
        pushButtonQuestionPrecedente->setStyleSheet(QString::fromUtf8(""));
        pushButton = new QPushButton(InterfaceQCM);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 0, 800, 80));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */\n"
"}"));
        pushButton_2 = new QPushButton(InterfaceQCM);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(0, 400, 801, 81));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 151, 178); /* Fond bleu */\n"
"    color: white; /* Texte en blanc */\n"
"    border: none; /* Enlever le contour si n\303\251cessaire */\n"
"    border-radius: 5px; /* Optionnel : coins arrondis */\n"
"    font-weight: bold; /* Optionnel : texte en gras */\n"
"}"));
        pushButtonSon = new QPushButton(InterfaceQCM);
        pushButtonSon->setObjectName("pushButtonSon");
        pushButtonSon->setGeometry(QRect(180, 240, 80, 80));
        pushButtonSon->setAutoFillBackground(false);
        pushButtonSon->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"    border: none;"));
        pushButton_2->raise();
        pushButton1->raise();
        pushButton4->raise();
        pushButtonQuestionSuivante->raise();
        pushButtonEffacerReponse->raise();
        pushButton2->raise();
        pushButton3->raise();
        pushButtonQuestionPrecedente->raise();
        pushButton->raise();
        pushButtonSon->raise();

        retranslateUi(InterfaceQCM);

        QMetaObject::connectSlotsByName(InterfaceQCM);
    } // setupUi

    void retranslateUi(QDialog *InterfaceQCM)
    {
        InterfaceQCM->setWindowTitle(QCoreApplication::translate("InterfaceQCM", "Dialog", nullptr));
        pushButton1->setText(QString());
        pushButton4->setText(QString());
        pushButtonQuestionSuivante->setText(QString());
        pushButtonEffacerReponse->setText(QString());
        pushButton2->setText(QString());
        pushButton3->setText(QString());
        pushButtonQuestionPrecedente->setText(QString());
        pushButton->setText(QCoreApplication::translate("InterfaceQCM", "Bienvenue sur l'interface de Question \303\240 choix multiple", nullptr));
        pushButton_2->setText(QString());
        pushButtonSon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InterfaceQCM: public Ui_InterfaceQCM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACEQCM_H
