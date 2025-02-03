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

private:
    Ui::InterfaceEnregistrement *ui;
};

#endif // INTERFACEENREGISTREMENT_H
