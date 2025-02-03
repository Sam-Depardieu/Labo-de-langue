#ifndef INTERFACEAUDIOCO_H
#define INTERFACEAUDIOCO_H

#include <QDialog>
#include <QPixmap>
#include <QIcon>

namespace Ui {
class InterfaceAudioCO;
}

class InterfaceAudioCO : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceAudioCO(QWidget *parent = nullptr);
    ~InterfaceAudioCO();

private slots:
    void openInterfaceEnregistrement();  // Déclaration de la méthode

    void on_pushButtonAppelProf_clicked();
    void on_pushButtonSon_clicked();

private:
    Ui::InterfaceAudioCO *ui;
};

#endif // INTERFACEAUDIOCO_H
