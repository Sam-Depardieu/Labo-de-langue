#ifndef INTERFACEENREGISTREMENT_H
#define INTERFACEENREGISTREMENT_H

#include <QDialog>

namespace Ui {
class InterfaceEnregistrement;
}

class InterfaceEnregistrement : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceEnregistrement(QWidget *parent = nullptr);
    ~InterfaceEnregistrement();

private slots:
    void on_pushButtonSon_clicked();

    void on_pushButtonSignet_clicked();

    void on_pushButtonFavoris_clicked();

    void on_pushButtonRevenirALaPhrasePrecedente_clicked();

    void on_pushButtonRepeter_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButtonSurveiller_clicked();

    void on_pushButtonRetourArriere_clicked();

    void on_pushButtonPause_clicked();

    void on_pushButtonAvancer_clicked();

    void on_pushButtonSpeak_clicked();

    void on_pushButtonPlay_clicked();

    void on_pushButtonAppelProf_clicked();

private:
    Ui::InterfaceEnregistrement *ui;
};

#endif // INTERFACEENREGISTREMENT_H
