#include "customgraphicsitemgroup.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

CustomGraphicsItemGroup::CustomGraphicsItemGroup(int numero, int id_eleve, QString ip) : QGraphicsItemGroup(), numero(numero), id_eleve(id_eleve), IP(ip) {
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void CustomGraphicsItemGroup::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {

    qDebug() << IP;
    emit doubleClicked();
    QGraphicsItemGroup::mouseDoubleClickEvent(event);
}

QVariant CustomGraphicsItemGroup::itemChange(GraphicsItemChange change, const QVariant &value)
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
        query.prepare("UPDATE Placement SET X = :x, Y = :y WHERE NumPoste = :numPoste");
        query.bindValue(":x", newPos.x());
        query.bindValue(":y", newPos.y());
        query.bindValue(":numPoste", numero);  // Utiliser l'identifiant de la poste
        if (!query.exec()) {
            qDebug() << "Erreur lors de la mise à jour de la position :" << query.lastError();
        }

        return newPos;
    }

    return QGraphicsItemGroup::itemChange(change, value);
}


QRectF CustomGraphicsItemGroup::boundingRect() const
{
    QRectF rect = childrenBoundingRect();
    return rect;
}

int CustomGraphicsItemGroup::getId() const{
    return numero;
}
