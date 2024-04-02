#include "model.h"

Model::Model(int width, int height, QObject *parent)
    : QObject(parent), canvasImage(width, height, QImage::Format_ARGB32_Premultiplied) {
    canvasImage.fill(Qt::white); // 初始化为白色或透明背景
}

void Model::setPixel(int x, int y, const QColor &color) {
    if (x >= 0 && x < canvasImage.width() && y >= 0 && y < canvasImage.height()) {
        canvasImage.setPixelColor(x, y, color);
        emit imageChanged(); // 发出图像更改的信号
    }
}

QColor Model::getPixel(int x, int y) const {
    if (x >= 0 && x < canvasImage.width() && y >= 0 && y < canvasImage.height()) {
        return canvasImage.pixelColor(x, y);
    }
    return QColor(); // 如果坐标无效，返回默认颜色
}

const QImage& Model::getCanvasImage() const {
    return canvasImage;
}

void Model::clearImage() {
    canvasImage.fill(Qt::white); // 或使用适当的背景颜色填充
    emit imageChanged(); // 发出图像更改的信号
}

QSize Model::getSize(){
    return canvasImage.size();
}
