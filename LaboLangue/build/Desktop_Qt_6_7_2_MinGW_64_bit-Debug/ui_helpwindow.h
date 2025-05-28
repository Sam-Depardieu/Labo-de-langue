/********************************************************************************
** Form generated from reading UI file 'helpwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPWINDOW_H
#define UI_HELPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelpWindow
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *mainWindowButton;
    QPushButton *gestionStudentButton;
    QPushButton *choixSessionButton;
    QPushButton *qcmButton;
    QTableWidget *tableWidget;

    void setupUi(QDialog *HelpWindow)
    {
        if (HelpWindow->objectName().isEmpty())
            HelpWindow->setObjectName("HelpWindow");
        HelpWindow->resize(700, 500);
        horizontalLayoutWidget = new QWidget(HelpWindow);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 701, 52));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        mainWindowButton = new QPushButton(horizontalLayoutWidget);
        mainWindowButton->setObjectName("mainWindowButton");
        mainWindowButton->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(mainWindowButton);

        gestionStudentButton = new QPushButton(horizontalLayoutWidget);
        gestionStudentButton->setObjectName("gestionStudentButton");
        gestionStudentButton->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(gestionStudentButton);

        choixSessionButton = new QPushButton(horizontalLayoutWidget);
        choixSessionButton->setObjectName("choixSessionButton");
        choixSessionButton->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(choixSessionButton);

        qcmButton = new QPushButton(horizontalLayoutWidget);
        qcmButton->setObjectName("qcmButton");
        qcmButton->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(qcmButton);

        tableWidget = new QTableWidget(HelpWindow);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 60, 681, 431));
        tableWidget->setWordWrap(true);

        retranslateUi(HelpWindow);

        QMetaObject::connectSlotsByName(HelpWindow);
    } // setupUi

    void retranslateUi(QDialog *HelpWindow)
    {
        HelpWindow->setWindowTitle(QCoreApplication::translate("HelpWindow", "Dialog", nullptr));
        mainWindowButton->setText(QCoreApplication::translate("HelpWindow", "G\303\251n\303\251ral", nullptr));
        gestionStudentButton->setText(QCoreApplication::translate("HelpWindow", "Gestion \303\251l\303\250ves", nullptr));
        choixSessionButton->setText(QCoreApplication::translate("HelpWindow", "Gestion sessions", nullptr));
        qcmButton->setText(QCoreApplication::translate("HelpWindow", "Cr\303\251ation QCM", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HelpWindow: public Ui_HelpWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPWINDOW_H
