#include "interfacevideo.h"
#include "ui_interfacevideo.h"

InterfaceVideo::InterfaceVideo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceVideo)
{
    ui->setupUi(this);
}

InterfaceVideo::~InterfaceVideo()
{
    delete ui;
}
