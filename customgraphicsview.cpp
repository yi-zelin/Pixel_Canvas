#include "CustomGraphicsView.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

CustomGraphicsView::CustomGraphicsView(Model *model, QWidget *parent)
    : QGraphicsView(parent), model(model) {

    // 创建场景并设置
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);

    // 创建一个图像来表示画布，并将其添加到场景
    QPixmap pixmap = QPixmap::fromImage(model->getCanvasImage());
    canvasItem = scene->addPixmap(pixmap);

    // 设置视图的其他属性，如抗锯齿等
    setRenderHint(QPainter::Antialiasing, false);
    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // 初始颜色设置，假设有方法改变currentColor
    currentColor = Qt::black;
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event) {
    drawPixel(event->pos());
    QGraphicsView::mousePressEvent(event);
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event) {
    drawPixel(event->pos());
    QGraphicsView::mouseMoveEvent(event);
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    // 鼠标释放可能不需要特殊处理
    QGraphicsView::mouseReleaseEvent(event);
}

void CustomGraphicsView::drawPixel(const QPoint &pos) {
    // 转换视图坐标到场景坐标
    QPointF scenePos = mapToScene(pos);

    // 调用模型来改变像素
    model->setPixel(scenePos.x(), scenePos.y(), currentColor);

    // 更新画布显示
    canvasItem->setPixmap(QPixmap::fromImage(model->getCanvasImage()));
}

CustomGraphicsView::~CustomGraphicsView() {
    // 如果需要在这里进行清理
}
void CustomGraphicsView::drawPixel(const QPoint &pos) {
    // 在这里实现绘制像素的逻辑
    QPointF scenePos = mapToScene(pos);
    // ... 更新 model 和 canvasItem ...
}
