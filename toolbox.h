#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include "Model.h"
#include <QVBoxLayout>
#include <QToolButton>
#include <QIcon>

class Toolbox: public QWidget
{
    Q_OBJECT
public:
    explicit Toolbox(Model *model, QWidget *parent = nullptr);
signals:
    void eraserModeChanged(bool active);
    void redoChanged();
    void undoChanged();
};

#endif // TOOLBOX_H
