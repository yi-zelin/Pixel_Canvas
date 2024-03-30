#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>
#include "Canvas.h"  // 确保你包含了之前创建的Canvas类

class CanvasWidget : public QWidget {
    Q_OBJECT

public:
    CanvasWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;  // 如果需要处理鼠标事件


private:
    Canvas canvas;  // Canvas对象实例
};

#endif // CANVASWIDGET_H
