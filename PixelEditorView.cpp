#include "PixelEditorView.h"
#include <QPainter>
#include <QMouseEvent>


PixelEditorView::PixelEditorView(Model *model, QWidget *parent,QColor currentColor,int scale,bool state)
    : QWidget(parent), model(model),currentColor(currentColor), scale(scale),lastPixelX(-1), lastPixelY(-1)
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
    } else if (isFillMode){
        fill(pixelX, pixelY);
        undoList.push_back(currentStroke);
        update();
    }
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
    if (isDrawingEnabled){
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
    if(active) {
        if (!isEraserMode)
            previousColor = currentColor;
        currentColor = QColor(Qt::white);
        isEraserMode = true;
        isDrawingEnabled = true;
    } else {
        isDrawingEnabled=false;
        isEraserMode = false;
    }
}
void PixelEditorView::setPenMode(bool active){
    isFillMode = false;
    if(active){
        if (isEraserMode)
            currentColor = previousColor;
        isDrawingEnabled = true;
        isEraserMode = false;
    }
    else{
        isDrawingEnabled=false;
        isEraserMode = false;
    }
}

void PixelEditorView::setFillMode(bool active){
    if(active){
        isDrawingEnabled = false;
        isFillMode = true;
        isEraserMode = false;
    }
    else{
        isDrawingEnabled=false;
        isFillMode = false;
        isEraserMode = false;
    }
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

void PixelEditorView::fill(int x, int y){
    // if x, y valid
     if (x < 0 || y < 0 || x > model->getCanvasImage().width() || y > model->getCanvasImage().width())
         return;
    if (model->getPixel(x,y) == QColor(Qt::white)){

        model->setPixel(x, y, currentColor);
        currentStroke->points->push_back({x, y});

        fill(x+1, y);
        fill(x-1, y);
        fill(x, y+1);
        fill(x, y-1);
    }
}
void PixelEditorView::getUpdate(){
    update();
}
