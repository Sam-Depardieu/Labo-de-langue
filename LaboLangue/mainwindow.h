#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customgraphicsitemgroup.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class CustomGraphicsItemGroup;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    int idTypeActivite = -1;
    std::vector<CustomGraphicsItemGroup*> listeRasp = {};
    std::vector<CustomGraphicsItemGroup*> listeParticipant = {};
    std::vector<int> listeEleveParticipant = {};

    bool parametrageSession = false;
    bool selectionParticipants = false;
    bool selectAllParticipants = false;
    bool parametrageEleve = false;

    void openSettingEleve(CustomGraphicsItemGroup *group);
    void closeSettingEleve(CustomGraphicsItemGroup *group);

    ~MainWindow();

private slots:
    void on_PlanButton_clicked();
    void keyPressEvent(QKeyEvent *event);
    void loadImagesFromDB();
    bool connectToDatabase();
    void onImageGroupDoubleClicked();
    void setupActivitiesComboBox();
    void setupClassesComboBox();
    void on_SessionButton_clicked();
    void on_ChoixActivite_currentIndexChanged(int index);
    void on_selectManuel_clicked();
    void editStatusButton(QPushButton *button, bool status);
    void addHorizontalLayout(QVBoxLayout *layout, QWidget *widget1, QWidget *widget2);
    void addHorizontalLayout(QVBoxLayout *layout, QWidget *widget1, QWidget *widget2, QWidget *widget3);
    void addButtonRow(QVBoxLayout *layout, QWidget *button1, QWidget *button2, QWidget *button3);
    void on_selectAll_clicked();
    void on_validButton_clicked();
    void showCheckIconOnGroup(CustomGraphicsItemGroup *group);
    void on_SourceButton_clicked();
    void on_delButton_clicked();
    void saveSessionData(bool isNewSession);
    void on_echapButton_clicked();
    void resetSession();
    void on_loadSession_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QSqlDatabase db;
    QGraphicsPixmapItem *item;
    QString source;
    QString nomProf;
    int idProf;
    QString duree;
    QString nomTypeActivite;
    int idClasse = -1;
    bool runningSession;
    int typeActivite;


};
#endif // MAINWINDOW_H
