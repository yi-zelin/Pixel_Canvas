#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include <QString>



class Model {
public:
    Model(QWidget *parent = nullptr);
    ~Model();
public slots:
    void mouseClicked(int x, int y);
signals:



private:

};

#endif // SPRITEFRAMEMODEL_H
