/********************************************************************************
** Form generated from reading UI file 'choixsession.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOIXSESSION_H
#define UI_CHOIXSESSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_choixSession
{
public:
    QListWidget *listeSession;
    QListWidget *infoSession;
    QLineEdit *findLineEdit;
    QPushButton *sortAZButton;
    QPushButton *sortZAButton;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *delSessionButton;
    QPushButton *takeSessionButton;

    void setupUi(QWidget *choixSession)
    {
        if (choixSession->objectName().isEmpty())
            choixSession->setObjectName("choixSession");
        choixSession->resize(1000, 560);
        listeSession = new QListWidget(choixSession);
        listeSession->setObjectName("listeSession");
        listeSession->setGeometry(QRect(10, 50, 371, 501));
        infoSession = new QListWidget(choixSession);
        infoSession->setObjectName("infoSession");
        infoSession->setGeometry(QRect(390, 10, 601, 501));
        findLineEdit = new QLineEdit(choixSession);
        findLineEdit->setObjectName("findLineEdit");
        findLineEdit->setGeometry(QRect(10, 13, 331, 31));
        sortAZButton = new QPushButton(choixSession);
        sortAZButton->setObjectName("sortAZButton");
        sortAZButton->setGeometry(QRect(350, 13, 31, 31));
        sortZAButton = new QPushButton(choixSession);
        sortZAButton->setObjectName("sortZAButton");
        sortZAButton->setGeometry(QRect(350, 13, 31, 31));
        horizontalLayoutWidget = new QWidget(choixSession);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(390, 520, 601, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(380);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        delSessionButton = new QPushButton(horizontalLayoutWidget);
        delSessionButton->setObjectName("delSessionButton");

        horizontalLayout->addWidget(delSessionButton);

        takeSessionButton = new QPushButton(horizontalLayoutWidget);
        takeSessionButton->setObjectName("takeSessionButton");

        horizontalLayout->addWidget(takeSessionButton);


        retranslateUi(choixSession);

        QMetaObject::connectSlotsByName(choixSession);
    } // setupUi

    void retranslateUi(QWidget *choixSession)
    {
        choixSession->setWindowTitle(QCoreApplication::translate("choixSession", "Form", nullptr));
        findLineEdit->setPlaceholderText(QCoreApplication::translate("choixSession", "Entrez un filtre", nullptr));
        sortAZButton->setText(QString());
        sortZAButton->setText(QString());
        delSessionButton->setText(QCoreApplication::translate("choixSession", "Supprimer session", nullptr));
        takeSessionButton->setText(QCoreApplication::translate("choixSession", "Choisir cette session", nullptr));
    } // retranslateUi

};

namespace Ui {
    class choixSession: public Ui_choixSession {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOIXSESSION_H
