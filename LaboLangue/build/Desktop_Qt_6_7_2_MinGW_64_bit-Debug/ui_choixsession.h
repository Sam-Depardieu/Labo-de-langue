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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_choixSession
{
public:

    void setupUi(QWidget *choixSession)
    {
        if (choixSession->objectName().isEmpty())
            choixSession->setObjectName("choixSession");
        choixSession->resize(1000, 560);

        retranslateUi(choixSession);

        QMetaObject::connectSlotsByName(choixSession);
    } // setupUi

    void retranslateUi(QWidget *choixSession)
    {
        choixSession->setWindowTitle(QCoreApplication::translate("choixSession", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class choixSession: public Ui_choixSession {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOIXSESSION_H
