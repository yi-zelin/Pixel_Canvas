#ifndef CANVAS_H
#define CANVAS_H
#include <QImage>
#include <vector>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "Pixel.h" // 确保Pixel类适用于Qt

class Canvas {
public:
    Canvas(int width, int height);
    ~Canvas();

    void setPixel(int x, int y, const Pixel& pixel);
    Pixel getPixel(int x, int y) const;

    int getWidth();
    int getHeight();


private:
    int width, height;
    std::vector<std::vector<Pixel>> pixels;
    std::vector<QString> editHistory; // 存储JSON字符串表示的编辑历史
};

#endif // CANVAS_H
