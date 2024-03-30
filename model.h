#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "canvas.h"


class Model {
public:
    Model();
    ~Model();
    //加帧
    void addFrame(const Canvas& frame);
    //减帧
    void removeFrame(int index);
    //选帧
    Canvas getFrame(int index) const;
    int frameCount() const;

    QString exportToJson() const;
    void importFromJson(const QString& jsonStr);

private:
    //存储用的list
    QList<Canvas> frames;
    //当前选择的颜色
    Pixel nowColor;
};

#endif // SPRITEFRAMEMODEL_H
