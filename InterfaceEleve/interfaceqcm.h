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

private:
    Ui::InterfaceQCM *ui;
};

#endif // INTERFACEQCM_H
