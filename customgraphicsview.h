#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class CustomGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    explicit CustomGraphicsView(QWidget *parent = nullptr);

signals:
    void mouseClicked(int x, int y);

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CUSTOMGRAPHICSVIEW_H
