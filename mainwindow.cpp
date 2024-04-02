#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QStringList scaleOptions = {"1*1", "2*2", "4*4", "8*8", "16*16", "32*32", "64*64"};
    bool ok;
    QString selectedScale = QInputDialog::getItem(this, tr("Select Canvas Scale"), tr("Canvas Scale:"), scaleOptions, 0, false, &ok);
    if (ok && !selectedScale.isEmpty()) {
        QStringList number = selectedScale.split('*');
        int widthTimesHeight = number.at(0).toInt();
        model = new Model(widthTimesHeight, widthTimesHeight, this);
    } else {
        model = new Model(64, 64, this);
    }
    pixelEditorView = new PixelEditorView(model, this,QColor(Qt::black),16,true);
    pixelEditorView2 = new PixelEditorView(model, this,QColor(Qt::black),4,false);
    tool = new Toolbox(model, this);
    toolboxDock = new QDockWidget(tr("Tools"), this);
    toolboxDock->setWidget(tool);
    toolboxDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

    addDockWidget(Qt::LeftDockWidgetArea, toolboxDock);

    setCentralWidget(pixelEditorView);

    frameBox = new FrameBox(model, this);
    frameBoxDock = new QDockWidget(tr("Frames"), this);
    frameBoxDock -> setWidget(frameBox);
    addDockWidget(Qt::BottomDockWidgetArea, frameBoxDock);
    //connect(frameBox, &FrameBox::frameSelected, this, &YourMainWindowClass::onFrameSelected);
    connect(frameBox, &FrameBox::callUpDate, pixelEditorView, &PixelEditorView::getUpdate);
    // 连接信号和槽
    connectSignalsSlots();

    connect(tool, &Toolbox::eraserModeChanged, pixelEditorView, &PixelEditorView::setEraserMode);
    connect(tool, &Toolbox::penModeChanged, pixelEditorView, &PixelEditorView::setPenMode);

    connect(tool, &Toolbox::fillModeChanged, pixelEditorView, &PixelEditorView::setFillMode);
    connect(tool, &Toolbox::lineModeChanged, pixelEditorView, &PixelEditorView::setLineMode);
    connect(tool, &Toolbox::rectangleModeChanged, pixelEditorView, &PixelEditorView::setRectangleMode);

    connect(tool, &Toolbox::undoChanged, pixelEditorView, &PixelEditorView::setUndo);
    connect(tool, &Toolbox::redoChanged, pixelEditorView, &PixelEditorView::setRedo);

    connect(tool, &Toolbox::colorChanged, pixelEditorView, &PixelEditorView::setCurrentColor);

    connect(tool, &Toolbox::saveChanged, pixelEditorView, &PixelEditorView::saveClicked);
    connect(tool, &Toolbox::loadChanged, pixelEditorView, &PixelEditorView::loadClicked);


    QDockWidget *dockWidget = new QDockWidget(this);
    dockWidget->setWindowTitle(tr("Canvas"));
    dockWidget->setWidget(pixelEditorView2);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);
    dockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

}
MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::connectSignalsSlots() {
    connect(model, &Model::imageChanged, pixelEditorView, static_cast<void (QWidget::*)()>(&QWidget::update));
    connect(model, &Model::imageChanged, pixelEditorView2, static_cast<void (QWidget::*)()>(&QWidget::update));
}


