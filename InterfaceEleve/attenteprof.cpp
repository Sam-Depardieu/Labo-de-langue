#include "attenteprof.h"
#include "ui_attenteprof.h"
#include <QTimer>
AttenteProf::AttenteProf(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AttenteProf)
    , loadingMovie(new QMovie(":/videos/loading.gif"))
{
    ui->setupUi(this);
    setFixedSize(800,480);
    this->setWindowTitle("Attente");
    ui->label_Loading->setMovie(loadingMovie);
    loadingMovie->start();

}

AttenteProf::~AttenteProf()
{
    delete ui;
    delete loadingMovie;
}
void AttenteProf::startLoading()
{
    ui->label_Loading->setVisible(true);
    loadingMovie->start();
}
void AttenteProf::stopLoading()
{
    ui->label_Loading->setVisible(false);
    loadingMovie->stop();
}
void AttenteProf::on_label_Loading_linkActivated(const QString &link)
{

}

