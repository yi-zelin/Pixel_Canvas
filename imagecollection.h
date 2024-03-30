#ifndef IMAGECOLLECTION_H
#define IMAGECOLLECTION_H

#include <vector>
#include <QString>
#include "Canvas.h" // 这里是你的Canvas类定义

class ImageCollection {
public:
    ImageCollection() = default;
    ~ImageCollection() = default;

    void addCanvas(const Canvas& canvas);
    void removeCanvas(size_t index);
    Canvas getCanvas(size_t index) const;
    size_t getCanvasCount() const;

    QString toJSON() const; // 将集合导出为JSON字符串
    void fromJSON(const QString& jsonString); // 从JSON字符串导入集合

private:
    std::vector<Canvas> canvases;
};

#endif // IMAGECOLLECTION_H
