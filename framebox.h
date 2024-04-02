#ifndef FRAMEBOX_H
#define FRAMEBOX_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QToolButton>
#include "model.h"
#include "stroke.h"
#include "PixelEditorView.h"
class FrameBox : public QWidget {
    Q_OBJECT

public:
    explicit FrameBox(Model *model, PixelEditorView *view, QWidget *parent = nullptr);
    ~FrameBox() override;

signals:
    void callUpDate();
    void undoReset();

public slots:
    void addFrame();
    void deleteFrame();
    void selectFrame(int frameIndex);
    void previewFrame();

private:
    void frameSelected(int frameIndex);
    QListWidget *listWidget;
    Model *model;
    QVector<QImage> listFrames;
    QVector<QToolButton> selectFrames;
    QVector<vector<Stroke*>> redoLists;
    QVector<bool> isDeleted;
    int nowEditing;
    QGridLayout *layout;
    int frameCount;
    PixelEditorView *view;
};

#endif // FRAMEBOX_H
