#include "choixsession.h"
#include "ui_choixsession.h"

choixSession::choixSession(MainWindow* parentWindow)
    : mainWindow(parentWindow)
    , ui(new Ui::choixSession)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    columnView->setModel(model);

    // Charger les dossiers de sessions
    basePath = R"(\\CIEL-T171-05\Activites\)";              //à changer
    QDir dir(basePath);
    QStringList sessionDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QString &folder : sessionDirs) {
        listWidget->addItem(folder);
    }
}

choixSession::~choixSession()
{
    delete ui;
}

void choixSession::on_listeSession_itemDoubleClicked(QListWidgetItem *item)
{
    QString selectedPath = basePath + item->text() + "/config.labo";
    QFile file(selectedPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "❌ Impossible d'ouvrir" << selectedPath;
        model->clear();
        model->appendRow(new QStandardItem("Erreur : Impossible d’ouvrir le fichier."));
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError || !doc.isObject()) {
        model->clear();
        model->appendRow(new QStandardItem("Erreur : JSON invalide."));
        return;
    }

    QJsonObject obj = doc.object();
    model->clear();
    for (const QString &key : obj.keys()) {
        QStandardItem *item = new QStandardItem(key + " : " + obj[key].toString());
        model->appendRow(item);
    }
}

