#include "customgraphicspixmapitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

CustomGraphicsPixmapItem::CustomGraphicsPixmapItem(const QPixmap &pixmap)
    : QGraphicsPixmapItem(pixmap) {}

void CustomGraphicsPixmapItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Double-clic détecté sur l'image !"; // Message de débogage
    emit doubleClicked();
    QGraphicsPixmapItem::mouseDoubleClickEvent(event);
}
