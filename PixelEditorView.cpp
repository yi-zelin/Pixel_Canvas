#include "PixelEditorView.h"
#include <QPainter>
#include <QMouseEvent> // 添加这行

PixelEditorView::PixelEditorView(Model *model, QWidget *parent)
    : QWidget(parent), model(model), currentColor(Qt::black) {
    // 设置适当的大小策略
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumSize(model->getCanvasImage().size());
}

void PixelEditorView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawImage(0, 0, model->getCanvasImage());
}

void PixelEditorView::mousePressEvent(QMouseEvent *event) {
    model->setPixel(event->x(), event->y(), currentColor);
    update(); // 重绘组件
}

void PixelEditorView::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        model->setPixel(event->x(), event->y(), currentColor);
        update(); // 重绘组件
    }
}

PixelEditorView::~PixelEditorView() {
    // 进行必要的清理工作
}

