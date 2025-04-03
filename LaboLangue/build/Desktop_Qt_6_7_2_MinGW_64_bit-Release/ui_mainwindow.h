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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
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
    QLabel *NameLabel;
    QLineEdit *NameLineEdit;
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
    QPushButton *muteButton;
    QPushButton *demuteButton;
    QPushButton *desactiverSonButton;
    QPushButton *activerSonButton;
    QLabel *nomEleveLabel;
    QLabel *nomGroupeLabel;
    QPushButton *annulerButton;
    QPushButton *creerGroupeButton;
    QComboBox *ParticipantsComboBox;

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
        LigneHaut->setGeometry(QRect(0, 0, 1601, 61));
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
        NameLabel = new QLabel(centralwidget);
        NameLabel->setObjectName("NameLabel");
        NameLabel->setEnabled(true);
        NameLabel->setGeometry(QRect(880, 90, 81, 21));
        NameLabel->setStyleSheet(QString::fromUtf8(""));
        NameLineEdit = new QLineEdit(centralwidget);
        NameLineEdit->setObjectName("NameLineEdit");
        NameLineEdit->setEnabled(true);
        NameLineEdit->setGeometry(QRect(980, 90, 221, 21));
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
        muteButton = new QPushButton(centralwidget);
        muteButton->setObjectName("muteButton");
        muteButton->setGeometry(QRect(890, 150, 80, 24));
        demuteButton = new QPushButton(centralwidget);
        demuteButton->setObjectName("demuteButton");
        demuteButton->setGeometry(QRect(1000, 150, 80, 24));
        desactiverSonButton = new QPushButton(centralwidget);
        desactiverSonButton->setObjectName("desactiverSonButton");
        desactiverSonButton->setGeometry(QRect(850, 190, 121, 24));
        activerSonButton = new QPushButton(centralwidget);
        activerSonButton->setObjectName("activerSonButton");
        activerSonButton->setGeometry(QRect(1000, 190, 121, 24));
        nomEleveLabel = new QLabel(centralwidget);
        nomEleveLabel->setObjectName("nomEleveLabel");
        nomEleveLabel->setGeometry(QRect(1000, 90, 261, 41));
        nomGroupeLabel = new QLabel(centralwidget);
        nomGroupeLabel->setObjectName("nomGroupeLabel");
        nomGroupeLabel->setGeometry(QRect(680, 90, 291, 41));
        annulerButton = new QPushButton(centralwidget);
        annulerButton->setObjectName("annulerButton");
        annulerButton->setGeometry(QRect(1000, 230, 121, 24));
        creerGroupeButton = new QPushButton(centralwidget);
        creerGroupeButton->setObjectName("creerGroupeButton");
        creerGroupeButton->setGeometry(QRect(850, 230, 121, 24));
        ParticipantsComboBox = new QComboBox(centralwidget);
        ParticipantsComboBox->setObjectName("ParticipantsComboBox");
        ParticipantsComboBox->setEnabled(true);
        ParticipantsComboBox->setGeometry(QRect(720, 320, 121, 21));
        ParticipantsComboBox->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setCentralWidget(centralwidget);

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
        NameLabel->setText(QCoreApplication::translate("MainWindow", "Votre Nom :", nullptr));
        ChoixActLabel->setText(QCoreApplication::translate("MainWindow", "Type activit\303\251 :", nullptr));
        DureeLabel->setText(QCoreApplication::translate("MainWindow", "Dur\303\251e activit\303\251 :", nullptr));
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
        muteButton->setText(QCoreApplication::translate("MainWindow", "Mute", nullptr));
        demuteButton->setText(QCoreApplication::translate("MainWindow", "Demute", nullptr));
        desactiverSonButton->setText(QCoreApplication::translate("MainWindow", "Desactiver son", nullptr));
        activerSonButton->setText(QCoreApplication::translate("MainWindow", "Activer son", nullptr));
        nomEleveLabel->setText(QString());
        nomGroupeLabel->setText(QString());
        annulerButton->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        creerGroupeButton->setText(QCoreApplication::translate("MainWindow", "Creer un groupe", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
