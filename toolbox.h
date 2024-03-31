#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include "Model.h"

class toolBox:QWidget
{
    Q_OBJECT
public:
    explicit toolBox(Model *model, QWidget *parent = nullptr);

};

#endif // TOOLBOX_H
