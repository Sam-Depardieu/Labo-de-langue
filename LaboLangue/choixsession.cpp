#include "choixsession.h"
#include "ui_choixsession.h"

choixSession::choixSession(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::choixSession)
{
    ui->setupUi(this);
}

choixSession::~choixSession()
{
    delete ui;
}
