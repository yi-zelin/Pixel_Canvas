#include "PixelEditorView.h"
#include <QPainter>
#include <QMouseEvent> // 添加这行

PixelEditorView::PixelEditorView(Model *model, QWidget *parent)
    : QWidget(parent), model(model), currentColor(Qt::black), scale(64),lastPixelX(-1), lastPixelY(-1) {
    // 设置适当的大小策略
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumSize(model->getCanvasImage().size());
}

void PixelEditorView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    const QImage &image = model->getCanvasImage();
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRect rect(x * scale, y * scale, scale, scale);
            painter.fillRect(rect, QColor(image.pixel(x, y)));
        }
    }
}

void PixelEditorView::mousePressEvent(QMouseEvent *event) {
    currentStroke = new Stroke(currentColor);
    int pixelX = event->x() / scale;
    int pixelY = event->y() / scale;
    model->setPixel(pixelX, pixelY, currentColor);
    update();
    lastPixelX = pixelX;
    lastPixelY = pixelY;
}

void PixelEditorView::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        int currentPixelX = event->x() / scale;
        int currentPixelY = event->y() / scale;

        // Interpolate between the previous and current pixel positions
        int deltaX = currentPixelX - lastPixelX;
        int deltaY = currentPixelY - lastPixelY;
        int steps = std::max(abs(deltaX), abs(deltaY));
        steps = std::max(steps, 1); // Ensure steps is never zero

        for (int i = 0; i <= steps; ++i) {
            int pointX = lastPixelX + (deltaX * i) / steps;
            int pointY = lastPixelY + (deltaY * i) / steps;
            model->setPixel(pointX, pointY, currentColor);
            currentStroke->points->push_back({pointX,pointY});
        }

        update();

        // Update the last pixel position
        lastPixelX = currentPixelX;
        lastPixelY = currentPixelY;
    }
}

void PixelEditorView::undoClicked(){
    if (!undoList.empty()){
        redoList.push(undoList.top());
        undoList.pop();
        // TODO: REDRAW
    }
}

void PixelEditorView::redoClicked(){
    if (!redoList.empty()){
        undoList.push(redoList.top());
        redoList.pop();
        // TODO: REDRAW
    }
}

void PixelEditorView::reDraw(){
    // if change backGround color, also change here
    model->canvasImage.fill(Qt::white);
}


void PixelEditorView::mouseReleaseEvent(QMouseEvent *event) {
    undoList.push(currentStroke);
    redoList=stack<Stroke*>();
}


PixelEditorView::~PixelEditorView() {
    // 进行必要的清理工作
}

