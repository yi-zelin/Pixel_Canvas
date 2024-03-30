// CanvasItem.h
#ifndef CANVASITEM_H
#define CANVASITEM_H

#include <QGraphicsItem>
#include "Canvas.h"

class CanvasItem : public QGraphicsItem {
public:
    CanvasItem(Canvas *canvas);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // 还可以添加其他事件处理函数，如 mousePressEvent 等

private:
    Canvas *canvas;
};

#endif // CANVASITEM_H
