#ifndef PIXELEDITORVIEW_H
#define PIXELEDITORVIEW_H


#include <QWidget>
#include "Model.h"

class PixelEditorView : public QWidget {
    Q_OBJECT

public:
    explicit PixelEditorView(Model *model, QWidget *parent = nullptr,QColor *currentColor =new QColor(Qt::white));

    ~PixelEditorView() override;
public slots:
    void setEraserMode(bool active);
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Model *model;
    QColor *currentColor;
    int scale;
    int lastPixelX;
    int lastPixelY;
};

#endif // PIXELEDITORVIEW_H
