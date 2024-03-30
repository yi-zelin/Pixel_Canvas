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


public slots:
    void mouseClicked(int x, int y);


signals:



private:

};

#endif // SPRITEFRAMEMODEL_H
