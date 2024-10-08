#ifndef FRAMEBOX_H
#define FRAMEBOX_H
/*
Framebox header for framebox class
By Kai-Chen Chiang,jinchao liang, Rishen Cao, Zelin Yi, Shuangji Li,Yuang sun
*/
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QToolButton>
#include "model.h"
#include "stroke.h"
#include <QTimer>
#include "PixelEditorView.h"
#include <QLineEdit>
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
    void previewFrame();
    void selectFrame(int frameIndex);
    void setPrevFps();
    void setPreviewTime();

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
    int previewSpeed;
    int previewTime;

};

#endif // FRAMEBOX_H
