#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlError>
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
    void on_pushButton_InterVideo_clicked();

    void on_label_Loading_linkActivated(const QString &link);

    void on_pushButton_InterAudio_clicked();

private:
    Ui::MainWindow *ui;
    QMovie *loadingMovie;
    QSqlDatabase db;

    void startLoading();
    void stopLoading();
};
#endif // MAINWINDOW_H
