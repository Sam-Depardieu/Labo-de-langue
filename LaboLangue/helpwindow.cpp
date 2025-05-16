#include "helpwindow.h"
#include "ui_helpwindow.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTableWidgetItem>
#include <QDebug>
#include <QLabel>

HelpWindow::HelpWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::HelpWindow)

{
    ui->setupUi(this);
    setWindowTitle("Aide - Professeur");

    // Charger le fichier JSON
    chargerJSON();

    // Table setup
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setWordWrap(true);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    ui->tableWidget->setHorizontalHeaderLabels({"Fonctionnalité", "Utilisation"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Par défaut
    afficherFonctionnalites("MainWindow");
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

        // Colonne fonctionnalité (texte court, simple)
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(obj["nom"].toString()));

        // Colonne utilisation (texte long, affiché dans un QLabel)
        QLabel *label = new QLabel(obj["utilisation"].toString());
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        ui->tableWidget->setCellWidget(i, 1, label);
    }

    // Redimensionner les lignes après insertion
    ui->tableWidget->resizeRowsToContents();

}

void HelpWindow::on_mainWindowButton_clicked()
{
    afficherFonctionnalites("MainWindow");
}

void HelpWindow::on_choixSessionButton_clicked()
{
    afficherFonctionnalites("ChoixSession");
}

void HelpWindow::on_qcmButton_clicked()
{
    afficherFonctionnalites("QCM");
}

HelpWindow::~HelpWindow()
{
    delete ui;
}
