#include "helpwindow.h"
#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
    setWindowTitle("Aide - Application Professeur");
    setModal(true); // empêche d'autres fenêtres d'interagir
    //setAttribute(Qt::WA_DeleteOnClose); // libère la mémoire à la fermeture
}



HelpWindow::~HelpWindow()
{
    delete ui;
}
