#include "CanvasWidget.h"
#include <QPainter>
#include <QMouseEvent>

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent), canvas(600, 400) {

}

void CanvasWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QImage image(canvas.getWidth(), canvas.getHeight(), QImage::Format_ARGB32);
    canvas.drawToImage(image);  // 使用Canvas的绘制方法
    painter.drawImage(0, 0, image);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // 计算点击位置对应的像素坐标
        int x = event->pos().x();
        int y = event->pos().y();
        // 设置像素为黑色，或者选择其他颜色
        canvas.setPixel(x, y, Pixel(0, 0, 0));
        update();  // 重绘组件以反映更改
    }
}

