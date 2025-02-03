#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include "customgraphicsitemgroup.h"

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

    int idActivite = 0;
    std::vector<CustomGraphicsItemGroup*> listeElve = {};

    ~MainWindow();

private slots:
    void on_PlanButton_clicked();
    void keyPressEvent(QKeyEvent *event);
    void loadImagesFromDB();
    bool connectToDatabase();
    void onImageGroupDoubleClicked();

    void on_NewButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QSqlDatabase db;
    QGraphicsPixmapItem *item;
};
#endif // MAINWINDOW_H
