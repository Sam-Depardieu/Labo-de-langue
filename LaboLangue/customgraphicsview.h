#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class CustomGraphicsView : public QGraphicsView {
public:
    CustomGraphicsView(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    qreal scaleFactor = 1.15;
};

#endif // CUSTOMGRAPHICSVIEW_H
