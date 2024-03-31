#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PixelItem.h"
#include <QGraphicsScene>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建一个 QGraphicsScene
    QGraphicsScene *scene = new QGraphicsScene(this);

    const int pixelSize = 8;
    const int gridSize = 100;
    scene->setSceneRect(0, 0, gridSize * pixelSize, gridSize * pixelSize); // 设置画布大小

    // 创建像素项并添加到场景中
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            QColor color = ((i + j) % 2 == 0) ? Qt::gray : Qt::white; // 棋盘效果
            PixelItem *item = new PixelItem(i, j, color, pixelSize);
            scene->addItem(item);
        }
    }

    // 创建 QGraphicsView 并设置场景
    QGraphicsView *view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(view); // 将 QGraphicsView 设置为主窗口的中央部件
}

MainWindow::~MainWindow() {
    delete ui;
    delete model; // 如果使用了new分配model的内存
}

void MainWindow::setupUI() {
    // 初始化窗口的其他UI部分，如状态栏和停靠窗口
}

void MainWindow::createActions() {
    // 创建与用户交互相关的动作
}

void MainWindow::createMenus() {
    // 创建菜单
}

void MainWindow::createToolbars() {
    // 创建工具栏
}

void MainWindow::connectSignalsSlots() {
    // 连接模型的信号到视图的槽，以便图像变更时更新视图
}
