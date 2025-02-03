#ifndef ATTENTEPROF_H
#define ATTENTEPROF_H

#include <QDialog>  // Corrigé : QDialog au lieu de QMainWindow
#include <QMovie>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class AttenteProf;
}
QT_END_NAMESPACE

class AttenteProf : public QDialog  // Corrigé : Hérite de QDialog
{
    Q_OBJECT

public:
    explicit AttenteProf(QWidget *parent = nullptr);  // `explicit` pour éviter les conversions implicites
    ~AttenteProf();

private slots:
    void on_pushButton_InterVideo_clicked();
    void on_pushButton_InterAudio_clicked();

private:
    Ui::AttenteProf *ui;
    QMovie *loadingMovie;
    QSqlDatabase db;

    void startLoading();
    void stopLoading();
};

#endif // ATTENTEPROF_H
