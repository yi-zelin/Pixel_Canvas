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

    // 编辑功能
    void setPixel(int x, int y, const Pixel& pixel);
    Pixel getPixel(int x, int y) const;

    // 撤销功能
    void undo();

    // JSON导入导出
    QString exportToJson() const;
    void importFromJson(const QString& jsonStr);
    int getWidth();
    int getHeight();
    //这个方法遍历Canvas上的所有像素，并将它们绘制到一个QImage对象上。
    void drawToImage(QImage &image) const;

private:
    int width, height;
    std::vector<std::vector<Pixel>> pixels;
    std::vector<QString> editHistory; // 存储JSON字符串表示的编辑历史
};

#endif // CANVAS_H
