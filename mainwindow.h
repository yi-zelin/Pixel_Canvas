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
public slots:

private:
    Ui::MainWindow *ui;
    PixelEditorView *pixelEditorView;
    PixelEditorView *pixelEditorView2;
    Toolbox *tool;
    Model *model;
    Model *model2;
    QDockWidget *toolboxDock;
    QColor *currentColor;

    void connectSignalsSlots();

};

#endif // MAINWINDOW_H
