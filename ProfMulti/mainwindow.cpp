#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonConnexion_clicked()
{
    if(audioProfMulti != nullptr)
    {
        delete audioProfMulti;
        audioProfMulti = nullptr;
    }
    QHostAddress serverAddress  = QHostAddress(ui->lineEditAdresseServeur->text());
    quint16 port = ui->lineEditPortServeur->text().toUInt();
    QString groupe = ui->lineEditGroupe->text();
    audioProfMulti = new AudioProfMulti(serverAddress,port,groupe,this);
}

