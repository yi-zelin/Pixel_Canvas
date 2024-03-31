#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QMainWindow>
#include "PixelEditorView.h"
#include "Model.h"
#include "toolBox.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    PixelEditorView *pixelEditorView;
    Toolbox *tool;
    Model *model;
    QDockWidget *toolboxDock;
    QColor *currentColor;

    // UI相关的函数，如创建菜单、工具栏、状态栏等
    void setupUI();
    void createActions();
    void createMenus();
    void createToolbars();
    void connectSignalsSlots();
};

#endif // MAINWINDOW_H
