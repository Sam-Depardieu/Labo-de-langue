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
    QPushButton *LigneBas;
    QPushButton *LigneHaut;
    QPushButton *PlanButton;
    QPushButton *PresenceButton;
    QPushButton *SessionButton;
    QPushButton *AppelButton;
    QPushButton *StatutButton;
    QPushButton *AideButton;
    QPushButton *EnregistrementButton;
    QGraphicsView *PlanClasse;
    QGraphicsView *Parametrage1;
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

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 480);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #7D7D7D;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        LigneBas = new QPushButton(centralwidget);
        LigneBas->setObjectName("LigneBas");
        LigneBas->setEnabled(false);
        LigneBas->setGeometry(QRect(-10, 440, 821, 51));
        LigneBas->setAutoFillBackground(false);
        LigneBas->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 151, 178);"));
        LigneHaut = new QPushButton(centralwidget);
        LigneHaut->setObjectName("LigneHaut");
        LigneHaut->setEnabled(false);
        LigneHaut->setGeometry(QRect(0, 0, 821, 61));
        LigneHaut->setAutoFillBackground(false);
        LigneHaut->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 151, 178);"));
        PlanButton = new QPushButton(centralwidget);
        PlanButton->setObjectName("PlanButton");
        PlanButton->setGeometry(QRect(100, 10, 91, 41));
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
        PresenceButton->setGeometry(QRect(200, 10, 91, 41));
        sizePolicy.setHeightForWidth(PresenceButton->sizePolicy().hasHeightForWidth());
        PresenceButton->setSizePolicy(sizePolicy);
        PresenceButton->setStyleSheet(QString::fromUtf8("background-color: black;\n"
"font: 9pt \"Segoe UI\";\n"
"color: white;\n"
"border: 1px solid white;\n"
"border-radius: 10px;"));
        SessionButton = new QPushButton(centralwidget);
        SessionButton->setObjectName("SessionButton");
        SessionButton->setGeometry(QRect(300, 10, 91, 41));
        sizePolicy.setHeightForWidth(SessionButton->sizePolicy().hasHeightForWidth());
        SessionButton->setSizePolicy(sizePolicy);
        SessionButton->setStyleSheet(QString::fromUtf8("background-color: black;\n"
"font: 9pt \"Segoe UI\";\n"
"color: white;\n"
"border: 1px solid white;\n"
"border-radius: 10px;"));
        AppelButton = new QPushButton(centralwidget);
        AppelButton->setObjectName("AppelButton");
        AppelButton->setGeometry(QRect(500, 10, 91, 41));
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
        StatutButton->setGeometry(QRect(600, 10, 91, 41));
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
        AideButton->setGeometry(QRect(700, 10, 91, 41));
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
        EnregistrementButton->setGeometry(QRect(400, 10, 91, 41));
        sizePolicy.setHeightForWidth(EnregistrementButton->sizePolicy().hasHeightForWidth());
        EnregistrementButton->setSizePolicy(sizePolicy);
        EnregistrementButton->setStyleSheet(QString::fromUtf8("background-color: black;\n"
"font: 9pt \"Segoe UI\";\n"
"color: white;\n"
"border: 1px solid white;\n"
"border-radius: 10px;"));
        PlanClasse = new QGraphicsView(centralwidget);
        PlanClasse->setObjectName("PlanClasse");
        PlanClasse->setGeometry(QRect(10, 70, 381, 361));
        PlanClasse->setStyleSheet(QString::fromUtf8("background-color: white;"));
        Parametrage1 = new QGraphicsView(centralwidget);
        Parametrage1->setObjectName("Parametrage1");
        Parametrage1->setGeometry(QRect(410, 70, 381, 361));
        Parametrage1->setStyleSheet(QString::fromUtf8("background-color: white;"));
        NameLabel = new QLabel(centralwidget);
        NameLabel->setObjectName("NameLabel");
        NameLabel->setGeometry(QRect(430, 90, 81, 21));
        NameLabel->setStyleSheet(QString::fromUtf8(""));
        NameLineEdit = new QLineEdit(centralwidget);
        NameLineEdit->setObjectName("NameLineEdit");
        NameLineEdit->setGeometry(QRect(530, 90, 221, 21));
        ChoixActLabel = new QLabel(centralwidget);
        ChoixActLabel->setObjectName("ChoixActLabel");
        ChoixActLabel->setGeometry(QRect(430, 130, 81, 21));
        ChoixActLabel->setStyleSheet(QString::fromUtf8(""));
        ChoixActivite = new QComboBox(centralwidget);
        ChoixActivite->setObjectName("ChoixActivite");
        ChoixActivite->setGeometry(QRect(530, 130, 221, 21));
        DureeLabel = new QLabel(centralwidget);
        DureeLabel->setObjectName("DureeLabel");
        DureeLabel->setGeometry(QRect(430, 170, 81, 21));
        DureeLabel->setStyleSheet(QString::fromUtf8(""));
        DureeActivite = new QTimeEdit(centralwidget);
        DureeActivite->setObjectName("DureeActivite");
        DureeActivite->setGeometry(QRect(530, 170, 221, 22));
        ConsigneLabel = new QLabel(centralwidget);
        ConsigneLabel->setObjectName("ConsigneLabel");
        ConsigneLabel->setGeometry(QRect(430, 290, 81, 21));
        ConsigneLabel->setStyleSheet(QString::fromUtf8(""));
        ConsigneTextEdit = new QTextEdit(centralwidget);
        ConsigneTextEdit->setObjectName("ConsigneTextEdit");
        ConsigneTextEdit->setGeometry(QRect(530, 290, 221, 31));
        ClasseLabel = new QLabel(centralwidget);
        ClasseLabel->setObjectName("ClasseLabel");
        ClasseLabel->setGeometry(QRect(430, 210, 81, 21));
        ClasseLabel->setStyleSheet(QString::fromUtf8(""));
        ChoixClasse = new QComboBox(centralwidget);
        ChoixClasse->setObjectName("ChoixClasse");
        ChoixClasse->setGeometry(QRect(530, 210, 221, 21));
        ParticipantsLabel = new QLabel(centralwidget);
        ParticipantsLabel->setObjectName("ParticipantsLabel");
        ParticipantsLabel->setGeometry(QRect(430, 250, 81, 21));
        ParticipantsLabel->setStyleSheet(QString::fromUtf8(""));
        selectAll = new QPushButton(centralwidget);
        selectAll->setObjectName("selectAll");
        selectAll->setGeometry(QRect(530, 250, 101, 24));
        selectManuel = new QPushButton(centralwidget);
        selectManuel->setObjectName("selectManuel");
        selectManuel->setGeometry(QRect(650, 250, 101, 24));
        validButton = new QPushButton(centralwidget);
        validButton->setObjectName("validButton");
        validButton->setGeometry(QRect(690, 400, 75, 24));
        validButton->setStyleSheet(QString::fromUtf8("background-color: green;"));
        echapButton = new QPushButton(centralwidget);
        echapButton->setObjectName("echapButton");
        echapButton->setGeometry(QRect(560, 400, 75, 24));
        echapButton->setStyleSheet(QString::fromUtf8("background-color: red;"));
        delButton = new QPushButton(centralwidget);
        delButton->setObjectName("delButton");
        delButton->setGeometry(QRect(430, 400, 75, 24));
        delButton->setStyleSheet(QString::fromUtf8("background-color: red;"));
        errorLabel = new QLabel(centralwidget);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setGeometry(QRect(430, 370, 321, 20));
        errorLabel->setStyleSheet(QString::fromUtf8("color: red;"));
        SourceLabel = new QLabel(centralwidget);
        SourceLabel->setObjectName("SourceLabel");
        SourceLabel->setGeometry(QRect(430, 340, 81, 21));
        SourceLabel->setStyleSheet(QString::fromUtf8(""));
        SourceButton = new QPushButton(centralwidget);
        SourceButton->setObjectName("SourceButton");
        SourceButton->setGeometry(QRect(590, 340, 91, 24));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        LigneBas->setText(QString());
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
