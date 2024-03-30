#ifndef MODEL_H
#define MODEL_H
#include <QWidget>
#include <QList>
#include <QString>
#include "Frame.h"
#include <QGraphicsScene>


class Model: public QObject{
public:
    Model(QObject *parent = nullptr);
    ~Model();
    void drawPixel(int x, int y, const QColor &color);

public slots:
    void mouseClicked(int x, int y);


signals:



private:
    QList<Frame> frames;
    int nowediting;
};

#endif // SPRITEFRAMEMODEL_H
