#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMap>
#include <QPushButton>
#include <QSqlDatabase>
#include <QTableWidget>
#include <QUdpSocket>
#include <vector>
#include <initializer_list>

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

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // === Accès public ===
    QString getSessionFolder() { return sessionFolder; }
    void setSource(QString newSource) { source = newSource; }
    void setNomEtudiantLineEdit(QString nom);
    bool getModeSombre() { return modeSombre; }

    // === Méthodes principales ===
    void toggleSettingEleve(iconEleveGroup *group, bool open);
    void updateCheckItemsVisibility();
    void continuerCreationSession();

    // === Données liées aux élèves ===
    std::vector<iconEleveGroup*> listeRasp = {};
    std::vector<iconEleveGroup*> listeParticipant = {};
    std::vector<iconEleveGroup*> listeEditEleve = {};
    std::vector<int> listeEleveParticipant = {};
    iconEleveGroup* eleveActuellementParametre = nullptr;

    // === Données de session / activité ===
    QMap<QString, std::vector<iconEleveGroup*>> listeGroup = {};
    QCM *qcm = nullptr;
    int idTypeActivite = -1;

    // === États de l’interface ===
    bool parametrageSession = false;
    bool selectionParticipants = false;
    bool selectAllParticipants = false;
    bool parametrageEleve = false;
    bool runningSession = false;
    bool interfaceQCMOpen = false;

    Ui::MainWindow *ui;

private slots:
    // === Boutons principaux ===
    void on_PlanButton_clicked();
    void on_SessionButton_clicked();
    void on_CreationButton_clicked();
    void on_StatutButton_clicked();

    // === Gestion de session ===
    void on_loadSession_clicked();
    void loadSession();
    void saveSessionData(bool isNewSession);
    void resetSession();
    void setupActivitiesComboBox();
    void setupClassesComboBox();
    void on_ChoixActivite_currentIndexChanged(int index);

    // === Sélection des élèves ===
    void on_selectAll_clicked();
    void on_selectManuel_clicked();
    void on_validButton_clicked();
    void on_SourceButton_clicked();
    void on_delButton_clicked();
    void on_echapButton_clicked();

    // === Paramétrage de l’élève ===
    void on_muteButton_clicked();
    void on_demuteButton_clicked();
    void on_desactiverSonButton_clicked();
    void on_activerSonButton_clicked();
    void on_Communication_clicked();
    void on_envoyerMessagePersonne_clicked();
    void on_envoyerMessageGroupe_clicked();
    void on_creerGroupeButton_clicked();
    void on_nomGroupeLineEdit_returnPressed();
    void on_nomEleveLineEdit_editingFinished();
    void on_annulerButton_clicked();
    void onClicked_itemBoutonAjouterGroupe(iconEleveGroup* eleve);

    // === Mode sombre / clair ===
    void on_modeClairButton_clicked();
    void on_modeSombreButton_clicked();
    void on_cacheButton_clicked();

    // === Méthodes internes ===
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
    void loadInformationTable();

private:
    // === Interface graphique ===
    QGraphicsScene *scene = nullptr;
    QGraphicsPixmapItem *item = nullptr;
    QTableWidget* TableauGroupe = nullptr;
    QTableWidget* StatutTableauGroupe = nullptr;

    // === Base de données et session ===
    QSqlDatabase db;
    QString source;
    QString sessionFolder;
    QString nomProf;
    int idProf = -1;
    int idClasse = -1;
    int typeActivite = -1;
    QString duree;
    QString nomTypeActivite;

    // === Audio / Réseau ===
    QUdpSocket* udpSocketPATH = nullptr;
    unsigned int portPATH = 5559;
    QUdpSocket* udpSocketQCM = nullptr;
    unsigned int portQCM = 5559;

    // === Autres ===
    Professor *prof = nullptr;
    bool modeSombre = true;
};

#endif // MAINWINDOW_H
