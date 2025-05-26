/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *LigneHaut;
    QPushButton *PlanButton;
    QPushButton *PresenceButton;
    QPushButton *SessionButton;
    QPushButton *AppelButton;
    QPushButton *StatutButton;
    QPushButton *AideButton;
    QPushButton *EnregistrementButton;
    QGraphicsView *PlanClasse;
    QGraphicsView *ParametrageSession;
    QLabel *NomProfLabel;
    QLineEdit *NomProfLineEdit;
    QLabel *ChoixActLabel;
    QComboBox *ChoixActivite;
    QLabel *DureeLabel;
    QTimeEdit *DureeActivite;
    QLabel *ConsigneLabel;
    QTextEdit *ConsigneTextEdit;
    QLabel *ClasseLabel;
    QComboBox *ChoixClasse;
    QLabel *ParticipantsLabel;
    QPushButton *selectAll;
    QPushButton *selectManuel;
    QPushButton *validButton;
    QPushButton *echapButton;
    QPushButton *delButton;
    QLabel *errorLabel;
    QLabel *SourceLabel;
    QPushButton *SourceButton;
    QLabel *NameSourceLabel;
    QPushButton *loadSession;
    QGraphicsView *ParametrageEleve;
    QPushButton *CreationButton;
    QPushButton *microSonButton;
    QPushButton *casqueSonButton;
    QLabel *nomGroupeLabel;
    QPushButton *pauseButton;
    QPushButton *creerGroupeButton;
    QLabel *alignerTableau;
    QTableWidget *TableauGroupe;
    QLineEdit *nomEleveLineEdit;
    QPushButton *Communication;
    QPushButton *envoyerMessagePersonne;
    QTextEdit *envoyerMessageTextEdit;
    QPushButton *envoyerMessageGroupe;
    QPushButton *modeSombreButton;
    QPushButton *modeClairButton;
    QGraphicsView *PageStatut;
    QLabel *alignerTableau_2;
    QTableWidget *StatutTableauGroupe;
    QPushButton *cacheButton;
    QLabel *nomCreationGroupeLabel;
    QLineEdit *nomGroupeLineEdit;
    QPushButton *AppelerButton;
    QPushButton *redemarrerButton;
    QPushButton *cadenaOpenButton;
    QPushButton *cadenaCloseButton;
    QLabel *chronoLabel;
    QPushButton *reloadButton;
    QPushButton *PauseStatutButton;
    QPushButton *LectureStatutButton;
    QLabel *RunningActivite;
    QPushButton *lectureButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1300, 760);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #7D7D7D;\n"
"color: black;\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        LigneHaut = new QPushButton(centralwidget);
        LigneHaut->setObjectName("LigneHaut");
        LigneHaut->setEnabled(false);
        LigneHaut->setGeometry(QRect(-40, -40, 1641, 101));
        LigneHaut->setAutoFillBackground(false);
        LigneHaut->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 151, 178);"));
        PlanButton = new QPushButton(centralwidget);
        PlanButton->setObjectName("PlanButton");
        PlanButton->setGeometry(QRect(250, 10, 91, 41));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PlanButton->sizePolicy().hasHeightForWidth());
        PlanButton->setSizePolicy(sizePolicy);
        PlanButton->setStyleSheet(QString::fromUtf8("background-color: black;\n"
"font: 9pt \"Segoe UI\";\n"
"color: white;\n"
"border: 1px solid white;\n"
"border-radius: 10px;"));
        PresenceButton = new QPushButton(centralwidget);
        PresenceButton->setObjectName("PresenceButton");
        PresenceButton->setGeometry(QRect(350, 10, 91, 41));
        sizePolicy.setHeightForWidth(PresenceButton->sizePolicy().hasHeightForWidth());
        PresenceButton->setSizePolicy(sizePolicy);
        PresenceButton->setStyleSheet(QString::fromUtf8("background-color: black;\n"
"font: 9pt \"Segoe UI\";\n"
"color: white;\n"
"border: 1px solid white;\n"
"border-radius: 10px;"));
        SessionButton = new QPushButton(centralwidget);
        SessionButton->setObjectName("SessionButton");
        SessionButton->setGeometry(QRect(450, 10, 91, 41));
        sizePolicy.setHeightForWidth(SessionButton->sizePolicy().hasHeightForWidth());
        SessionButton->setSizePolicy(sizePolicy);
        SessionButton->setStyleSheet(QString::fromUtf8("background-color: black;\n"
"font: 9pt \"Segoe UI\";\n"
"color: white;\n"
"border: 1px solid white;\n"
"border-radius: 10px;"));
        AppelButton = new QPushButton(centralwidget);
        AppelButton->setObjectName("AppelButton");
        AppelButton->setGeometry(QRect(650, 10, 91, 41));
        sizePolicy.setHeightForWidth(AppelButton->sizePolicy().hasHeightForWidth());
        AppelButton->setSizePolicy(sizePolicy);
        AppelButton->setAutoFillBackground(false);
        AppelButton->setStyleSheet(QString::fromUtf8("background-color: black;\n"
"font: 9pt \"Segoe UI\";\n"
"color: white;\n"
"border: 1px solid white;\n"
"border-radius: 10px;"));
        StatutButton = new QPushButton(centralwidget);
        StatutButton->setObjectName("StatutButton");
        StatutButton->setGeometry(QRect(750, 10, 91, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(StatutButton->sizePolicy().hasHeightForWidth());
        StatutButton->setSizePolicy(sizePolicy1);
        StatutButton->setAutoFillBackground(false);
        StatutButton->setStyleSheet(QString::fromUtf8("background-color: black;\n"
"font: 9pt \"Segoe UI\";\n"
"color: white;\n"
"border: 1px solid white;\n"
"border-radius: 10px;"));
        AideButton = new QPushButton(centralwidget);
        AideButton->setObjectName("AideButton");
        AideButton->setGeometry(QRect(850, 10, 91, 41));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(5);
        sizePolicy2.setVerticalStretch(5);
        sizePolicy2.setHeightForWidth(AideButton->sizePolicy().hasHeightForWidth());
        AideButton->setSizePolicy(sizePolicy2);
        AideButton->setAutoFillBackground(false);
        AideButton->setStyleSheet(QString::fromUtf8("background-color: black;\n"
"font: 9pt \"Segoe UI\";\n"
"color: white;\n"
"border: 1px solid white;\n"
"border-radius: 10px;"));
        EnregistrementButton = new QPushButton(centralwidget);
        EnregistrementButton->setObjectName("EnregistrementButton");
        EnregistrementButton->setGeometry(QRect(550, 10, 91, 41));
        sizePolicy.setHeightForWidth(EnregistrementButton->sizePolicy().hasHeightForWidth());
        EnregistrementButton->setSizePolicy(sizePolicy);
        EnregistrementButton->setStyleSheet(QString::fromUtf8("background-color: black;\n"
"font: 9pt \"Segoe UI\";\n"
"color: white;\n"
"border: 1px solid white;\n"
"border-radius: 10px;"));
        PlanClasse = new QGraphicsView(centralwidget);
        PlanClasse->setObjectName("PlanClasse");
        PlanClasse->setGeometry(QRect(10, 70, 631, 681));
        PlanClasse->setStyleSheet(QString::fromUtf8("background-color: white;"));
        ParametrageSession = new QGraphicsView(centralwidget);
        ParametrageSession->setObjectName("ParametrageSession");
        ParametrageSession->setEnabled(true);
        ParametrageSession->setGeometry(QRect(660, 70, 631, 681));
        ParametrageSession->setStyleSheet(QString::fromUtf8("background-color: white;"));
        NomProfLabel = new QLabel(centralwidget);
        NomProfLabel->setObjectName("NomProfLabel");
        NomProfLabel->setEnabled(true);
        NomProfLabel->setGeometry(QRect(880, 90, 81, 21));
        NomProfLabel->setStyleSheet(QString::fromUtf8(""));
        NomProfLineEdit = new QLineEdit(centralwidget);
        NomProfLineEdit->setObjectName("NomProfLineEdit");
        NomProfLineEdit->setEnabled(true);
        NomProfLineEdit->setGeometry(QRect(980, 90, 221, 21));
        ChoixActLabel = new QLabel(centralwidget);
        ChoixActLabel->setObjectName("ChoixActLabel");
        ChoixActLabel->setEnabled(true);
        ChoixActLabel->setGeometry(QRect(880, 130, 81, 21));
        ChoixActLabel->setStyleSheet(QString::fromUtf8(""));
        ChoixActivite = new QComboBox(centralwidget);
        ChoixActivite->setObjectName("ChoixActivite");
        ChoixActivite->setEnabled(true);
        ChoixActivite->setGeometry(QRect(980, 130, 221, 21));
        ChoixActivite->setStyleSheet(QString::fromUtf8(""));
        DureeLabel = new QLabel(centralwidget);
        DureeLabel->setObjectName("DureeLabel");
        DureeLabel->setEnabled(true);
        DureeLabel->setGeometry(QRect(880, 170, 81, 21));
        DureeLabel->setStyleSheet(QString::fromUtf8(""));
        DureeActivite = new QTimeEdit(centralwidget);
        DureeActivite->setObjectName("DureeActivite");
        DureeActivite->setEnabled(true);
        DureeActivite->setGeometry(QRect(980, 170, 221, 22));
        ConsigneLabel = new QLabel(centralwidget);
        ConsigneLabel->setObjectName("ConsigneLabel");
        ConsigneLabel->setEnabled(true);
        ConsigneLabel->setGeometry(QRect(880, 330, 81, 21));
        ConsigneLabel->setStyleSheet(QString::fromUtf8(""));
        ConsigneTextEdit = new QTextEdit(centralwidget);
        ConsigneTextEdit->setObjectName("ConsigneTextEdit");
        ConsigneTextEdit->setEnabled(true);
        ConsigneTextEdit->setGeometry(QRect(980, 330, 221, 31));
        ClasseLabel = new QLabel(centralwidget);
        ClasseLabel->setObjectName("ClasseLabel");
        ClasseLabel->setEnabled(true);
        ClasseLabel->setGeometry(QRect(880, 210, 81, 21));
        ClasseLabel->setStyleSheet(QString::fromUtf8(""));
        ChoixClasse = new QComboBox(centralwidget);
        ChoixClasse->setObjectName("ChoixClasse");
        ChoixClasse->setEnabled(true);
        ChoixClasse->setGeometry(QRect(980, 210, 221, 21));
        ParticipantsLabel = new QLabel(centralwidget);
        ParticipantsLabel->setObjectName("ParticipantsLabel");
        ParticipantsLabel->setEnabled(true);
        ParticipantsLabel->setGeometry(QRect(880, 250, 81, 21));
        ParticipantsLabel->setStyleSheet(QString::fromUtf8(""));
        selectAll = new QPushButton(centralwidget);
        selectAll->setObjectName("selectAll");
        selectAll->setEnabled(true);
        selectAll->setGeometry(QRect(980, 250, 101, 24));
        selectAll->setStyleSheet(QString::fromUtf8("background-color: gray;"));
        selectManuel = new QPushButton(centralwidget);
        selectManuel->setObjectName("selectManuel");
        selectManuel->setEnabled(true);
        selectManuel->setGeometry(QRect(1100, 250, 101, 24));
        selectManuel->setStyleSheet(QString::fromUtf8("background-color: gray;"));
        validButton = new QPushButton(centralwidget);
        validButton->setObjectName("validButton");
        validButton->setEnabled(true);
        validButton->setGeometry(QRect(1140, 400, 75, 24));
        validButton->setStyleSheet(QString::fromUtf8("background-color: green;"));
        echapButton = new QPushButton(centralwidget);
        echapButton->setObjectName("echapButton");
        echapButton->setEnabled(true);
        echapButton->setGeometry(QRect(1010, 400, 75, 24));
        echapButton->setStyleSheet(QString::fromUtf8("background-color: red;"));
        delButton = new QPushButton(centralwidget);
        delButton->setObjectName("delButton");
        delButton->setEnabled(true);
        delButton->setGeometry(QRect(880, 400, 75, 24));
        delButton->setStyleSheet(QString::fromUtf8("background-color: red;"));
        errorLabel = new QLabel(centralwidget);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setEnabled(true);
        errorLabel->setGeometry(QRect(880, 370, 321, 20));
        errorLabel->setStyleSheet(QString::fromUtf8("color: red;"));
        SourceLabel = new QLabel(centralwidget);
        SourceLabel->setObjectName("SourceLabel");
        SourceLabel->setEnabled(true);
        SourceLabel->setGeometry(QRect(880, 290, 81, 21));
        SourceLabel->setStyleSheet(QString::fromUtf8(""));
        SourceButton = new QPushButton(centralwidget);
        SourceButton->setObjectName("SourceButton");
        SourceButton->setEnabled(true);
        SourceButton->setGeometry(QRect(1110, 290, 91, 24));
        SourceButton->setStyleSheet(QString::fromUtf8("background-color: gray;"));
        NameSourceLabel = new QLabel(centralwidget);
        NameSourceLabel->setObjectName("NameSourceLabel");
        NameSourceLabel->setEnabled(true);
        NameSourceLabel->setGeometry(QRect(980, 290, 81, 21));
        NameSourceLabel->setStyleSheet(QString::fromUtf8(""));
        loadSession = new QPushButton(centralwidget);
        loadSession->setObjectName("loadSession");
        loadSession->setGeometry(QRect(1000, 80, 131, 24));
        loadSession->setStyleSheet(QString::fromUtf8("background-color: gray;"));
        ParametrageEleve = new QGraphicsView(centralwidget);
        ParametrageEleve->setObjectName("ParametrageEleve");
        ParametrageEleve->setGeometry(QRect(660, 70, 631, 681));
        ParametrageEleve->setStyleSheet(QString::fromUtf8("background-color: white;"));
        CreationButton = new QPushButton(centralwidget);
        CreationButton->setObjectName("CreationButton");
        CreationButton->setGeometry(QRect(950, 10, 91, 41));
        sizePolicy.setHeightForWidth(CreationButton->sizePolicy().hasHeightForWidth());
        CreationButton->setSizePolicy(sizePolicy);
        CreationButton->setStyleSheet(QString::fromUtf8("background-color: black;\n"
"font: 9pt \"Segoe UI\";\n"
"color: white;\n"
"border: 1px solid white;\n"
"border-radius: 10px;"));
        microSonButton = new QPushButton(centralwidget);
        microSonButton->setObjectName("microSonButton");
        microSonButton->setGeometry(QRect(1000, 150, 201, 24));
        casqueSonButton = new QPushButton(centralwidget);
        casqueSonButton->setObjectName("casqueSonButton");
        casqueSonButton->setGeometry(QRect(760, 150, 201, 24));
        nomGroupeLabel = new QLabel(centralwidget);
        nomGroupeLabel->setObjectName("nomGroupeLabel");
        nomGroupeLabel->setGeometry(QRect(680, 90, 101, 41));
        pauseButton = new QPushButton(centralwidget);
        pauseButton->setObjectName("pauseButton");
        pauseButton->setGeometry(QRect(900, 230, 171, 24));
        creerGroupeButton = new QPushButton(centralwidget);
        creerGroupeButton->setObjectName("creerGroupeButton");
        creerGroupeButton->setGeometry(QRect(680, 230, 201, 24));
        alignerTableau = new QLabel(centralwidget);
        alignerTableau->setObjectName("alignerTableau");
        alignerTableau->setGeometry(QRect(700, 380, 31, 291));
        TableauGroupe = new QTableWidget(centralwidget);
        TableauGroupe->setObjectName("TableauGroupe");
        TableauGroupe->setGeometry(QRect(750, 380, 511, 291));
        TableauGroupe->setStyleSheet(QString::fromUtf8(""));
        nomEleveLineEdit = new QLineEdit(centralwidget);
        nomEleveLineEdit->setObjectName("nomEleveLineEdit");
        nomEleveLineEdit->setGeometry(QRect(800, 90, 281, 41));
        Communication = new QPushButton(centralwidget);
        Communication->setObjectName("Communication");
        Communication->setGeometry(QRect(1110, 90, 161, 41));
        envoyerMessagePersonne = new QPushButton(centralwidget);
        envoyerMessagePersonne->setObjectName("envoyerMessagePersonne");
        envoyerMessagePersonne->setGeometry(QRect(1080, 510, 191, 41));
        envoyerMessageTextEdit = new QTextEdit(centralwidget);
        envoyerMessageTextEdit->setObjectName("envoyerMessageTextEdit");
        envoyerMessageTextEdit->setGeometry(QRect(750, 380, 331, 291));
        envoyerMessageGroupe = new QPushButton(centralwidget);
        envoyerMessageGroupe->setObjectName("envoyerMessageGroupe");
        envoyerMessageGroupe->setGeometry(QRect(1080, 440, 191, 41));
        modeSombreButton = new QPushButton(centralwidget);
        modeSombreButton->setObjectName("modeSombreButton");
        modeSombreButton->setGeometry(QRect(1230, 0, 61, 61));
        modeSombreButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: none;\n"
""));
        modeClairButton = new QPushButton(centralwidget);
        modeClairButton->setObjectName("modeClairButton");
        modeClairButton->setGeometry(QRect(1230, 0, 61, 61));
        modeClairButton->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: none;\n"
""));
        PageStatut = new QGraphicsView(centralwidget);
        PageStatut->setObjectName("PageStatut");
        PageStatut->setGeometry(QRect(660, 70, 631, 681));
        PageStatut->setStyleSheet(QString::fromUtf8("background-color: white;"));
        alignerTableau_2 = new QLabel(centralwidget);
        alignerTableau_2->setObjectName("alignerTableau_2");
        alignerTableau_2->setGeometry(QRect(700, 110, 31, 501));
        StatutTableauGroupe = new QTableWidget(centralwidget);
        StatutTableauGroupe->setObjectName("StatutTableauGroupe");
        StatutTableauGroupe->setGeometry(QRect(770, 110, 441, 501));
        StatutTableauGroupe->setStyleSheet(QString::fromUtf8(""));
        cacheButton = new QPushButton(centralwidget);
        cacheButton->setObjectName("cacheButton");
        cacheButton->setGeometry(QRect(0, 740, 21, 24));
        cacheButton->setStyleSheet(QString::fromUtf8("background-color:transparent;\n"
"border:none;\n"
""));
        nomCreationGroupeLabel = new QLabel(centralwidget);
        nomCreationGroupeLabel->setObjectName("nomCreationGroupeLabel");
        nomCreationGroupeLabel->setGeometry(QRect(1350, 310, 101, 41));
        nomGroupeLineEdit = new QLineEdit(centralwidget);
        nomGroupeLineEdit->setObjectName("nomGroupeLineEdit");
        nomGroupeLineEdit->setGeometry(QRect(260, 320, 281, 41));
        AppelerButton = new QPushButton(centralwidget);
        AppelerButton->setObjectName("AppelerButton");
        AppelerButton->setGeometry(QRect(680, 310, 171, 24));
        redemarrerButton = new QPushButton(centralwidget);
        redemarrerButton->setObjectName("redemarrerButton");
        redemarrerButton->setGeometry(QRect(1100, 280, 171, 24));
        cadenaOpenButton = new QPushButton(centralwidget);
        cadenaOpenButton->setObjectName("cadenaOpenButton");
        cadenaOpenButton->setGeometry(QRect(610, 80, 20, 20));
        cadenaOpenButton->setStyleSheet(QString::fromUtf8("background-color: transparent; border: none;"));
        cadenaCloseButton = new QPushButton(centralwidget);
        cadenaCloseButton->setObjectName("cadenaCloseButton");
        cadenaCloseButton->setGeometry(QRect(610, 80, 20, 20));
        cadenaCloseButton->setStyleSheet(QString::fromUtf8("background-color: transparent; border: none;"));
        chronoLabel = new QLabel(centralwidget);
        chronoLabel->setObjectName("chronoLabel");
        chronoLabel->setGeometry(QRect(10, 10, 111, 45));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setBold(true);
        chronoLabel->setFont(font);
        chronoLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: #0097a7; /* m\303\252me ton bleu-vert que ta barre */\n"
"    color: white;\n"
"    border: 2px solid white;\n"
"    border-radius: 8px;\n"
"    font-family: \"Segoe UI\", \"Arial\", sans-serif;\n"
"    font-weight: bold;\n"
"    font-size: 28px;\n"
"    padding: 5px 15px;\n"
"    qproperty-alignment: 'AlignCenter';\n"
"}\n"
""));
        reloadButton = new QPushButton(centralwidget);
        reloadButton->setObjectName("reloadButton");
        reloadButton->setGeometry(QRect(610, 110, 20, 20));
        reloadButton->setStyleSheet(QString::fromUtf8("background-color: transparent; border: none;"));
        PauseStatutButton = new QPushButton(centralwidget);
        PauseStatutButton->setObjectName("PauseStatutButton");
        PauseStatutButton->setGeometry(QRect(710, 150, 171, 24));
        PauseStatutButton->setStyleSheet(QString::fromUtf8("background-color: red;"));
        LectureStatutButton = new QPushButton(centralwidget);
        LectureStatutButton->setObjectName("LectureStatutButton");
        LectureStatutButton->setGeometry(QRect(990, 150, 171, 24));
        LectureStatutButton->setStyleSheet(QString::fromUtf8("background-color: green;"));
        RunningActivite = new QLabel(centralwidget);
        RunningActivite->setObjectName("RunningActivite");
        RunningActivite->setGeometry(QRect(690, 80, 131, 16));
        lectureButton = new QPushButton(centralwidget);
        lectureButton->setObjectName("lectureButton");
        lectureButton->setGeometry(QRect(1100, 230, 171, 24));
        MainWindow->setCentralWidget(centralwidget);
        AppelerButton->raise();
        redemarrerButton->raise();
        LectureStatutButton->raise();
        PauseStatutButton->raise();
        RunningActivite->raise();
        ParametrageSession->raise();
        nomGroupeLineEdit->raise();
        nomCreationGroupeLabel->raise();
        alignerTableau_2->raise();
        StatutTableauGroupe->raise();
        LigneHaut->raise();
        PlanButton->raise();
        PresenceButton->raise();
        SessionButton->raise();
        AppelButton->raise();
        StatutButton->raise();
        AideButton->raise();
        EnregistrementButton->raise();
        PlanClasse->raise();
        NomProfLabel->raise();
        NomProfLineEdit->raise();
        ChoixActLabel->raise();
        ChoixActivite->raise();
        DureeLabel->raise();
        DureeActivite->raise();
        ConsigneLabel->raise();
        ConsigneTextEdit->raise();
        ClasseLabel->raise();
        ChoixClasse->raise();
        ParticipantsLabel->raise();
        selectAll->raise();
        selectManuel->raise();
        validButton->raise();
        echapButton->raise();
        delButton->raise();
        errorLabel->raise();
        SourceLabel->raise();
        SourceButton->raise();
        NameSourceLabel->raise();
        loadSession->raise();
        ParametrageEleve->raise();
        CreationButton->raise();
        microSonButton->raise();
        casqueSonButton->raise();
        nomGroupeLabel->raise();
        pauseButton->raise();
        creerGroupeButton->raise();
        alignerTableau->raise();
        TableauGroupe->raise();
        nomEleveLineEdit->raise();
        Communication->raise();
        envoyerMessagePersonne->raise();
        envoyerMessageTextEdit->raise();
        envoyerMessageGroupe->raise();
        modeSombreButton->raise();
        modeClairButton->raise();
        PageStatut->raise();
        cacheButton->raise();
        cadenaOpenButton->raise();
        cadenaCloseButton->raise();
        chronoLabel->raise();
        reloadButton->raise();
        lectureButton->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        LigneHaut->setText(QString());
        PlanButton->setText(QCoreApplication::translate("MainWindow", "Plan de classe", nullptr));
        PresenceButton->setText(QCoreApplication::translate("MainWindow", "Pr\303\251sence", nullptr));
        SessionButton->setText(QCoreApplication::translate("MainWindow", "Nouv. Session", nullptr));
        AppelButton->setText(QCoreApplication::translate("MainWindow", "Appeler tous", nullptr));
        StatutButton->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        AideButton->setText(QCoreApplication::translate("MainWindow", "Aide", nullptr));
        EnregistrementButton->setText(QCoreApplication::translate("MainWindow", "Enregistrement", nullptr));
        NomProfLabel->setText(QCoreApplication::translate("MainWindow", "Votre Nom :", nullptr));
        ChoixActLabel->setText(QCoreApplication::translate("MainWindow", "Type activit\303\251 :", nullptr));
        DureeLabel->setText(QCoreApplication::translate("MainWindow", "Dur\303\251e activit\303\251 :", nullptr));
        DureeActivite->setDisplayFormat(QCoreApplication::translate("MainWindow", "mm:ss", nullptr));
        ConsigneLabel->setText(QCoreApplication::translate("MainWindow", "Consigne :", nullptr));
        ClasseLabel->setText(QCoreApplication::translate("MainWindow", "Classe :", nullptr));
        ParticipantsLabel->setText(QCoreApplication::translate("MainWindow", "Participants :", nullptr));
        selectAll->setText(QCoreApplication::translate("MainWindow", "S\303\251lectionner tous", nullptr));
        selectManuel->setText(QCoreApplication::translate("MainWindow", "Personnaliser", nullptr));
        validButton->setText(QCoreApplication::translate("MainWindow", "Valider", nullptr));
        echapButton->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        delButton->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        errorLabel->setText(QString());
        SourceLabel->setText(QCoreApplication::translate("MainWindow", "Source :", nullptr));
        SourceButton->setText(QCoreApplication::translate("MainWindow", "Selection fichier", nullptr));
        NameSourceLabel->setText(QString());
        loadSession->setText(QCoreApplication::translate("MainWindow", "Charger une session", nullptr));
        CreationButton->setText(QCoreApplication::translate("MainWindow", "Creation", nullptr));
        microSonButton->setText(QCoreApplication::translate("MainWindow", "Couper le micro", nullptr));
        casqueSonButton->setText(QCoreApplication::translate("MainWindow", "Couper le son", nullptr));
        nomGroupeLabel->setText(QCoreApplication::translate("MainWindow", "Poste s\303\251l\303\251ction\303\251 :", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        creerGroupeButton->setText(QCoreApplication::translate("MainWindow", "Creer un groupe", nullptr));
        alignerTableau->setText(QString());
        Communication->setText(QCoreApplication::translate("MainWindow", "Communication", nullptr));
        envoyerMessagePersonne->setText(QCoreApplication::translate("MainWindow", "Envoyer le message (\303\240 la personne)", nullptr));
        envoyerMessageTextEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        envoyerMessageGroupe->setText(QCoreApplication::translate("MainWindow", "Envoyer le message (au groupe)", nullptr));
        modeSombreButton->setText(QString());
        modeClairButton->setText(QString());
        alignerTableau_2->setText(QString());
        cacheButton->setText(QString());
        nomCreationGroupeLabel->setText(QCoreApplication::translate("MainWindow", "Nom du groupe :", nullptr));
        AppelerButton->setText(QCoreApplication::translate("MainWindow", "Appeler", nullptr));
        redemarrerButton->setText(QCoreApplication::translate("MainWindow", "Red\303\251marrer l'appareil", nullptr));
        cadenaOpenButton->setText(QString());
        cadenaCloseButton->setText(QString());
        chronoLabel->setText(QCoreApplication::translate("MainWindow", "00:00", nullptr));
        reloadButton->setText(QString());
        PauseStatutButton->setText(QString());
        LectureStatutButton->setText(QString());
        RunningActivite->setText(QCoreApplication::translate("MainWindow", "Activit\303\251e en cours :", nullptr));
        lectureButton->setText(QCoreApplication::translate("MainWindow", "Lecture", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
