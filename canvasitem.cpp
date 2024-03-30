// CanvasItem.cpp
#include "CanvasItem.h"
#include <QPainter>

CanvasItem::CanvasItem(Canvas *canvas) : canvas(canvas) {}

QRectF CanvasItem::boundingRect() const {
    // 返回 Canvas 的矩形边界
    return QRectF(0, 0, canvas->getWidth(), canvas->getHeight());
}

void CanvasItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // 根据 Canvas 中的像素数据绘制项目
    for (int y = 0; y < canvas->getHeight(); ++y) {
        for (int x = 0; x < canvas->getWidth(); ++x) {
            Pixel pixel = canvas->getPixel(x, y);
            painter->setPen(QColor(pixel.getR(), pixel.getG(), pixel.getB()));
            painter->drawPoint(x, y);
        }
    }
}
