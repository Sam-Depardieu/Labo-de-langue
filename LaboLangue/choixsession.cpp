#include "choixsession.h"
#include "ui_choixsession.h"

choixSession::choixSession(MainWindow* parentWindow)
    : mainWindow(parentWindow)
    , ui(new Ui::choixSession)
{
    ui->setupUi(this);

    ui->sortAZButton->setIcon(QIcon("../img/sortAZ.png"));
    ui->sortZAButton->setIcon(QIcon("../img/sortZA.png"));
    ui->sortAZButton->setVisible(false);
    ui->sortZAButton->setVisible(true);

    // Charger les dossiers de sessions
    basePath = R"(//CIEL-T171-05/Activites)";              //à changer
    QDir dir(basePath);
    QStringList sessionDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);


    for (const QString &folder : sessionDirs) {
        QString folderPath = basePath + "/" + folder;
        QFileInfo info(folderPath);
        QString creationDate = info.birthTime().toString("dd/MM/yyyy hh:mm");

        // Lire le fichier config.labo
        QFile file(folderPath + "/config.labo");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "❌ Impossible d’ouvrir :" << file.fileName();
            continue;  // passer au dossier suivant
        }

        QByteArray data = file.readAll();
        file.close();

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(data, &error);
        if (error.error != QJsonParseError::NoError || !doc.isObject()) {
            qDebug() << "❌ JSON invalide dans :" << file.fileName();
            continue;
        }

        QJsonObject obj = doc.object();
        int id = obj.value("idTypeActivite").toInt(-1);  // -1 = valeur par défaut si non présent ou non int
        QString idTypeActivite = (id == -1) ? "Inconnu" : QString::number(id);

        // Création du widget personnalisé
        QWidget* itemWidget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout(itemWidget);
        layout->setContentsMargins(5, 5, 5, 5);

        QLabel* titleLabel = new QLabel(folder);
        titleLabel->setStyleSheet("font-weight: bold; font-size: 16px;");

        QLabel* dateLabel = new QLabel("Créé le : " + creationDate);
        QLabel* customLine1 = new QLabel("Type d'activité : " + idTypeActivite);
        QLabel* customLine2 = new QLabel("Ligne personnalisée 2"); // Tu peux personnaliser ça aussi depuis le JSON si tu veux

        layout->addWidget(titleLabel);
        layout->addWidget(dateLabel);
        layout->addWidget(customLine1);
        layout->addWidget(customLine2);

        // Ajout à la QListWidget
        QListWidgetItem* item = new QListWidgetItem(ui->listeSession);
        item->setSizeHint(itemWidget->sizeHint());
        item->setData(Qt::UserRole, folder);  // pour le retrouver facilement plus tard

        ui->listeSession->addItem(item);
        ui->listeSession->setItemWidget(item, itemWidget);
    }

}

choixSession::~choixSession()
{
    delete ui;
}

void choixSession::on_listeSession_itemDoubleClicked(QListWidgetItem *item)
{
    QString folderName = item->data(Qt::UserRole).toString();
    QString selectedPath = basePath + "/" + folderName + "/config.labo";
    QFile file(selectedPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "❌ Impossible d'ouvrir" << selectedPath;
        ui->infoSession->clear();
        ui->infoSession->addItem("Erreur : Impossible d’ouvrir le fichier.");

        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError || !doc.isObject()) {
        ui->infoSession->clear();
        ui->infoSession->addItem("Erreur : JSON invalide.");

        return;
    }

    QJsonObject obj = doc.object();
    ui->infoSession->clear();
    for (const QString &key : obj.keys()) {
        QJsonValue val = obj[key];
        QString displayValue;

        if (val.isString()) {
            displayValue = val.toString();
        } else if (val.isDouble()) {
            displayValue = QString::number(val.toDouble());
        } else if (val.isBool()) {
            displayValue = val.toBool() ? "true" : "false";
        } else if (val.isNull()) {
            displayValue = "null";
        } else if (val.isArray()) {
            displayValue = "[...]";  // tu peux aussi itérer dessus si besoin
        } else if (val.isObject()) {
            displayValue = "{...}";  // idem, à détailler si nécessaire
        } else {
            displayValue = "Inconnu";
        }

        ui->infoSession->addItem(key + " : " + displayValue);
    }


}

void choixSession::on_findLineEdit_textChanged(const QString &arg1)
{
    const QString basePath = R"(//CIEL-T171-05/Activites)";
    QDir dir(basePath);
    QStringList sessionDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    ui->listeSession->clear();

    for (const QString &folder : sessionDirs) {
        if (!folder.contains(arg1, Qt::CaseInsensitive))
            continue;

        const QString folderPath = basePath + "/" + folder;
        QFileInfo info(folderPath);
        QString creationDate = info.birthTime().toString("dd/MM/yyyy hh:mm");

        QFile file(folderPath + "/config.labo");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "❌ Impossible d’ouvrir :" << file.fileName();
            continue;
        }

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
        file.close();

        if (error.error != QJsonParseError::NoError || !doc.isObject()) {
            qDebug() << "❌ JSON invalide dans :" << file.fileName();
            continue;
        }

        QJsonObject obj = doc.object();
        QString idTypeActivite = obj.contains("idTypeActivite") && obj["idTypeActivite"].isDouble()
                                     ? QString::number(obj["idTypeActivite"].toInt())
                                     : "Inconnu";

        // -- Création du widget personnalisé --
        QWidget *itemWidget = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(itemWidget);
        layout->setContentsMargins(5, 5, 5, 5);

        QLabel *titleLabel = new QLabel(folder);
        titleLabel->setStyleSheet("font-weight: bold; font-size: 16px;");

        layout->addWidget(titleLabel);
        layout->addWidget(new QLabel("Créé le : " + creationDate));
        layout->addWidget(new QLabel("Type d'activité : " + idTypeActivite));
        layout->addWidget(new QLabel("Ligne personnalisée 2"));

        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->sizeHint());
        item->setData(Qt::UserRole, folder);

        ui->listeSession->addItem(item);
        ui->listeSession->setItemWidget(item, itemWidget);
    }
}


void choixSession::on_sortAZButton_clicked()
{
    trierListeSessions(true);
}


void choixSession::on_sortZAButton_clicked()
{
    trierListeSessions(false);
}


void choixSession::trierListeSessions(bool ordreCroissant)
{
    ui->sortAZButton->setVisible(!ordreCroissant);
    ui->sortZAButton->setVisible(ordreCroissant);

    QList<QString> folderNames;
    QMap<QString, QString> creationDates;
    QMap<QString, QString> idTypes;

    for (int i = 0; i < ui->listeSession->count(); ++i) {
        QListWidgetItem* item = ui->listeSession->item(i);
        QString folder = item->data(Qt::UserRole).toString();
        folderNames.append(folder);

        QString folderPath = basePath + "/" + folder;
        QFileInfo info(folderPath);
        creationDates[folder] = info.birthTime().toString("dd/MM/yyyy hh:mm");

        QFile file(folderPath + "/config.labo");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) continue;
        QByteArray data = file.readAll();
        file.close();

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(data, &error);
        if (error.error != QJsonParseError::NoError || !doc.isObject()) continue;

        int id = doc.object().value("idTypeActivite").toInt(-1);
        idTypes[folder] = (id == -1) ? "Inconnu" : QString::number(id);
    }

    std::sort(folderNames.begin(), folderNames.end(), [ordreCroissant](const QString &a, const QString &b) {
        return ordreCroissant ? a.toLower() < b.toLower() : a.toLower() > b.toLower();
    });

    ui->listeSession->clear();

    for (const QString &folder : folderNames) {
        QWidget* itemWidget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout(itemWidget);
        layout->setContentsMargins(5, 5, 5, 5);

        QLabel* titleLabel = new QLabel(folder);
        titleLabel->setStyleSheet("font-weight: bold; font-size: 16px;");

        QLabel* dateLabel = new QLabel("Créé le : " + creationDates.value(folder));
        QLabel* customLine1 = new QLabel("Type d'activité : " + idTypes.value(folder));
        QLabel* customLine2 = new QLabel("Ligne personnalisée 2");

        layout->addWidget(titleLabel);
        layout->addWidget(dateLabel);
        layout->addWidget(customLine1);
        layout->addWidget(customLine2);

        QListWidgetItem* item = new QListWidgetItem(ui->listeSession);
        item->setSizeHint(itemWidget->sizeHint());
        item->setData(Qt::UserRole, folder);

        ui->listeSession->addItem(item);
        ui->listeSession->setItemWidget(item, itemWidget);
    }
}
