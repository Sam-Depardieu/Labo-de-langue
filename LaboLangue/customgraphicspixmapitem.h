#ifndef CUSTOMGRAPHICSPIXMAPITEM_H
#define CUSTOMGRAPHICSPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>

class CustomGraphicsPixmapItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    CustomGraphicsPixmapItem(const QPixmap &pixmap);
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void doubleClicked();
};


#endif // CUSTOMGRAPHICSPIXMAPITEM_H
