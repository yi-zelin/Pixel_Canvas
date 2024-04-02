#include "FrameBox.h"
#include <QListWidgetItem>

FrameBox::FrameBox(Model *model, QWidget *parent)
    : QWidget(parent), model(model), nowEditing(0) {


    layout = new QGridLayout(this);

    QToolButton *addButton = new QToolButton(this);
    addButton->setText("add");
    layout->addWidget(addButton, 0, 0, 1, 1, Qt::AlignLeft);
    addButton->setMaximumSize(50,50);
    addButton->setStyleSheet("QToolButton { icon-size: 40px 40px; background-color: white; }");
    connect(addButton, &QToolButton::clicked, this, &FrameBox::addFrame);

    QToolButton *deleteButton = new QToolButton(this);
    deleteButton->setText("delete");
    layout->addWidget(deleteButton, 1, 0, 1, 1, Qt::AlignLeft);
    deleteButton->setMaximumSize(50,50);
    deleteButton->setStyleSheet("QToolButton { icon-size: 40px 40px; background-color: white; }");
    connect(addButton, &QToolButton::clicked, this, &FrameBox::deleteFrame);
    addFrame();

}

void FrameBox::addFrame() {

    QToolButton *newFrame = new QToolButton(this);
    int frameIndex = layout->columnCount();
    newFrame->setText(QString::number(frameIndex + 1)); // Label the button with the frame number
    layout->addWidget(newFrame, 0, frameIndex, 1, 1, Qt::AlignLeft); // Add to the new row, column 0
    newFrame->setMaximumSize(50, 50);
    newFrame->setStyleSheet("QToolButton { icon-size: 40px 40px; background-color: white; }");
    connect(newFrame, &QToolButton::clicked, this,[this, frameIndex]() {
        this->selectFrame(frameIndex);
    });


}

void FrameBox::selectFrame(int frameIndex) {

}

void FrameBox::deleteFrame() {



}

FrameBox::~FrameBox() {
    // Qt's parent-child relationship will delete the listWidget automatically
}
