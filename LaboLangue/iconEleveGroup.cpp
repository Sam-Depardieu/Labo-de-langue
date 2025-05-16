#include "iconEleveGroup.h"
#include "mainwindow.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

iconEleveGroup::iconEleveGroup(int IDEleve, QString ipEleve, QGraphicsTextItem* text, MainWindow* parentWindow) : QGraphicsItemGroup(), mainWindow(parentWindow), nom(QString::number(IDEleve)), IP(ipEleve), ID(IDEleve), textItem(text) {
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setFlag(QGraphicsItem::ItemIsMovable, true);

}

void iconEleveGroup::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (mainWindow->parametrageSession && !mainWindow->runningSession) {
        // Ajouter ou retirer de la liste des participants seulement si sélection active
        auto it = std::find(mainWindow->listeParticipant.begin(), mainWindow->listeParticipant.end(), this);
        if ((mainWindow->selectionParticipants || mainWindow->selectAllParticipants)) {
            if (it == mainWindow->listeParticipant.end()) {
                mainWindow->listeParticipant.push_back(this);
            } else {
                mainWindow->listeParticipant.erase(it);
            }
        }
            // Fermer un paramétrage élève actif
            if (mainWindow->parametrageEleve && mainWindow->eleveActuellementParametre) {
            mainWindow->toggleSettingEleve(mainWindow->eleveActuellementParametre, false);
            mainWindow->parametrageEleve = false;
            mainWindow->eleveActuellementParametre = nullptr;
        }

        // ✅ Modifier l'état du checkItem uniquement si sélection active
        if ((mainWindow->selectionParticipants || mainWindow->selectAllParticipants) && checkItem) {
            checkItem->setVisible(!checkItem->isVisible());
        }
    }
    else if (mainWindow->runningSession) {

        for (auto *eleve : mainWindow->listeParticipant) {
            if (eleve->getCheckItem()) {
                eleve->getCheckItem()->setVisible(false);
            }
        }

        if (!mainWindow->parametrageEleve) {
            mainWindow->toggleSettingEleve(mainWindow->eleveActuellementParametre, true);
            mainWindow->parametrageEleve = true;
            mainWindow->eleveActuellementParametre = this;
            mainWindow->listeEditEleve.push_back(this);
            mainWindow->setNomEtudiantLineEdit(this->getNom());
            qDebug() << "IP : " << getIP();
        }
        else if (mainWindow->eleveActuellementParametre == this) {
            mainWindow->toggleSettingEleve(mainWindow->eleveActuellementParametre, false);

            mainWindow->listeEditEleve.clear();
            mainWindow->parametrageEleve = false;
            mainWindow->eleveActuellementParametre = nullptr;
        }
        else {
            mainWindow->toggleSettingEleve(mainWindow->eleveActuellementParametre, false); // Ferme l'ancien
            mainWindow->eleveActuellementParametre = this; // Met à jour le pointeur AVANT d'ouvrir
            mainWindow->toggleSettingEleve(this, true); // Ouvre avec le nouveau
        }
    }

    QGraphicsItemGroup::mouseDoubleClickEvent(event);

}

QVariant iconEleveGroup::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange) {

        QPointF newPos = value.toPointF();
        QRectF sceneBounds = scene() ? scene()->sceneRect() : QRectF();  // Vérifier que la scène existe

        if (sceneBounds.isNull()) {
            return QGraphicsItemGroup::itemChange(change, value);  // Éviter de modifier si la scène n'est pas définie
        }

        // Taille du groupe
        QRectF itemBounds = boundingRect();

        // Vérifier les limites et ajuster la position
        if (newPos.x() < sceneBounds.left()) {
            newPos.setX(sceneBounds.left());
        }
        if (newPos.y() < sceneBounds.top()) {
            newPos.setY(sceneBounds.top());
        }
        if (newPos.x() + itemBounds.width() > sceneBounds.right()) {
            newPos.setX(sceneBounds.right() - itemBounds.width());
        }
        if (newPos.y() + itemBounds.height() > sceneBounds.bottom()) {
            newPos.setY(sceneBounds.bottom() - itemBounds.height());
        }

        // Mettre à jour la position dans la base de données
        QSqlQuery query;
        query.prepare("UPDATE Raspberry SET X = :x, Y = :y WHERE Id_Raspberry = :numPoste");
        query.bindValue(":x", newPos.x());
        query.bindValue(":y", newPos.y());
        query.bindValue(":numPoste", ID);  // Utiliser l'identifiant de la poste
        if (!query.exec()) {
            qDebug() << "Erreur lors de la mise à jour de la position :" << query.lastError();
        }

        return newPos;
    }

    return QGraphicsItemGroup::itemChange(change, value);

}

QRectF iconEleveGroup::boundingRect() const
{
    QRectF rect = childrenBoundingRect();
    return rect;
}

QColor iconEleveGroup::couleurDepuisEtat(CouleurEtat etat) {
    switch (etat) {
    case CouleurEtat::Rouge:      return Qt::red;
    case CouleurEtat::Vert:       return Qt::green;
    case CouleurEtat::Bleu:       return Qt::blue;
    case CouleurEtat::Jaune:      return Qt::yellow;
    case CouleurEtat::Orange:     return QColor(255, 165, 0);
    case CouleurEtat::Violet:     return QColor(128, 0, 128);
    case CouleurEtat::Rose:       return QColor(255, 105, 180);
    case CouleurEtat::Marron:     return QColor(139, 69, 19);
    case CouleurEtat::Cyan:       return Qt::cyan;
    case CouleurEtat::Magenta:    return Qt::magenta;
    case CouleurEtat::Turquoise:  return QColor(64, 224, 208);
    case CouleurEtat::Olive:      return QColor(128, 128, 0);
    case CouleurEtat::Corail:     return QColor(255, 127, 80);
    case CouleurEtat::Indigo:     return QColor(75, 0, 130);
    case CouleurEtat::Menthe:     return QColor(152, 255, 152);
    default:                      return Qt::gray;
    }
}

void iconEleveGroup::setEtatCouleurEnum(CouleurEtat etat) {
    setCouleurGroup(couleurDepuisEtat(etat));
    etatActuel = etat;
}

void iconEleveGroup::setCouleurGroup(const QColor &couleur) {
    if (groupColor) {
        groupColor->setBrush(couleur);
        groupColor->setVisible(true); // Affiche la pastille si elle ne l'était pas
    }
}
