#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "iconEleveGroup.h"
#include "AudioCommunicator.h"
#include "qcm.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class iconEleveGroup;
class QCM;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    int idTypeActivite = -1;
    std::vector<iconEleveGroup*> listeRasp = {};
    std::vector<iconEleveGroup*> listeParticipant = {};
    std::vector<int> listeEleveParticipant = {};
    std::vector<iconEleveGroup*> listeEditEleve = {};

    bool parametrageSession = false;
    bool selectionParticipants = false;
    bool selectAllParticipants = false;
    bool parametrageEleve = false;
    bool runningSession = false;

    void openSettingEleve(iconEleveGroup *group);
    void closeSettingEleve(iconEleveGroup *group);
    QString getSessionFolder() {return sessionFolder;};

    ~MainWindow();

    int *X = 0;

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
    void showCheckIconOnGroup(iconEleveGroup *group);
    void on_SourceButton_clicked();
    void on_delButton_clicked();
    void saveSessionData(bool isNewSession);
    void on_echapButton_clicked();
    void resetSession();
    void on_loadSession_clicked();
    void on_CreationButton_clicked();

    // Bouton de ParametrageEleve
    void on_muteButton_clicked();
    void on_demuteButton_clicked();
    void on_desactiverSonButton_clicked();
    void on_activerSonButton_clicked();
    void on_creerGroupeButton_clicked();
    void on_annulerButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QSqlDatabase db;
    QGraphicsPixmapItem *item;
    QString source;
    QString sessionFolder;
    QString nomProf;
    Professor *prof;
    int idProf;
    QString duree;
    QString nomTypeActivite;
    int idClasse = -1;
    int typeActivite;




};
#endif // MAINWINDOW_H
