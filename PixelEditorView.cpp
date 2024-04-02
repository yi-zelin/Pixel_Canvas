#include "PixelEditorView.h"
#include <QPainter>
#include <QMouseEvent>

using std::min;
using std::max;

PixelEditorView::PixelEditorView(Model *model, QWidget *parent,QColor currentColor,int scale,bool state)
    : QWidget(parent), currentColor(currentColor),model(model), scale(scale),lastPixelX(-1), lastPixelY(-1)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumSize(model->getCanvasImage().size());
    isDrawingEnabled=state;

}

void PixelEditorView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    const QImage &image = model->getCanvasImage();

    const int scaleLessThan4by4 = 100;

    if (image.width() < 5 && image.height() < 5) {
        scale = scaleLessThan4by4;
    } else {
        scale = qMin(width() / image.width(), height() / image.height());
        scale = qMax(scale, 10);
    }

    // Calculate the top-left position to center the canvas
    int offsetX = (width() - image.width() * scale) / 2;
    int offsetY = (height() - image.height() * scale) / 2;

    // Draw the scaled pixels
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
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
    currentStroke = new Stroke(currentColor);
    redoList.clear();
    int offsetX = (width() - model->getCanvasImage().width() * scale) / 2;
    int offsetY = (height() - model->getCanvasImage().height() * scale) / 2;

    int pixelX = (event->x() - offsetX) / scale;
    int pixelY = (event->y() - offsetY) / scale;

    if (isDrawingEnabled){
        if (pixelX >= 0 && pixelX < model->getCanvasImage().width() &&
            pixelY >= 0 && pixelY < model->getCanvasImage().height()) {
            model->setPixel(pixelX, pixelY, currentColor);
            update();
        }

        lastPixelX = pixelX;
        lastPixelY = pixelY;
        currentStroke->points->push_back({pixelX,pixelY});
    } else if (isFillMode){
        fill(pixelX, pixelY);
        undoList.push_back(currentStroke);
        update();
    } else {
        // draw line or rectangle need Real Time Rendering
        lastPixelX = pixelX;
        lastPixelY = pixelY;
    }
}

void PixelEditorView::mouseMoveEvent(QMouseEvent *event) {
    int offsetX = (width() - model->getCanvasImage().width() * scale) / 2;
    int offsetY = (height() - model->getCanvasImage().height() * scale) / 2;

    int currentPixelX = (event->x() - offsetX) / scale;
    int currentPixelY = (event->y() - offsetY) / scale;

    if ((isDrawingEnabled || lineMode)&& event->buttons() & Qt::LeftButton) {
        if (lineMode){
            redraw(undoList);
            currentStroke = new Stroke(currentColor);
        }

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
                currentStroke->points->push_back({interpolatedX,interpolatedY});
            }

            update();

            // Update the last pixel position
            if (isDrawingEnabled){
                lastPixelX = currentPixelX;
                lastPixelY = currentPixelY;
            }
        }
    } else if (rectangleMode){
        redraw(undoList);
        currentStroke = new Stroke(currentColor);

        int minX = min(currentPixelX, lastPixelX);
        int maxX = max(currentPixelX, lastPixelX);
        int minY = min(currentPixelY, lastPixelY);
        int maxY = max(currentPixelY, lastPixelY);

        for (int x = minX; x <= maxX; x++){
            model->setPixel(x, minY, currentColor);
            model->setPixel(x, maxY, currentColor);
            currentStroke->points->push_back({x,minY});
            currentStroke->points->push_back({x,maxY});
        }

        for (int y = minY; y <= maxY; y++){
            model->setPixel(minX, y, currentColor);
            model->setPixel(maxX, y, currentColor);
            currentStroke->points->push_back({minX,y});
            currentStroke->points->push_back({maxX,y});
        }

        update();
    }
}

void PixelEditorView::mouseReleaseEvent(QMouseEvent* event)
{
    if (isDrawingEnabled || lineMode || rectangleMode){
        undoList.push_back(currentStroke);
    }
    currentStroke = nullptr;
}

void PixelEditorView::undoClicked(){
    if (!undoList.empty()){
        redoList.push_back(undoList.back());
        undoList.pop_back();
        redraw(undoList);
    }
}

void PixelEditorView::redoClicked(){
    if (!redoList.empty()){
        undoList.push_back(redoList.back());
        redoList.pop_back();
        redraw(undoList);
    }
}

void PixelEditorView::redraw(vector<Stroke*> strokes){
    model->canvasImage.fill(Qt::white);
    for(auto stroke: strokes)
    {
        auto color = stroke->color;
        auto points = stroke->points;
        for(auto point: *points)
        {
            int x = point.first;
            int y = point.second;
            model->setPixel(x, y, color);
        }
    }
    update();
}

void PixelEditorView::setEraserMode(bool active) {
    isFillMode = false;
    rectangleMode = false;
    lineMode = false;
    isDrawingEnabled = active;
    if(active) {
        if (!isEraserMode)
            previousColor = currentColor;
        currentColor = QColor(Qt::white);
        isEraserMode = true;
    } else {
    }
}
void PixelEditorView::setPenMode(bool active){
    isFillMode = false;
    rectangleMode = false;
    lineMode = false;
    // currentColor = previousColor;
    if(active){
        if (isEraserMode)
            currentColor = previousColor;
        isDrawingEnabled = true;
        isEraserMode = false;
    }
    else{
        isDrawingEnabled=false;
    }
}

void PixelEditorView::setFillMode(bool active){
    if (isEraserMode)
        currentColor = previousColor;
    isDrawingEnabled = false;
    isEraserMode = false;
    rectangleMode = false;
    lineMode = false;
    if(active){
        isFillMode = true;
    }
    else{
        isFillMode = false;
    }
}

void PixelEditorView::setLineMode(bool active){
    if (isEraserMode)
        currentColor = previousColor;
    isDrawingEnabled = false;
    isEraserMode = false;
    isFillMode = false;
    rectangleMode = false;
    lineMode = active;
}

void PixelEditorView::setRectangleMode(bool active){
    if (isEraserMode)
        currentColor = previousColor;
    isDrawingEnabled = false;
    isEraserMode = false;
    isFillMode = false;
    lineMode = false;
    rectangleMode = active;
}

void PixelEditorView::setCurrentColor(const QColor &color) {
    currentColor = color;
    isEraserMode = false;
}

void PixelEditorView::setUndo(){
    undoClicked();
}
void PixelEditorView::setRedo(){
    redoClicked();
}

void PixelEditorView::saveClicked() {
    QJsonDocument jsonFile(convertIntoJson(model->getCanvasImage()));
    saveJsonToFile(jsonFile);
}


void PixelEditorView::loadClicked()
{
    loadJsonFromFile();

}

QJsonDocument PixelEditorView::convertIntoJson(QImage image)
{
    QByteArray imageBytes;
    QBuffer buffer(&imageBytes);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    QByteArray data = imageBytes.toBase64();
    QJsonObject json;
    json["image"] = QString(data);
    return QJsonDocument(json);
}

void PixelEditorView::saveJsonToFile(QJsonDocument &document) {
    QString fileName = QFileDialog::getSaveFileName(this, QObject::tr("Save File"), "", QObject::tr("JSON Files (*.ssp)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return;
    file.write(document.toJson());
    file.close();
    return;
}

void PixelEditorView::loadJsonFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this, QObject::tr("Open File"), "", QObject::tr("JSON Files (*.ssp)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QByteArray saveData = file.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(saveData);
    QJsonObject jsonObj = jsonDocument.object();
    QString string = jsonObj["image"].toString();
    QByteArray data = string.toLatin1();
    QImage image;
    image.loadFromData(QByteArray::fromBase64(data));
    model->canvasImage = image;
}

PixelEditorView::~PixelEditorView() {

}

void PixelEditorView::fill(int x, int y){
    if ((*model).getPixel(x,y).isValid() && (*model).getPixel(x,y) == QColor(Qt::white)){


        model->setPixel(x, y, currentColor);
        currentStroke->points->push_back({x, y});

        fill(x+1, y);
        fill(x-1, y);
        fill(x, y+1);
        fill(x, y-1);
    }
}
vector<Stroke*> PixelEditorView::getUndoList(){
    return undoList;
}
void PixelEditorView::setUndoList(vector<Stroke*> list){
    undoList = list;
}
void PixelEditorView::getUpdate(){
    update();
}

void PixelEditorView::frameClicked()
{
    resetRedoUndo();
}

void PixelEditorView::resetRedoUndo()
{
    redoList.clear();
}
