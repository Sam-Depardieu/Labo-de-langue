#include "iconEleveGroup.h"
#include "mainwindow.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

iconEleveGroup::iconEleveGroup(int ID, QString ip, QGraphicsTextItem* text, MainWindow* parentWindow) : QGraphicsItemGroup(), ID(ID), IP(ip), nom(QString::number(ID)), textItem(text), mainWindow(parentWindow) {
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
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
            qDebug() << "IP : " << getIP();
        }
        else if (mainWindow->eleveActuellementParametre == this) {
            mainWindow->toggleSettingEleve(mainWindow->eleveActuellementParametre, false);

            mainWindow->listeEditEleve.clear();
            mainWindow->parametrageEleve = false;
            mainWindow->eleveActuellementParametre = nullptr;
        }
        else {
            mainWindow->toggleSettingEleve(mainWindow->eleveActuellementParametre, false);
            mainWindow->toggleSettingEleve(mainWindow->eleveActuellementParametre, true);
            mainWindow->eleveActuellementParametre = this;
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
