#ifndef VOLUMECONTROLDIALOG_H
#define VOLUMECONTROLDIALOG_H

#include <QDialog>

namespace Ui {
class VolumeControlDialog;
}

class VolumeControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VolumeControlDialog(QWidget *parent = nullptr);
    ~VolumeControlDialog();

private slots:
    void on_sliderSystemVolume_valueChanged(int value);
    void on_sliderStudentVolume_valueChanged(int value);

private:
    Ui::VolumeControlDialog *ui;
};

#endif // VOLUMECONTROLDIALOG_H
