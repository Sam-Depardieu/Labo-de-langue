#ifndef ATTENTEPROF_H
#define ATTENTEPROF_H

#include <QDialog>
#include <QMovie>
namespace Ui {
class AttenteProf;
}

class AttenteProf : public QDialog
{
    Q_OBJECT

public:
    explicit AttenteProf(QWidget *parent = nullptr);
    ~AttenteProf();

private slots:
    void on_label_Loading_linkActivated(const QString &link);

private:
    Ui::AttenteProf *ui;
    QMovie *loadingMovie;
};

#endif // ATTENTEPROF_H
