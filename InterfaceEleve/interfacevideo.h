#ifndef INTERFACEVIDEO_H
#define INTERFACEVIDEO_H

#include <QDialog>

namespace Ui {
class InterfaceVideo;
}

class InterfaceVideo : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceVideo(QWidget *parent = nullptr);
    ~InterfaceVideo();

private:
    Ui::InterfaceVideo *ui;
};

#endif // INTERFACEVIDEO_H
