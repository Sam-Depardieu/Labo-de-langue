#ifndef GESTIONSESSION_H
#define GESTIONSESSION_H

#include "iconEleveGroup.h"
#include <QSqlDatabase>

// Pré-déclaration
class Participant;
class Professeur;

namespace Ui {
class MainWindow;
class gestionSession;
}

class gestionSession : public QObject {
    Q_OBJECT

public:
    explicit gestionSession(MainWindow *ui, QSqlDatabase db, QObject *parent = nullptr);

    bool validerEtEnregistrerSession(const QString &nomProf, const QString &nomActivite, const QString &nomClasse, const QTime &dureeActivite,
        const QString &consigne, const QString &source, std::vector<iconEleveGroup*> &participants, std::vector<int> &idsParticipants, int &idProf,
        bool sessionExistante);

    QStringList getActivites();
    QStringList getClasses();
    void reset();

private:
    MainWindow* mainWindow;

    QSqlDatabase database;
    QSqlDatabase m_db;
};
#endif // GESTIONSESSION_H
