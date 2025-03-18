/********************************************************************************
** Form generated from reading UI file 'qcm.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCM_H
#define UI_QCM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QCM
{
public:

    void setupUi(QWidget *QCM)
    {
        if (QCM->objectName().isEmpty())
            QCM->setObjectName("QCM");
        QCM->resize(400, 300);

        retranslateUi(QCM);

        QMetaObject::connectSlotsByName(QCM);
    } // setupUi

    void retranslateUi(QWidget *QCM)
    {
        QCM->setWindowTitle(QCoreApplication::translate("QCM", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QCM: public Ui_QCM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCM_H
