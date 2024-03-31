#include "PixelEditorView.h"
#include <QPainter>
#include <QMouseEvent>

PixelEditorView::PixelEditorView(Model *model, QWidget *parent)
    : QWidget(parent), model(model), currentColor(Qt::black), scale(16),lastPixelX(-1), lastPixelY(-1) {
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumSize(model->getCanvasImage().size());
}

void PixelEditorView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    const QImage &image = model->getCanvasImage();

    // Calculate the top-left position to center the canvas
    int offsetX = (width() - image.width() * scale) / 2;
    int offsetY = (height() - image.height() * scale) / 2;

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRect rect(offsetX + x * scale, offsetY + y * scale, scale, scale);
            painter.fillRect(rect, QColor(image.pixel(x, y)));
        }
    }
}

void PixelEditorView::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event); // Mark the event parameter as unused to avoid compiler warnings
    update(); // Trigger a repaint to re-center the canvas
}

void PixelEditorView::mousePressEvent(QMouseEvent *event) {
    int offsetX = (width() - model->getCanvasImage().width() * scale) / 2;
    int offsetY = (height() - model->getCanvasImage().height() * scale) / 2;

    int pixelX = (event->x() - offsetX) / scale;
    int pixelY = (event->y() - offsetY) / scale;
    if (pixelX >= 0 && pixelX < model->getCanvasImage().width() &&
        pixelY >= 0 && pixelY < model->getCanvasImage().height()) {
        model->setPixel(pixelX, pixelY, currentColor);
        update();
    }

    lastPixelX = pixelX;
    lastPixelY = pixelY;
}

void PixelEditorView::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        int offsetX = (width() - model->getCanvasImage().width() * scale) / 2;
        int offsetY = (height() - model->getCanvasImage().height() * scale) / 2;

        int currentPixelX = (event->x() - offsetX) / scale;
        int currentPixelY = (event->y() - offsetY) / scale;

        if (currentPixelX >= 0 && currentPixelX < model->getCanvasImage().width() &&
            currentPixelY >= 0 && currentPixelY < model->getCanvasImage().height()) {
            // Interpolate between the previous and current pixel positions
            int deltaX = currentPixelX - lastPixelX;
            int deltaY = currentPixelY - lastPixelY;
            int steps = std::max(abs(deltaX), abs(deltaY));
            steps = std::max(steps, 1); // Ensure steps is never zero

            for (int i = 0; i <= steps; ++i) {
                int interpolatedX = lastPixelX + (deltaX * i) / steps;
                int interpolatedY = lastPixelY + (deltaY * i) / steps;
                if (interpolatedX >= 0 && interpolatedX < model->getCanvasImage().width() &&
                    interpolatedY >= 0 && interpolatedY < model->getCanvasImage().height()) {
                    model->setPixel(interpolatedX, interpolatedY, currentColor);
                }
            }

            update();

            // Update the last pixel position
            lastPixelX = currentPixelX;
            lastPixelY = currentPixelY;
        }
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

}

