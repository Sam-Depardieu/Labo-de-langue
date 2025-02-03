/********************************************************************************
** Form generated from reading UI file 'volumecontroldialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOLUMECONTROLDIALOG_H
#define UI_VOLUMECONTROLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_VolumeControlDialog
{
public:
    QSlider *sliderSystemVolume;
    QSlider *sliderStudentVolume;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *VolumeControlDialog)
    {
        if (VolumeControlDialog->objectName().isEmpty())
            VolumeControlDialog->setObjectName("VolumeControlDialog");
        VolumeControlDialog->resize(800, 480);
        sliderSystemVolume = new QSlider(VolumeControlDialog);
        sliderSystemVolume->setObjectName("sliderSystemVolume");
        sliderSystemVolume->setGeometry(QRect(607, 120, 40, 160));
        sliderSystemVolume->setOrientation(Qt::Vertical);
        sliderStudentVolume = new QSlider(VolumeControlDialog);
        sliderStudentVolume->setObjectName("sliderStudentVolume");
        sliderStudentVolume->setGeometry(QRect(710, 120, 16, 160));
        sliderStudentVolume->setOrientation(Qt::Vertical);
        label = new QLabel(VolumeControlDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(600, 290, 51, 51));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Image/SonEleve.png")));
        label_2 = new QLabel(VolumeControlDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(690, 290, 51, 51));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/Image/SonSysteme.png")));

        retranslateUi(VolumeControlDialog);

        QMetaObject::connectSlotsByName(VolumeControlDialog);
    } // setupUi

    void retranslateUi(QDialog *VolumeControlDialog)
    {
        VolumeControlDialog->setWindowTitle(QCoreApplication::translate("VolumeControlDialog", "Dialog", nullptr));
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VolumeControlDialog: public Ui_VolumeControlDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOLUMECONTROLDIALOG_H
