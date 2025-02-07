#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    bool connectToDatabase();
    void on_pushButtonEnregistrement_clicked();

    void on_pushButtonConnexion_clicked();

    void on_pushButtonInterfaceQCM_clicked();

    void on_pushButtonInterfaceAudio_clicked();

    void on_pushButtonInterfaceVideo_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

};
#endif // MAINWINDOW_H
