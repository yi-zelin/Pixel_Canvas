#include "PixelItem.h"
#include <QPainter>

PixelItem::PixelItem(int x, int y, const QColor &color, int pixelSize) : size(pixelSize) {
    setPos(x * size, y * size);
    this->color = color;
}

QRectF PixelItem::boundingRect() const {
    return QRectF(0, 0, size, size); // 使用传入的像素大小
}

void PixelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->fillRect(boundingRect(), color);
}
