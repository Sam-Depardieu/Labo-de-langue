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
    void on_mainWindowButton_clicked();
    void on_choixSessionButton_clicked();
    void on_qcmButton_clicked();

    void on_gestionStudentButton_clicked();

private:
    void chargerJSON();
    void afficherFonctionnalites(const QString &categorie);

    Ui::HelpWindow *ui;
    QJsonObject jsonFonctionnalites;
};

#endif // HELPWINDOW_H
