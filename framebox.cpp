#include "FrameBox.h"
#include <QListWidgetItem>

FrameBox::FrameBox(Model *model, QWidget *parent)
    : QWidget(parent), model(model), nowEditing(0),listFrames({}),isDeleted({false}) {

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
    connect(deleteButton, &QToolButton::clicked, this, &FrameBox::deleteFrame);

    QToolButton *firstFrame = new QToolButton(this);


    layout->addWidget(firstFrame, 0, 1, 1, 1, Qt::AlignLeft);
    firstFrame->setMaximumSize(150, 150);
    firstFrame->setStyleSheet("QToolButton { icon-size: 100px 100px; background-color: white; }");
    connect(firstFrame, &QToolButton::clicked, this,[this]() {
        this->selectFrame(0);
    });

    QImage whiteImage (model->getSize().height(), model->getSize().height(), QImage::Format_RGB32);
    listFrames.push_back(whiteImage);
    frameCount++;
}

void FrameBox::addFrame() {

    QToolButton *newFrame = new QToolButton(this);
    int frameIndex = layout->columnCount() - 1;
    layout->addWidget(newFrame, 0, frameIndex +  1, 1, 1, Qt::AlignLeft); // Add to the new row, column 0
    newFrame->setMaximumSize(150, 150);
    newFrame->setStyleSheet("QToolButton { icon-size: 100px 100px; background-color: white; }");
    connect(newFrame, &QToolButton::clicked, this,[this, frameIndex]() {
        this->selectFrame(frameIndex);
    });
    isDeleted.push_back(false);
    QImage whiteImage (model->getSize().height(), model->getSize().height(), QImage::Format_RGB32);
    whiteImage.fill(Qt::white);
    listFrames.push_back(whiteImage);


}

void FrameBox::selectFrame(int frameIndex) {
    QImage nowImage = model->getCanvasImage();

    QLayoutItem* editingFrame = layout->itemAtPosition(0, nowEditing + 1);
    QToolButton *editingButton = qobject_cast<QToolButton*>(editingFrame->widget());
    QPixmap pixmap = QPixmap::fromImage(nowImage);
    QIcon icon(pixmap);
    editingButton->setIcon(icon);

    listFrames[nowEditing] = nowImage;
    QImage selectedImage = listFrames[frameIndex];
    model->canvasImage =selectedImage;
    nowEditing = frameIndex;
    emit callUpDate();



}

void FrameBox::deleteFrame() {
    int frameCount = 0;
    for(bool b : isDeleted){
        if(!b)frameCount++;
    }
    if(frameCount==1){
        return;
    }
    isDeleted[nowEditing] = true;
    QImage selectedImage = listFrames[nowEditing];
    model->canvasImage =selectedImage;
    QLayoutItem* editingFrame = layout->itemAtPosition(0, nowEditing + 1 );
    QToolButton *editingButton = qobject_cast<QToolButton*>(editingFrame->widget());
    editingButton->deleteLater();
    for(int i=nowEditing ;  ; i++){
        if(i == isDeleted.size()){
            i=0;
        }
        if(!isDeleted[i]){
            selectFrame(i);
            break;
        }
    }

}

FrameBox::~FrameBox() {
    // Qt's parent-child relationship will delete the listWidget automatically
}
