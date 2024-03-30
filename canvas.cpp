#include "canvas.h"

Canvas::Canvas(int width, int height) : width(width), height(height) {
    pixels = std::vector<std::vector<Pixel>>(height, std::vector<Pixel>(width, Pixel()));
}

Canvas::~Canvas() {
    // 析构函数，进行必要的清理
}

int Canvas::getWidth(){
    return pixels[0].size();
}


int Canvas::getHeight(){
    return pixels.size();
}


void Canvas::setPixel(int x, int y, const Pixel& pixel) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        pixels[y][x] = pixel;
    }
}

Pixel Canvas::getPixel(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return pixels[y][x];
    }
    return Pixel(); // 返回一个默认Pixel对象，可能需要更合理的错误处理
}


