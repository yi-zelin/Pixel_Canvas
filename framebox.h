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
    void frameSelected(int frameIndex);

public slots:
    void addFrame();
    void deleteFrame();
    void selectFrame(int frameIndex);

private:
    QListWidget *listWidget;
    Model *model;
    QList<QImage> listFrames;
    int nowEditing;
    QGridLayout *layout;
};

#endif // FRAMEBOX_H
