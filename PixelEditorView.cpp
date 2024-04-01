#include "PixelEditorView.h"
#include <QPainter>
#include <QMouseEvent>


PixelEditorView::PixelEditorView(Model *model, QWidget *parent,QColor currentColor)
    : QWidget(parent), model(model),currentColor(currentColor), scale(16),lastPixelX(-1), lastPixelY(-1)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumSize(model->getCanvasImage().size());
    isDrawingEnabled=true;

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
    if (!isDrawingEnabled) return;
    currentStroke = new Stroke(currentColor);
    redoList.clear();
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
    if (!isDrawingEnabled) return;
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
                currentStroke->points->push_back({interpolatedX,interpolatedY});
            }

            update();

            // Update the last pixel position
            lastPixelX = currentPixelX;
            lastPixelY = currentPixelY;
        }
    }
}

void PixelEditorView::mouseReleaseEvent(QMouseEvent* event)
{
    undoList.push_back(currentStroke);
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
    isDrawingEnabled=active;
    if(active) {
        if (!isEraserMode) {
            previousColor = currentColor;}
        currentColor = QColor(Qt::white);
        isEraserMode = true;
    } else {
        isDrawingEnabled=false;

    }
}
void PixelEditorView::setPenMode(bool active){
    isDrawingEnabled=active;
    if(active){
        if (isEraserMode) {
            currentColor = previousColor;
        }
        isEraserMode = false;
    }

    else
        isDrawingEnabled=false;
}
void PixelEditorView::setCurrentColor(const QColor &color) {
    currentColor = color;
    isDrawingEnabled = true;
}

void PixelEditorView::setUndo(){
    undoClicked();
}
void PixelEditorView::setRedo(){
    redoClicked();
}

void PixelEditorView::saveClicked() {
    saveJsonToFile(convertIntoJson(undoList));
}


void PixelEditorView::loadClicked()
{
    vector<Stroke*> strokes;
    loadJsonFromFile(strokes);
    redraw(strokes);
}

QJsonDocument PixelEditorView::convertIntoJson(vector<Stroke*> image)
{
    QJsonArray strokesArray;
    for (const auto stroke : image)
        strokesArray.append(stroke -> toJson());
    return QJsonDocument(strokesArray);
}

void PixelEditorView::saveJsonToFile(const QJsonDocument &document) {
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

void PixelEditorView::loadJsonFromFile(vector<Stroke*> &strokes) {
    QString fileName = QFileDialog::getOpenFileName(this, QObject::tr("Open File"), "", QObject::tr("JSON Files (*.ssp)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    const QJsonArray strokesArray = loadDoc.array();
    for (const QJsonValue &value : strokesArray) {
        QJsonObject strokeObject = value.toObject();

        Stroke stroke(QColor(strokeObject["color"].toString()));

        QJsonArray pointsArray = strokeObject["points"].toArray();
        for (const QJsonValue &pointValue : pointsArray) {
            QJsonObject pointObject = pointValue.toObject();
            stroke.points->push_back({pointObject["x"].toInt(),pointObject["y"].toInt()});
        }
        strokes.push_back(&stroke);
    }
}

PixelEditorView::~PixelEditorView() {

}
