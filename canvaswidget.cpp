#include "CanvasWidget.h"
#include <QPainter>
#include <QMouseEvent>

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent), canvas(600, 400) {

}

void CanvasWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {

    QPoint pos = event->pos();
    Pixel color(255, 0, 0);
    canvas.setPixel(pos.x(), pos.y(), color);
    update();
}


