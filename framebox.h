#ifndef FRAMEBOX_H
#define FRAMEBOX_H

#include <QWidget>
#include <QListWidget>
#include "model.h"
#include <QVBoxLayout>
#include <QToolButton>
class FrameBox : public QWidget {
    Q_OBJECT

public:
    explicit FrameBox(Model *model, QWidget *parent = nullptr);
    ~FrameBox() override;

signals:
    void frameSelected(int frameIndex);

public slots:
    void addFrame(const QImage &frameImage);
    void selectFrame(int frameIndex);

private:
    QListWidget *listWidget;
    Model *model;
};

#endif // FRAMEBOX_H
