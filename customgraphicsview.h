#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QGraphicsScene>
#include "Model.h"

class CustomGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
   CustomGraphicsView(Model *model, QWidget *parent = nullptr);
   void drawPixel(const QPoint &pos);


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QGraphicsLineItem* currentLine;  // 当前正在绘制的线条
    QGraphicsScene* scene;           // 场景
    QColor currentColor;             // 当前选择的颜色
    qreal penWidth;                  // 笔触宽度
    QGraphicsPixmapItem *canvasItem; // 确保这一行存在
};

#endif // CUSTOMGRAPHICSVIEW_H
