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
    const QImage &image = model->getCanvasImage();
    const int pixelSize = 4; // 实际的放大倍数
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRect rect(x * pixelSize, y * pixelSize, pixelSize, pixelSize);
            painter.fillRect(rect, QColor(image.pixel(x, y)));
        }
    }
}

void PixelEditorView::mousePressEvent(QMouseEvent *event) {
    // 假设 scaleFactor 是您用于放大图像的倍数
    int scaleFactor = 4;
    // 将鼠标坐标转换为画布上的像素坐标
    int pixelX = event->x() / scaleFactor;
    int pixelY = event->y() / scaleFactor;
    // 设置模型中相应像素的颜色
    model->setPixel(pixelX, pixelY, currentColor);
    update();
}

void PixelEditorView::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        int scaleFactor = 4;
        int pixelX = event->x() / scaleFactor;
        int pixelY = event->y() / scaleFactor;
        model->setPixel(pixelX, pixelY, currentColor);
        update();
    }
}

PixelEditorView::~PixelEditorView() {
    // 进行必要的清理工作
}

