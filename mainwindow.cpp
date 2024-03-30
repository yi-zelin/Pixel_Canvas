#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( Model *model ,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , allModel(model)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}
