#include "CustomGraphicsView.h"
#include <QGraphicsScene>

CustomGraphicsView::CustomGraphicsView(QWidget *parent) : QGraphicsView(parent) {}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event) {
    QPointF scenePoint = mapToScene(event->pos());
    emit mouseClicked(static_cast<int>(scenePoint.x()), static_cast<int>(scenePoint.y()));
}
