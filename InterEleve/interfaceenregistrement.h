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
    void on_pushButtonAppelProf_clicked();
    void updateChrono();
    void on_pushButtonSpeak_clicked();
    void on_pushButtonPause_clicked();

    void on_pushButtonRetourArriere_clicked();
    void on_pushButtonPlay_clicked();

private:
    Ui::InterfaceEnregistrement *ui;
    QTimer *timer;
    int initialSecondes;
    int pauseClickCount;
    bool speakButtonClicked;
};

#endif // INTERFACEENREGISTREMENT_H
