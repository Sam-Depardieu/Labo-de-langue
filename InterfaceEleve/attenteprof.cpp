#include "attenteprof.h"
#include "ui_attenteprof.h"

AttenteProf::AttenteProf(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AttenteProf)
{
    ui->setupUi(this);
}

AttenteProf::~AttenteProf()
{
    delete ui;
}
