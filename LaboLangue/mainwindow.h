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
    Ui::MainWindow *ui;

    int idTypeActivite = -1;
    std::vector<iconEleveGroup*> listeRasp = {};
    std::vector<iconEleveGroup*> listeParticipant = {};
    std::vector<int> listeEleveParticipant = {};
    std::vector<iconEleveGroup*> listeEditEleve = {};
    iconEleveGroup* eleveActuellementParametre = nullptr;

    bool parametrageSession = false;
    bool selectionParticipants = false;
    bool selectAllParticipants = false;
    bool parametrageEleve = false;
    bool runningSession = false;
    bool interfaceQCMOpen = false;

    void toggleSettingEleve(iconEleveGroup *group, bool open);
    QString getSessionFolder() {return sessionFolder;};
    void setNomEtudiantLineEdit(QString nom);
    void updateCheckItemsVisibility();

    ~MainWindow();

private slots:
    void on_PlanButton_clicked();
    void loadImagesFromDB();
    bool connectToDatabase();
    void onImageGroupDoubleClicked();
    void editStatusButton(QPushButton *button, bool status);
    void addHorizontalLayout(QVBoxLayout *layout, std::initializer_list<QWidget*> widgets);
    void showCheckIconOnGroup(iconEleveGroup *group);

    // Bouton de Création de Session
    void on_SessionButton_clicked();
    void on_ChoixActivite_currentIndexChanged(int index);
    void on_loadSession_clicked();
    void on_CreationButton_clicked();
    void on_selectAll_clicked();
    void on_selectManuel_clicked();
    void on_validButton_clicked();
    void on_SourceButton_clicked();
    void on_delButton_clicked();
    void on_echapButton_clicked();
    void resetSession();
    void setupActivitiesComboBox();
    void setupClassesComboBox();
    void saveSessionData(bool isNewSession);

    // Bouton de ParametrageEleve
    void on_muteButton_clicked();
    void on_demuteButton_clicked();
    void on_desactiverSonButton_clicked();
    void on_activerSonButton_clicked();
    void on_creerGroupeButton_clicked();
    void on_annulerButton_clicked();
    void on_Communication_clicked();
    void on_nomEleveLineEdit_editingFinished();
    void changeNameTable(QTableWidgetItem* item);
    void changeNameGroup(iconEleveGroup *group, QString newName);
    void loadInformationTable();
    void on_envoyerMessagePersonne_clicked();
    void on_envoyerMessageGroupe_clicked();

    void on_modeClairButton_clicked();

    void on_modeSombreButton_clicked();

private:
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

    QTableWidget* TableauGroupe ;


};
#endif // MAINWINDOW_H
