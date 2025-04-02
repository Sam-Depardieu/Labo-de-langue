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
    if(audioEleveMulti != nullptr)
    {
        delete audioEleveMulti;
        audioEleveMulti = nullptr;
    }
    QHostAddress serverAddress  = QHostAddress(ui->lineEditAdresseServeur->text());
    quint16 port = ui->lineEditPortServeur->text().toUInt();
    QString groupe = ui->lineEditGroupe->text();
    audioEleveMulti = new AudioEleveMulti(serverAddress,port,groupe,this);
}

