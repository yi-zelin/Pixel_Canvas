#include "toolbox.h"

Toolbox::Toolbox(Model *model, QWidget *parent) {
    QGridLayout *layout = new QGridLayout(this);


    // Pen tool button
    QToolButton *penButton = new QToolButton(this);
    penButton->setIcon(QIcon(":/new/icons/pen.jpg")); // Adjust the path to your icon
    penButton->setCheckable(true); // Optional: make the button checkable
    penButton->setChecked(true);
    layout->addWidget(penButton, 0, 0);
    penButton->setMinimumSize(50,50);
    // Eraser tool button
    QToolButton *eraserButton = new QToolButton(this);
    eraserButton->setIcon(QIcon(":/new/icons/eraser.jpg")); // Adjust the path to your icon
    eraserButton->setCheckable(true); // Optional: make the button checkable
    layout->addWidget(eraserButton, 0, 1);
    eraserButton->setMinimumSize(50,50);


}
