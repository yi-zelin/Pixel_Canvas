#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMovie>
#include <QDebug>

#include "model.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr );
    ~MainWindow();


public slots:


private slots:
    void handleMouseClicked(int x, int y);

private:
    Ui::MainWindow *ui;
    Model *model;
};
#endif // MAINWINDOW_H
