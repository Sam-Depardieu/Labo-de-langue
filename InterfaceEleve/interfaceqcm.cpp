#include "interfaceqcm.h"
#include "ui_interfaceqcm.h"

InterfaceQCM::InterfaceQCM(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceQCM)
{
    ui->setupUi(this);
}

InterfaceQCM::~InterfaceQCM()
{
    delete ui;
}
