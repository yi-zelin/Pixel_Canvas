#include "FrameBox.h"
#include <QListWidgetItem>

FrameBox::FrameBox(Model *model,PixelEditorView *view, QWidget *parent )
    : QWidget(parent), model(model), listFrames({}),isDeleted({false}),nowEditing(0) ,redoLists({{}}),view(view) {
    previewSpeed = 30;
    previewTime=100;
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

    QToolButton *previewButton = new QToolButton(this);
    previewButton->setText("preview");
    layout->addWidget(previewButton, 2, 0, 1, 1, Qt::AlignLeft);
    previewButton->setMaximumSize(50,50);
    previewButton->setStyleSheet("QToolButton { icon-size: 40px 40px; background-color: white; }");
    connect(previewButton, &QToolButton::clicked, this, &FrameBox::previewFrame);

    QToolButton *firstFrame = new QToolButton(this);
    layout->addWidget(firstFrame, 0, 1, 1, 1, Qt::AlignLeft);
    firstFrame->setMaximumSize(150, 150);
    firstFrame->setStyleSheet("QToolButton { icon-size: 100px 100px; background-color: white; }");
    connect(firstFrame, &QToolButton::clicked, this,[this]() {
        this->selectFrame(0);
    });

    QLineEdit *previewFPS = new QLineEdit(this);
    previewFPS -> setPlaceholderText("Enter FPS");
    layout->addWidget(previewFPS, 3, 0, 1, 1, Qt::AlignLeft);
    connect(previewFPS, &QLineEdit::returnPressed, this, &FrameBox::setPrevFps);

    QLineEdit *previewRep = new QLineEdit(this);
    layout->addWidget(previewRep, 4, 0, 1, 1, Qt::AlignLeft);
    previewRep -> setPlaceholderText("Enter repeat time");



    QImage whiteImage (model->getSize().height(), model->getSize().height(), QImage::Format_RGB32);
    listFrames.push_back(whiteImage);
    frameCount++;
}

void FrameBox::addFrame() {
    redoLists.push_back(vector<Stroke*>{});
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
    redoLists[nowEditing] = view->getUndoList();
    view->setUndoList(redoLists[frameIndex]);
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
void FrameBox::setPrevFps(){
    QLineEdit *FPS = qobject_cast<QLineEdit*>(layout->itemAtPosition(3, 0)->widget());
    QString text = FPS->text();
    bool ok;
    int speed = text.toInt(&ok);
    if (ok) {
        previewSpeed = speed;
    } else {
        FPS->setText("please Enter an int");
    }
}

void FrameBox::setPreviewTime(){
    QLineEdit *repeat = qobject_cast<QLineEdit*>(layout->itemAtPosition(4, 0)->widget());
    QString text = repeat->text();
    bool ok;
    int time = text.toInt(&ok);
    if (ok) {
        previewTime = time;
    } else {
        repeat->setText("please Enter an int");
    }
}
void FrameBox::previewFrame() {
    int speed = 1000 / previewSpeed;
    int nowSelect = 0;
    view->isDrawingEnabled = false;

    QToolButton *addButton = qobject_cast<QToolButton*>(layout->itemAtPosition(0, 0)->widget());
    QToolButton *delButton = qobject_cast<QToolButton*>(layout->itemAtPosition(1, 0)->widget());
    QToolButton *prevButton = qobject_cast<QToolButton*>(layout->itemAtPosition(2, 0)->widget());
    addButton->setDisabled(true);
    delButton->setDisabled(true);
    prevButton->setDisabled(true);
    for(int i=1;i<100;i++){
        while(isDeleted[nowSelect]){
            nowSelect++;
        }
        QTimer::singleShot(i*previewTime, this, [this,nowSelect]() {
           selectFrame(nowSelect);
        });
        nowSelect++;
        if(nowSelect == isDeleted.size()) nowSelect =0;
    }
    QTimer::singleShot(speed*previewSpeed, this, [this,addButton,delButton,prevButton]() {
        view->isDrawingEnabled = true;
        addButton->setDisabled(false);
        delButton->setDisabled(false);
        prevButton->setDisabled(false);
    });
}

FrameBox::~FrameBox() {

}
