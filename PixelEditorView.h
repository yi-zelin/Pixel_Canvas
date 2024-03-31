#ifndef PIXELEDITORVIEW_H
#define PIXELEDITORVIEW_H


#include <QWidget>
#include <stack>
#include "Model.h" // 假设 Model 类包含 QImage 和相关的逻辑
#include "stroke.h"
using std::stack;

class PixelEditorView : public QWidget {
    Q_OBJECT

public:
    explicit PixelEditorView(Model *model, QWidget *parent = nullptr);

    ~PixelEditorView() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void undoClicked();
    void redoClicked();

private:
    Model *model;
    QColor currentColor;
    stack<Stroke*> undoList;
    stack<Stroke*> redoList;
    Stroke *currentStroke;
    int scale;
    int lastPixelX;
    int lastPixelY;
    void reDraw();
};

#endif // PIXELEDITORVIEW_H
