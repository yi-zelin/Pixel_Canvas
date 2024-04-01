#include "FrameBox.h"
#include <QListWidgetItem>

FrameBox::FrameBox(Model *model, QWidget *parent)
    : QWidget(parent), model(model) {

    QGridLayout *layout = new QGridLayout(this);

    QToolButton *addButton = new QToolButton(this);
    addButton->setIcon(QIcon("add"));
    layout->addWidget(addButton, 0, 0, 1, 1, Qt::AlignLeft);
    addButton->setMaximumSize(50,50);
    addButton->setStyleSheet("QToolButton { icon-size: 40px 40px; background-color: white; }");

    QToolButton *deleteButton = new QToolButton(this);
    deleteButton->setIcon(QIcon("add"));
    layout->addWidget(deleteButton, 1, 0, 1, 1, Qt::AlignLeft);
    deleteButton->setMaximumSize(50,50);
    deleteButton->setStyleSheet("QToolButton { icon-size: 40px 40px; background-color: white; }");

}

void FrameBox::addFrame(const QImage &frameImage) {

}

void FrameBox::selectFrame(int frameIndex) {
    if (frameIndex >= 0 && frameIndex < listWidget->count()) {
        listWidget->setCurrentRow(frameIndex);
    }
}

FrameBox::~FrameBox() {
    // Qt's parent-child relationship will delete the listWidget automatically
}
