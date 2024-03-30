#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    model = new Model(); //
    connect(ui->MainCanvas, &CustomGraphicsView::mouseClicked, this, &MainWindow::handleMouseClicked);



}

void MainWindow::handleMouseClicked(int x, int y) {
    // Assuming pixelSize is accessible here, or you need to adjust coordinates based on your scene scale
    model->drawPixel(x / model->getXSize(), y / model->getYSize(), Qt::black); // Or use a selected color
}


MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}


