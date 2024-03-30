#include "ImageCollection.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

void ImageCollection::addCanvas(const Canvas& canvas) {
    canvases.push_back(canvas);
}

void ImageCollection::removeCanvas(size_t index) {
    if (index < canvases.size()) {
        canvases.erase(canvases.begin() + index);
    }
}

Canvas ImageCollection::getCanvas(size_t index) const {
    if (index < canvases.size()) {
        return canvases[index];
    }
    throw std::out_of_range("Index out of range"); // 或者返回一个默认构造的Canvas对象
}

size_t ImageCollection::getCanvasCount() const {
    return canvases.size();
}

// ... 其他包含的文件和类定义 ...

QString ImageCollection::toJSON() const {

}


void ImageCollection::fromJSON(const QString& jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    if (!doc.isArray()) {
        throw std::runtime_error("JSON string is not a valid canvas array");
    }

    QJsonArray array = doc.array();
    canvases.clear();
    for (const auto& item : array) {
        QJsonObject canvasObject = item.toObject();
        int width = canvasObject["width"].toInt();
        int height = canvasObject["height"].toInt();
        Canvas canvas(width, height);

        QJsonArray pixelsArray = canvasObject["pixels"].toArray();
        for (int y = 0; y < pixelsArray.size(); ++y) {
            QJsonArray rowArray = pixelsArray[y].toArray();
            for (int x = 0; x < rowArray.size(); ++x) {
                QJsonObject pixelObject = rowArray[x].toObject();
                int r = pixelObject["r"].toInt();
                int g = pixelObject["g"].toInt();
                int b = pixelObject["b"].toInt();
                Pixel pixel(r, g, b);
                canvas.setPixel(x, y, pixel);
            }
        }

        canvases.push_back(canvas);
    }
}
