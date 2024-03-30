#include "Frame.h"

Frame::Frame(int width, int height) : m_width(width), m_height(height) {
    m_pixels.resize(width * height, QColor(Qt::transparent)); // Initialize all pixels as transparent
}

QColor Frame::getPixel(int x, int y) const {
    return m_pixels.at(index(x, y));
}

void Frame::setPixel(int x, int y, const QColor &color) {
    m_pixels[index(x, y)] = color;
}

int Frame::getWidth() const {
    return m_width;
}

int Frame::getHeight() const {
    return m_height;
}

int Frame::index(int x, int y) const {
    return y * m_width + x;
}
