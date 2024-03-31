#ifndef PIXELEDITORVIEW_H
#define PIXELEDITORVIEW_H


#include <QWidget>
#include "Model.h"
#include "stroke.h"

class PixelEditorView : public QWidget {
    Q_OBJECT

public:
    explicit PixelEditorView(Model *model, QWidget *parent = nullptr,QColor *currentColor =new QColor(Qt::white));
    ~PixelEditorView() override;

public slots:
    void setEraserMode(bool active);
    void setRedo(bool active);
    void setUndo(bool active);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void undoClicked();
    void redoClicked();

private:
    Model *model;
    QColor *currentColor;
    vector<Stroke*> undoList;
    vector<Stroke*> redoList;
    Stroke *currentStroke;
    int scale;
    int lastPixelX;
    int lastPixelY;
    void reDraw();
};

#endif // PIXELEDITORVIEW_H
