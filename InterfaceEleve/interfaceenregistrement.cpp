#include "interfaceenregistrement.h"
#include "ui_interfaceenregistrement.h"

InterfaceEnregistrement::InterfaceEnregistrement(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceEnregistrement)
{
    ui->setupUi(this);
    setFixedSize(800,480);
}

InterfaceEnregistrement::~InterfaceEnregistrement()
{
    delete ui;
}
