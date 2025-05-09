#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "iconEleveGroup.h"
#include "AudioCommunicator.h"
#include "qcm.h"
#include "choixsession.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class iconEleveGroup;
class QCM;
class choixSession;
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
    QCM *qcm = nullptr;

    QMap<QString, std::vector<iconEleveGroup*>> listeGroup = {};
    /*
    Clé (QString)	Valeur (std::vector<iconEleveGroup*>)
    "Groupe A"      [Alice, Bob]
    "Groupe B"      [Charlie, David]
    */

    bool parametrageSession = false;
    bool selectionParticipants = false;
    bool selectAllParticipants = false;
    bool parametrageEleve = false;
    bool runningSession = false;
    bool interfaceQCMOpen = false;

    void toggleSettingEleve(iconEleveGroup *group, bool open);
    QString getSessionFolder() {return sessionFolder;};
    void setNomEtudiantLineEdit(QString nom);
    void setSource(QString newSource) {source = newSource;};
    void updateCheckItemsVisibility();
    bool getModeSombre() {return modeSombre;};

    ~MainWindow();

private slots:
    void on_PlanButton_clicked();
    void loadImagesFromDB();
    bool connectToDatabase();
    void onImageGroupDoubleClicked();
    void editStatusButton(QPushButton *button, bool status);
    void addHorizontalLayout(QVBoxLayout *layout, std::initializer_list<QWidget*> widgets);
    void showCheckIconOnGroup(iconEleveGroup *group);
    void majStatusQCM();
    void changeNameTable(QTableWidgetItem* item);
    void updateEleveNom(iconEleveGroup* eleve, const QString& newName);
    void updateNomDansBDD(int idEleve, const QString& nouveauNom);
    void loadSession();

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
        // Gestion audio de l'éléve
            void on_muteButton_clicked();
            void on_demuteButton_clicked();
            void on_desactiverSonButton_clicked();
            void on_activerSonButton_clicked();
        // Communiquer (ecris/oral) avec l'élève
            void on_Communication_clicked();
            void on_envoyerMessagePersonne_clicked();
            void on_envoyerMessageGroupe_clicked();
        // Tableau de creation de groupe (+ gestion de l'élève)
            // Creation de groupe
                void on_creerGroupeButton_clicked();
                void on_nomGroupeLineEdit_returnPressed();
            // Mise a jour des données via la base de donnée
                void loadInformationTable();
                void on_nomEleveLineEdit_editingFinished();
            // Ajouter l'élève séléctionné au groupe
                void onClicked_itemBoutonAjouterGroupe(iconEleveGroup* eleve);
        // Fermeture de la page
            void on_annulerButton_clicked();

    // Page statut
        void on_StatutButton_clicked();

    // Mode de couleurs
        void on_modeClairButton_clicked();
        void on_modeSombreButton_clicked();

    void on_cacheButton_clicked();



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

    QTableWidget* TableauGroupe = nullptr;
    bool modeSombre = true;
    QTableWidget* StatutTableauGroupe ;

    QUdpSocket* udpSocketQCM;
    unsigned int portQCM = 5559;


};
#endif // MAINWINDOW_H
