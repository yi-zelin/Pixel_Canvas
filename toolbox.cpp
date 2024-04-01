#include "toolbox.h"

Toolbox::Toolbox(Model *model, QWidget *parent) {
    QGridLayout *layout = new QGridLayout(this);


    // Pen tool button
    QToolButton *penButton = new QToolButton(this);
    penButton->setIcon(QIcon(":/new/icons/pen.jpg")); // Adjust the path to your icon
    penButton->setCheckable(true); // Optional: make the button checkable
    penButton->setChecked(true);
    layout->addWidget(penButton, 0, 0);
    penButton->setMaximumSize(50,50);
    penButton->setStyleSheet("QToolButton { icon-size: 40px 40px; background-color: white; }");

    // Eraser tool button
    QToolButton *eraserButton = new QToolButton(this);
    eraserButton->setIcon(QIcon(":/new/icons/eraser.jpg")); // Adjust the path to your icon
    eraserButton->setCheckable(true); // Optional: make the button checkable
    layout->addWidget(eraserButton, 0, 1);
    eraserButton->setMaximumSize(50,50);
    eraserButton->setStyleSheet("QToolButton { icon-size: 40px 40px; background-color: white; }");

    QToolButton *color = new QToolButton(this);
    color->setIcon(QIcon(":/new/icons/images.png")); // Adjust the path to your icon
     // Optional: make the button checkable
    layout->addWidget(color, 1, 0);
    color->setMaximumSize(50,50);
    color->setStyleSheet("QToolButton { icon-size: 30px 30px; background-color: white; }");

    QToolButton *shape = new QToolButton(this);
    shape->setIcon(QIcon(":/new/icons/shape.png")); // Adjust the path to your icon
    shape->setCheckable(true); // Optional: make the button checkable
    layout->addWidget(shape, 1, 1);
    shape->setMaximumSize(50,50);
    shape->setStyleSheet("QToolButton { icon-size: 30px 30px; background-color: white; }");

    QToolButton *redo = new QToolButton(this);
    redo->setIcon(QIcon(":/new/icons/redo.png")); // Adjust the path to your icon
    layout->addWidget(redo, 2, 1);
    redo->setMaximumSize(50,50);
    redo->setStyleSheet("QToolButton { icon-size: 30px 30px; background-color: white; }");

    QToolButton *undo = new QToolButton(this);
    undo->setIcon(QIcon(":/new/icons/undo.png")); // Adjust the path to your icon
    layout->addWidget(undo, 2, 0);
    undo->setMaximumSize(50,50);
    undo->setStyleSheet("QToolButton { icon-size: 30px 30px; background-color: white; }");

    QToolButton *import = new QToolButton(this);
    import->setIcon(QIcon(":/new/icons/import.png")); // Adjust the path to your icon
    layout->addWidget(import, 3, 0);
    import->setMaximumSize(50,50);
    import->setStyleSheet("QToolButton { icon-size: 30px 30px; background-color: white; }");

    QToolButton *export1 = new QToolButton(this);
    export1->setIcon(QIcon(":/new/icons/export.png")); // Adjust the path to your icon
    layout->addWidget(export1, 3, 1);
    export1->setMaximumSize(50,50);
    export1->setStyleSheet("QToolButton { icon-size: 30px 30px; background-color: white; }");
    connect(eraserButton, &QToolButton::toggled, this, &Toolbox::eraserModeChanged);
    connect(penButton, &QToolButton::toggled, this, &Toolbox::penModeChanged);
    connect(redo, &QToolButton::clicked, this, &Toolbox::redoChanged);
    connect(undo, &QToolButton::clicked, this, &Toolbox::undoChanged);
    connect(export1, &QToolButton::clicked, this, &Toolbox::saveChanged);
    connect(import, &QToolButton::clicked, this, &Toolbox::loadChanged);

    connect(penButton, &QToolButton::toggled, this, [this, eraserButton, shape](bool checked) {
        if (checked) {
            eraserButton->setChecked(false);
            shape->setChecked(false);
            emit penModeChanged(true);

        } else {
            emit penModeChanged(false);
        }
    });
    connect(eraserButton, &QToolButton::toggled, this, [this, penButton, shape](bool checked) {
        if (checked) {
            penButton->setChecked(false);
            shape->setChecked(false);
            emit eraserModeChanged(true);
        } else {
            emit eraserModeChanged(false);
        }
    });
    connect(shape, &QToolButton::toggled, this, [this, eraserButton, penButton](bool checked) {
        if (checked) {
            eraserButton->setChecked(false);
            penButton->setChecked(false);
            emit fillModeChanged(true);

        } else {
            emit fillModeChanged(false);
        }
    });

    connect(color, &QToolButton::clicked, this, [this, eraserButton, penButton]() {
        QColor selectedColor = QColorDialog::getColor(Qt::black, this, "Select Color");
        if (selectedColor.isValid()) {
            eraserButton->setChecked(false);
            penButton->setChecked(true);
            emit eraserModeChanged(false);
            emit penModeChanged(true);
            emit colorChanged(selectedColor);
        }
    });



}
