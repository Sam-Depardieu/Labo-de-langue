#include "interfacevideo.h"
#include "ui_interfacevideo.h"

InterfaceVideo::InterfaceVideo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InterfaceVideo)
{
    ui->setupUi(this);
    setFixedSize(800,480);
    this->setWindowTitle("Page de Video");
}

InterfaceVideo::~InterfaceVideo()
{
    delete ui;
}
