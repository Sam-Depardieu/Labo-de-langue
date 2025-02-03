#include "attenteprof.h"
#include "ui_attenteprof.h"
#include "interfacevideo.h"
#include "interfaceaudio.h"
#include <QTimer>
#include <QDialog>

AttenteProf::AttenteProf(QWidget *parent)
    : QDialog(parent)  // Correction ici
    , ui(new Ui::AttenteProf)
    , loadingMovie(new QMovie(":/Video/loading.gif"))
{
    ui->setupUi(this);
    this->setWindowTitle("Attente");

    setFixedSize(800, 480); // Fixe la taille de la fenêtre

    ui->label_Loading->setMovie(loadingMovie);
    loadingMovie->start();  // Démarre l'animation
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

void AttenteProf::on_pushButton_InterVideo_clicked()
{
    InterfaceVideo *interfaceVideo = new InterfaceVideo(this);
    interfaceVideo->show();
}

void AttenteProf::on_pushButton_InterAudio_clicked()
{
    InterfaceAudio *interfaceAudio = new InterfaceAudio(this);
    interfaceAudio->show();
}
