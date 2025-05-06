#ifndef CHOIXSESSION_H
#define CHOIXSESSION_H

#include <QWidget>

namespace Ui {
class choixSession;
}

class choixSession : public QWidget
{
    Q_OBJECT

public:
    explicit choixSession(QWidget *parent = nullptr);
    ~choixSession();

private:
    Ui::choixSession *ui;
};

#endif // CHOIXSESSION_H
