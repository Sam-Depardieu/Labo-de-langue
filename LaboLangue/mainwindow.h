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

// Inclusions projet
#include "iconEleveGroup.h"
#include "AudioCommunicator.h"
#include "qcm.h"
#include "choixsession.h"
#include "gestionSession.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // === Accesseurs publics ===
    QString getSessionFolder() const { return sessionFolder; }
    QString getSource() {return source;}
    QString* getNomProf() {return &nomProf;}
    QString* getDuree() {return &duree;}
    QString* getNomTypeActivite() {return &nomTypeActivite;}
    int getIdTypeActivite() {return idTypeActivite;}
    QString getNewName() {return newNameFolder;}
    QString getIpProf() {return ip;}
    gestionSession* getGestionSession() {return gestion_Session;}
    Professeur* getProf() {return prof;};

    void setNewNameFolder(QString newName) { newNameFolder = newName;}
    void setSource(QString newSource) { source = newSource; }
    void setNomEtudiantLineEdit(QString nom);
    void setIdTypeActivite(unsigned int newId) {idTypeActivite = newId;};
    void setIdProf(unsigned int newId) {idProf = newId;};
    void setIdClasse(unsigned int newId) {idClasse = newId;};
    bool getModeSombre() const { return modeSombre; }
    bool getMovable() const {return movable;};
    void afficherEtatEleves();
    void addHorizontalLayout(QVBoxLayout *layout, std::initializer_list<QWidget*> widgets);
    void editStatusButton(QPushButton *button, bool status);
    void showCheckIconOnGroup(iconEleveGroup *group);
    void updateEleveNom(iconEleveGroup* eleve, const QString& newName);
    void updateNomDansBDD(int idEleve, const QString& nouveauNom);


    // === Méthodes principales ===
    void continuerCreationSession();
    void toggleSettingEleve(iconEleveGroup *group, bool open);
    void updateCheckItemsVisibility();
    void mettreAJourEtatsAudioEleves();

    // === Données publiques élèves / session ===
    std::vector<iconEleveGroup*> listeRasp;
    std::vector<iconEleveGroup*> listeParticipant;
    std::vector<iconEleveGroup*> listeEditEleve;
    std::vector<int> listeEleveParticipant;
    iconEleveGroup* eleveActuellementParametre = nullptr;
    QMap<QString, std::vector<iconEleveGroup*>> listeGroup;
    QCM *qcm = nullptr;
    QMap<QString, QColor> couleursGroup;  // Clé : nom du groupe, Valeur : couleur
    void loadImagesFromDB();


    // === États de l’interface ===
    bool parametrageSession = false;
    bool selectionParticipants = false;
    bool selectAllParticipants = false;
    bool parametrageEleve = false;
    bool runningSession = false;
    bool interfaceQCMOpen = false;

    // === Audio & Réseau ===
    QUdpSocket* udpSocketPATH = nullptr;
    unsigned int portPATH = 5559;
    QUdpSocket* udpSocketQCM = nullptr;
    unsigned int portQCM = 5559;
    QUdpSocket* udpSocketAppel = nullptr;
    unsigned int portAppel = 5557;
    QMap<QString, int> portsAudioGroupes; // Groupe → port (ex: "Groupe A" → 6000)
    int prochainPortAudioDisponible = 6000;

    Ui::MainWindow *ui;
    QTableWidget* TableauGroupe = nullptr;
    QTableWidget* StatutTableauGroupe = nullptr;
    QGraphicsScene *scene = nullptr;
    QGraphicsPixmapItem *item = nullptr;

    bool clignotementEtat = false;
    QTimer *chronoTimer;
    QTime remainingTime;
    QTimer* clignotementTimer;

private slots:
    // === Boutons principaux ===
    void on_PlanButton_clicked();
    void on_SessionButton_clicked();
    void on_CreationButton_clicked();
    void on_StatutButton_clicked();

    // === Gestion session ===
    void on_loadSession_clicked();
    void saveSessionData(bool isNewSession);
    void resetSession();
    void setupActivitiesComboBox();
    void setupClassesComboBox();
    void on_ChoixActivite_currentIndexChanged(int index);

    // === Sélection élèves ===
    void on_selectAll_clicked();
    void on_selectManuel_clicked();
    void on_validButton_clicked();
    void on_SourceButton_clicked();
    void on_delButton_clicked();
    void on_echapButton_clicked();

    // === Paramétrage élèves ===
    void on_casqueSonButton_clicked();
    void on_microSonButton_clicked();
    void on_Communication_clicked();
    void on_envoyerMessagePersonne_clicked();
    void on_envoyerMessageGroupe_clicked();
    void on_creerGroupeButton_clicked();
    void on_nomGroupeLineEdit_returnPressed();
    void on_nomEleveLineEdit_editingFinished();
    void on_pauseButton_clicked();
    void onClicked_itemBoutonAjouterGroupe(iconEleveGroup* eleve);

    // === Apparence ===
    void on_modeClairButton_clicked();
    void on_modeSombreButton_clicked();
    void on_cacheButton_clicked();

    // === Autres fonctionnalités ===
    void majStatusQCM();
    void changeNameTable(QTableWidgetItem* item);
    void loadInformationTable();
    void on_redemarrerButton_clicked();
    void on_AideButton_clicked();
    void on_cadenaCloseButton_clicked();

    void on_cadenaOpenButton_clicked();

    bool errorBdd(QSqlQuery& query);

    QList<QColor> listeCouleursDisponibles();
    QColor couleurDisponible() ;

    void on_reloadButton_clicked();

    void on_LectureStatutButton_clicked();

    void on_PauseStatutButton_clicked();

    void on_lectureButton_clicked();

private:
    // === Interface graphique ===

    // === Base de données ===
    QSqlDatabase db;
    QString source;
    QString sessionFolder;
    QString newNameFolder;
    QString nomProf;
    int idProf = -1;
    int idClasse = -1;
    int idTypeActivite = -1;
    QString duree = "00:00";
    QString nomTypeActivite;
    QString ip;

    // === Divers ===
    Professeur *prof = nullptr;
    bool modeSombre = true;
    bool movable = false;


    // === Méthodes utilitaires ===
    bool connectToDatabase();
    void onImageGroupDoubleClicked();
    void onClicked_itemBoutonSupprimerGroupe(iconEleveGroup* eleve);
    void mettreAJourAudioPourGroupe(const QString& groupe);
    void changerStatusMicro (bool statusMicro);
    void changerStatusCasque (bool statusCasque);
    void updateChronoLabel();
    void faireClignoterLabel();

    void demandeAide();

    gestionSession *gestion_Session;
};

#endif // MAINWINDOW_H
