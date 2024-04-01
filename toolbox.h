#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include "Model.h"
#include <QVBoxLayout>
#include <QToolButton>
#include <QIcon>
#include <QColorDialog>
#include "PixelEditorView.h"


class Toolbox: public QWidget
{
    Q_OBJECT
public:
    explicit Toolbox(Model *model, QWidget *parent = nullptr);
signals:
    void eraserModeChanged(bool active);
    void penModeChanged(bool active);
    void fillModeChanged(bool active);
    void redoChanged();
    void undoChanged();
    void colorChanged(const QColor &Color);
    void saveChanged();
    void loadChanged();
};

#endif // TOOLBOX_H
