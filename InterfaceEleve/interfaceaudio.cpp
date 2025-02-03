#include "interfaceaudio.h"
#include "ui_interfaceaudio.h"

InterfaceAudio::InterfaceAudio(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceAudio)
{
    ui->setupUi(this);
    setFixedSize(800,480);
}

InterfaceAudio::~InterfaceAudio()
{
    delete ui;
}
