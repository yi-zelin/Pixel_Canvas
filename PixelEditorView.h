#ifndef PIXELEDITORVIEW_H
#define PIXELEDITORVIEW_H


#include <QWidget>
#include "Model.h"
#include "stroke.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFileDialog>

class PixelEditorView : public QWidget {
    Q_OBJECT

public:
    explicit PixelEditorView(Model *model, QWidget *parent = nullptr,QColor currentColor = QColor(Qt::black),int scale = 16,bool state = true);
    bool isDrawingEnabled;
    QColor previousColor;
    QColor currentColor;
    bool isEraserMode;
    bool isFillMode=false;
    ~PixelEditorView() override;

public slots:
    void setEraserMode(bool active);
    void setPenMode(bool active);
    void setFillMode(bool active);
    void setRedo();
    void setUndo();
    void setCurrentColor(const QColor &color);
    void saveClicked();
    void loadClicked();
    void getUpdate();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void undoClicked();
    void redoClicked();

private:
    Model *model;
    vector<Stroke*> undoList;
    vector<Stroke*> redoList;
    Stroke *currentStroke;
    int scale;
    int lastPixelX;
    int lastPixelY;
    void redraw(vector<Stroke*> strokes);
    void saveJsonToFile(const QJsonDocument &document);
    QJsonDocument convertIntoJson(vector<Stroke*> image);
    void loadJsonFromFile(vector<Stroke*> &strokes);
    void fill(int x, int y);
};

#endif // PIXELEDITORVIEW_H
