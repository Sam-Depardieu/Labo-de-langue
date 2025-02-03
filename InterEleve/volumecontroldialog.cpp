#include "volumecontroldialog.h"
#include "ui_volumecontroldialog.h"

VolumeControlDialog::VolumeControlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VolumeControlDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Interface Volume");
    // Initialisez les sliders avec des valeurs par défaut
    ui->sliderSystemVolume->setValue(50);
    ui->sliderStudentVolume->setValue(50);

    connect(ui->sliderSystemVolume, &QSlider::valueChanged, this, &VolumeControlDialog::on_sliderSystemVolume_valueChanged);
    connect(ui->sliderStudentVolume, &QSlider::valueChanged, this, &VolumeControlDialog::on_sliderStudentVolume_valueChanged);
}

VolumeControlDialog::~VolumeControlDialog()
{
    delete ui;
}

void VolumeControlDialog::on_sliderSystemVolume_valueChanged(int value)
{
    qDebug() <<"Volume Système :"<< value << "%" ;
    // Implémentez la logique pour ajuster le volume du système ici
}

void VolumeControlDialog::on_sliderStudentVolume_valueChanged(int value)
{
    qDebug() <<"Volume Elève :"<< value << "%";
    // Implémentez la logique pour ajuster le volume de l'élève ici
}
