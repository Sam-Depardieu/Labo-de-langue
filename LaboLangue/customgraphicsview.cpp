#include "customgraphicsview.h"

CustomGraphicsView::CustomGraphicsView(QWidget *parent) : QGraphicsView(parent) {}

void CustomGraphicsView::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zoom out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}
