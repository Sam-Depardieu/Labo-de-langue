#ifndef INTERFACEQCM_H
#define INTERFACEQCM_H

#include <QDialog>

namespace Ui {
class InterfaceQCM;
}

class InterfaceQCM : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceQCM(QWidget *parent = nullptr);
    ~InterfaceQCM();

private slots:
    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

    void on_pushButtonEffacerReponse_clicked();

private:
    Ui::InterfaceQCM *ui;
    bool isButton1BaseImage; // Déclaration pour Button 1
    bool isButton2BaseImage; // Déclaration pour Button 2
    bool isButton3BaseImage; // Déclaration pour Button 3
    bool isButton4BaseImage;
};

#endif // INTERFACEQCM_H
