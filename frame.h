#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <QColor>

class Frame {
public:
    Frame(int width, int height);
    ~Frame() = default;

    QColor getPixel(int x, int y) const;
    void setPixel(int x, int y, const QColor &color);

    int getWidth() const;
    int getHeight() const;

private:
    std::vector<QColor> m_pixels;
    int m_width;
    int m_height;

    int index(int x, int y) const;
};

#endif // FRAME_H
