#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // 创建和初始化模型，大小为50x50像素
    model = new Model(50, 50, this);

    // 创建和初始化像素编辑器视图，将模型传递给它
    pixelEditorView = new PixelEditorView(model, this);
    tool = new Toolbox(model, this);
    toolboxDock = new QDockWidget(tr("Tools"), this);
    toolboxDock->setWidget(tool);
    toolboxDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

    addDockWidget(Qt::LeftDockWidgetArea, toolboxDock);

    setCentralWidget(pixelEditorView);

    // 设置UI，例如创建动作和菜单
    setupUI();
    createActions();
    createMenus();
    createToolbars();

    // 连接信号和槽
    connectSignalsSlots();
}

MainWindow::~MainWindow() {
    delete ui;
    // 注意: Model 和 PixelEditorView 的析构在 Qt 的父子关系管理下自动处理
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
    connect(model, &Model::imageChanged, pixelEditorView, static_cast<void (QWidget::*)()>(&QWidget::update));
}
