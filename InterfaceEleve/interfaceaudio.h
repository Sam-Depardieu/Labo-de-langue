#ifndef INTERFACEAUDIO_H
#define INTERFACEAUDIO_H

#include <QDialog>

namespace Ui {
class InterfaceAudio;
}

class InterfaceAudio : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceAudio(QWidget *parent = nullptr);
    ~InterfaceAudio();

private:
    Ui::InterfaceAudio *ui;
};

#endif // INTERFACEAUDIO_H
