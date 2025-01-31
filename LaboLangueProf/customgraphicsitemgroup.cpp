#include "customgraphicsitemgroup.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

CustomGraphicsItemGroup::CustomGraphicsItemGroup(int numero, int id_eleve) : QGraphicsItemGroup(), numero(numero), id_eleve(id_eleve) {
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void CustomGraphicsItemGroup::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Double-clic détecté sur le groupe !"; // Message de débogage
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
