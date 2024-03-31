#ifndef PIXELEDITORVIEW_H
#define PIXELEDITORVIEW_H


#include <QWidget>
#include "Model.h" // 假设 Model 类包含 QImage 和相关的逻辑

class PixelEditorView : public QWidget {
    Q_OBJECT

public:
    explicit PixelEditorView(Model *model, QWidget *parent = nullptr);

    ~PixelEditorView() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Model *model;
    QColor currentColor;
    int scale;
    int lastPixelX;
    int lastPixelY;
};

#endif // PIXELEDITORVIEW_H
