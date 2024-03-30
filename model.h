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

    void addFrame(const QString& framePath);
    void removeFrame(int index);
    QString getFrame(int index) const;
    int frameCount() const;

    QString exportToJson() const;
    void importFromJson(const QString& jsonStr);

private:
    QList<Canvas> frames;
};

#endif // SPRITEFRAMEMODEL_H
