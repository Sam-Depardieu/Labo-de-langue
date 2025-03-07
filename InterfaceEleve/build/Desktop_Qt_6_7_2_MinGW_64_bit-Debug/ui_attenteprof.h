/********************************************************************************
** Form generated from reading UI file 'attenteprof.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTENTEPROF_H
#define UI_ATTENTEPROF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_AttenteProf
{
public:
    QLabel *label_Loading;
    QLabel *label;

    void setupUi(QDialog *AttenteProf)
    {
        if (AttenteProf->objectName().isEmpty())
            AttenteProf->setObjectName("AttenteProf");
        AttenteProf->resize(800, 480);
        label_Loading = new QLabel(AttenteProf);
        label_Loading->setObjectName("label_Loading");
        label_Loading->setGeometry(QRect(300, 170, 191, 121));
        label_Loading->setStyleSheet(QString::fromUtf8("background-color : transparent;\n"
"border:none;\n"
""));
        label = new QLabel(AttenteProf);
        label->setObjectName("label");
        label->setGeometry(QRect(260, 70, 321, 91));
        label->raise();
        label_Loading->raise();

        retranslateUi(AttenteProf);

        QMetaObject::connectSlotsByName(AttenteProf);
    } // setupUi

    void retranslateUi(QDialog *AttenteProf)
    {
        AttenteProf->setWindowTitle(QCoreApplication::translate("AttenteProf", "Dialog", nullptr));
        label_Loading->setText(QString());
        label->setText(QCoreApplication::translate("AttenteProf", "<html><head/><body><p><span style=\" font-size:26pt; font-weight:700;\">Attente professeur</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AttenteProf: public Ui_AttenteProf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTENTEPROF_H
