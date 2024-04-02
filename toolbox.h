#ifndef TOOLBOX_H
#define TOOLBOX_H
/*
toolbox header for toolbox class
By Kai-Chen Chiang,jinchao liang, Rishen Cao, Zelin Yi, Shuangji Li,Yuang sun
*/
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
    void lineModeChanged(bool active);
    void rectangleModeChanged(bool active);
    void redoChanged();
    void undoChanged();
    void colorChanged(const QColor &Color);
    void saveChanged();
    void loadChanged();
};

#endif // TOOLBOX_H
