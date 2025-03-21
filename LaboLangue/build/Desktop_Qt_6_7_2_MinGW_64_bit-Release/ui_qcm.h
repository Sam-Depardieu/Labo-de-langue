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
        QCM->resize(1000, 560);
        QCM->setStyleSheet(QString::fromUtf8("QDialog {\n"
"        background-color: #f5f5f5;\n"
"    }\n"
"    QLabel {\n"
"        font-size: 14px;\n"
"        font-weight: bold;\n"
"        color: #333;\n"
"    }\n"
"    QSpinBox, QLineEdit {\n"
"        border: 1px solid #ccc;\n"
"        border-radius: 4px;\n"
"        padding: 5px;\n"
"        background: white;\n"
"    }\n"
"    QPushButton {\n"
"        background-color: #007BFF;\n"
"        color: white;\n"
"        border-radius: 5px;\n"
"        padding: 7px;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #0056b3;\n"
"    }\n"
"    QPushButton#removeQuestionButton {\n"
"        background-color: #dc3545;\n"
"    }\n"
"    QPushButton#removeQuestionButton:hover {\n"
"        background-color: #a71d2a;\n"
"    }\n"
"    QFrame {\n"
"        background-color: #ccc;\n"
"    }"));

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
