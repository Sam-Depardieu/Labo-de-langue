#ifndef ATTENTEPROF_H
#define ATTENTEPROF_H

#include <QDialog>

namespace Ui {
class AttenteProf;
}

class AttenteProf : public QDialog
{
    Q_OBJECT

public:
    explicit AttenteProf(QWidget *parent = nullptr);
    ~AttenteProf();

private:
    Ui::AttenteProf *ui;
};

#endif // ATTENTEPROF_H
