#ifndef PIXELITEM_H
#define PIXELITEM_H

#include <QGraphicsItem>

class PixelItem : public QGraphicsItem {
public:
    // 构造函数，设置像素的位置和颜色
    PixelItem(int x, int y, const QColor &color, int pixelSize);

    // 必须重写的函数
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QColor color;
    int size;
};

#endif // PIXELITEM_H
