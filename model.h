#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QColor>
#include <QList>
#include "PixelItem.h"

class Model : public QObject {
    Q_OBJECT

public:
    Model(QObject *parent = nullptr);

    void createPixelItems(int width, int height);
    QList<PixelItem *> getPixelItems() const;

private:
    QList<PixelItem *> pixelItems;
};

#endif // MODEL_H
