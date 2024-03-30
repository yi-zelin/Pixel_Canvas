#include "Pixel.h"

Pixel::Pixel() : red(0), green(0), blue(0) {
    // 默认构造函数体，初始化为黑色
}

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b)
    : red(r), green(g), blue(b) {
    // 带参数的构造函数，用于初始化RGB值
}

Pixel::~Pixel() {
    // 析构函数，如果需要可以在这里执行清理操作
}

void Pixel::setRGB(unsigned char r, unsigned char g, unsigned char b) {
    red = r;
    green = g;
    blue = b;
}

unsigned char Pixel::getR() const {
    return red;
}

unsigned char Pixel::getG() const {
    return green;
}

unsigned char Pixel::getB() const {
    return blue;
}
