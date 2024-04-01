#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    bool ok;
    int width = QInputDialog::getInt(this, tr("Canvas Width"), tr("Enter canvas width:"), 50, 1, 1000, 1, &ok);
    if (!ok) return;

    int height = QInputDialog::getInt(this, tr("Canvas Height"), tr("Enter canvas height:"), 50, 1, 1000, 1, &ok);
    if (!ok) return;
    model = new Model(width, height, this);
    pixelEditorView = new PixelEditorView(model, this,*currentColor,16,true);
    pixelEditorView2 = new PixelEditorView(model, this,*currentColor,4,false);
    tool = new Toolbox(model, this);
    toolboxDock = new QDockWidget(tr("Tools"), this);
    toolboxDock->setWidget(tool);
    toolboxDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

    addDockWidget(Qt::LeftDockWidgetArea, toolboxDock);

    setCentralWidget(pixelEditorView);

    connectSignalsSlots();

    connect(tool, &Toolbox::eraserModeChanged, pixelEditorView, &PixelEditorView::setEraserMode);
    connect(tool, &Toolbox::penModeChanged, pixelEditorView, &PixelEditorView::setPenMode);
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


