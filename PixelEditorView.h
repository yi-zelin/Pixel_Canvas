/*
 *The header files for pixelEditorView.cpp
 *Author:Kai-chen Chiang, Rishen Cao, Yuang Sun, JinChao Liang, Shuangji Li, Yize Lin
*/

#ifndef PIXELEDITORVIEW_H
#define PIXELEDITORVIEW_H
/*
PixelEditorView header for PixelEditorView class
By Kai-Chen Chiang,jinchao liang, Rishen Cao, Zelin Yi, Shuangji Li,Yuang sun
*/

#include <QWidget>
#include "Model.h"
#include "stroke.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFileDialog>
#include <QBuffer>

class PixelEditorView : public QWidget {
    Q_OBJECT

public:
    explicit PixelEditorView(Model *model, QWidget *parent = nullptr,QColor currentColor = QColor(Qt::black),int scale = 16,bool state = true);
    bool isDrawingEnabled;
    QColor previousColor;
    QColor currentColor;
    bool isEraserMode;
    bool isFillMode=false;
    bool lineMode = false;
    bool rectangleMode = false;
    bool squareMode = false;
    vector<Stroke*> getUndoList();
    void setUndoList(vector<Stroke*>);
    ~PixelEditorView() override;
    Model *model;


public slots:
    void setEraserMode(bool active);
    void setPenMode(bool active);
    void setFillMode(bool active);
    void setLineMode(bool active);
    void setRectangleMode(bool active);
    void setRedo();
    void setUndo();
    void setCurrentColor(const QColor &color);
    void saveClicked();
    void loadClicked();
    void getUpdate();
    void frameClicked();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void undoClicked();
    void redoClicked();
    void resetRedoUndo();

private:
    vector<Stroke*> undoList;
    vector<Stroke*> redoList;
    Stroke *currentStroke;
    int scale;
    int lastPixelX;
    int lastPixelY;
    void redraw(vector<Stroke*> strokes);
    void saveJsonToFile( QJsonDocument &document);
    QJsonDocument convertIntoJson( QImage image );
    void loadJsonFromFile();
    void fill(int x, int y);
    bool state;
};

#endif
