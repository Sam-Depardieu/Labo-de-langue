#ifndef ICONELEVEGROUP_H
#define ICONELEVEGROUP_H

// === Qt Core & Widgets ===
#include <QObject>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QRectF>
#include <QString>
#include <vector>

// === Qt Multimédia (optionnel selon utilisation) ===
#include <QtMultimedia>
#include <QtMultimediaWidgets>

// === Projet ===
class MainWindow;

class iconEleveGroup : public QObject, public QGraphicsItemGroup {
    Q_OBJECT

public:
    // === Constructeur ===
    iconEleveGroup(int ID, QString ip, QGraphicsTextItem* text, MainWindow* parentWindow);

    // === Setters ===
    void setCheckItem(QGraphicsPixmapItem *item) { checkItem = item; }
    void setSound(QGraphicsPixmapItem *item) { sound = item; }
    void setMicroActiver(QGraphicsPixmapItem *item) { microActiver = item; }
    void setMicroDesactiver(QGraphicsPixmapItem *item) { microDesactiver = item; }
    void setCasqueActiver(QGraphicsPixmapItem *item) { casqueActiver = item; }
    void setCasqueDesactiver(QGraphicsPixmapItem *item) { casqueDesactiver = item; }
    void setIDELeve(int id) { IDEleve = id; }
    void setTextItem(const QString newText) { if (textItem) textItem->setPlainText(newText); }
    void setNom(const QString& newNom) { nom = newNom; }
    void setNumQCM(int num) { numQCM = num; }
    void setNomGroupe(const QString& nomG) { nomGroupe = nomG; }

    // === Getters ===
    int getID() const { return ID; }
    int getIDEleve() const { return IDEleve; }
    int getNumQCM() const { return numQCM; }
    QString getNom() const { return nom; }
    QString getIP() const { return IP; }
    QString getNomGroupe() const { return nomGroupe; }
    std::vector<iconEleveGroup*> getAffiliate() const { return affiliate; }

    QGraphicsTextItem* getTextItem() const { return textItem; }
    QGraphicsPixmapItem* getCheckItem() const { return checkItem; }
    QGraphicsPixmapItem* getSound() const { return sound; }

    QGraphicsPixmapItem* getMicroActiver() const { return microActiver; }
    QGraphicsPixmapItem* getMicroDesactiver() const { return microDesactiver; }
    QGraphicsPixmapItem* getCasqueActiver() const { return casqueActiver; }
    QGraphicsPixmapItem* getCasqueDesactiver() const { return casqueDesactiver; }

signals:
    void doubleClicked();

protected:
    // === Redéfinitions graphiques ===
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    QRectF boundingRect() const override;

private:
    // === Références / contexte ===
    MainWindow* mainWindow;

    // === Données élève ===
    QString nom;
    QString IP;
    QString nomGroupe;
    int ID = 0;
    int IDEleve = 0;
    int numQCM = 1;

    std::vector<iconEleveGroup*> affiliate;

    // === Éléments graphiques ===
    QGraphicsTextItem* textItem = nullptr;
    QGraphicsPixmapItem* checkItem = nullptr;
    QGraphicsPixmapItem* sound = nullptr;

    QGraphicsPixmapItem* microActiver = nullptr;
    QGraphicsPixmapItem* microDesactiver = nullptr;
    QGraphicsPixmapItem* casqueActiver = nullptr;
    QGraphicsPixmapItem* casqueDesactiver = nullptr;
};

#endif // ICONELEVEGROUP_H
