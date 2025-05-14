#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QWidget>
#include <QJsonObject>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class HelpWindow; }
QT_END_NAMESPACE


class HelpWindow : public QDialog

{
    Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = nullptr);
    ~HelpWindow();

private slots:
    void afficherFonctionnalitesMain();
    void afficherFonctionnalitesQCM();
    void afficherFonctionnalitesChoixSession();

private:
    void chargerJSON();
    void afficherFonctionnalites(const QString &categorie);

    Ui::HelpWindow *ui;
    QJsonObject jsonFonctionnalites;
};

#endif // HELPWINDOW_H
