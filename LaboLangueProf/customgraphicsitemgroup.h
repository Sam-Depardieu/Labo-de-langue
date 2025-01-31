#ifndef CUSTOMGRAPHICSITEMGROUP_H
#define CUSTOMGRAPHICSITEMGROUP_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QObject>

class CustomGraphicsItemGroup : public QObject, public QGraphicsItemGroup {
    Q_OBJECT
    public:
        CustomGraphicsItemGroup(int numero, int id_eleve);

    protected:
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
        QRectF boundingRect()const override;
        int getId() const;

    private:
        int numero = 0;
        int id_eleve;
        int affiliate = {};

    signals:
        void doubleClicked();
};

#endif // CUSTOMGRAPHICSITEMGROUP_H
