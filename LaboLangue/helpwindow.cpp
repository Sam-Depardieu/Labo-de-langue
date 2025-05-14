#include "helpwindow.h"
#include "ui_helpwindow.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTableWidgetItem>
#include <QDebug>

HelpWindow::HelpWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::HelpWindow)

{
    ui->setupUi(this);
    setWindowTitle("Aide - Professeur");

    // Charger le fichier JSON
    chargerJSON();

    // Connexions des boutons
    connect(ui->mainWindowButton, &QPushButton::clicked, this, &HelpWindow::afficherFonctionnalitesMain);
    connect(ui->qcmButton, &QPushButton::clicked, this, &HelpWindow::afficherFonctionnalitesQCM);
    connect(ui->choixSessionButton, &QPushButton::clicked, this, &HelpWindow::afficherFonctionnalitesChoixSession);

    // Table setup
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({"Fonctionnalité", "Utilisation"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Par défaut
    afficherFonctionnalites("MainWindow");
}

HelpWindow::~HelpWindow()
{
    delete ui;
}

void HelpWindow::chargerJSON()
{
    QFile file(":/json/help.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erreur ouverture JSON : " << file.errorString();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) {
        qWarning() << "Format JSON incorrect";
        return;
    }

    jsonFonctionnalites = doc.object();
}

void HelpWindow::afficherFonctionnalites(const QString &categorie)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    if (!jsonFonctionnalites.contains(categorie)) return;

    QJsonArray array = jsonFonctionnalites[categorie].toArray();
    ui->tableWidget->setRowCount(array.size());

    for (int i = 0; i < array.size(); ++i) {
        QJsonObject obj = array[i].toObject();
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(obj["nom"].toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(obj["utilisation"].toString()));
    }
}

void HelpWindow::afficherFonctionnalitesMain()
{
    afficherFonctionnalites("MainWindow");
}

void HelpWindow::afficherFonctionnalitesQCM()
{
    afficherFonctionnalites("QCM");
}

void HelpWindow::afficherFonctionnalitesChoixSession()
{
    afficherFonctionnalites("ChoixSession");
}
