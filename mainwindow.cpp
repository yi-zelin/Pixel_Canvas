#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( Model *model ,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , allModel(model)
{
    ui->setupUi(this);
    connect(allModel, &Model::frameAdded, this, &MainWindow::onFrameAdded);
    connect(allModel, &Model::frameUpdated, this, &MainWindow::onFrameUpdated);



    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene); // ui->graphicsView 应该是一个 QGraphicsView 的对象

    // 假设我们正在编辑第一个帧
    CanvasItem *item = new CanvasItem(&model->getFrame(0));
    scene->addItem(item);

}

MainWindow::~MainWindow()
{
    delete ui;
}
