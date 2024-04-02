#ifndef FRAMEBOX_H
#define FRAMEBOX_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QToolButton>
#include "model.h"

class FrameBox : public QWidget {
    Q_OBJECT

public:
    explicit FrameBox(Model *model, QWidget *parent = nullptr);
    ~FrameBox() override;

signals:

    void callUpDate();

public slots:
    void addFrame();
    void deleteFrame();
    void selectFrame(int frameIndex);

private:
    void frameSelected(int frameIndex);
    QListWidget *listWidget;
    Model *model;
    QVector<QImage> listFrames;
    QVector<QToolButton> selectFrames;
    QVector<bool> isDeleted;
    int nowEditing;
    QGridLayout *layout;
    int frameCount;
};

#endif // FRAMEBOX_H
