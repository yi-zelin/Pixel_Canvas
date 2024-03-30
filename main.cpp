#include "mainwindow.h"
#include "model.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Model model;   // Create an instance of the game model

    MainWindow w (&model);           // Create an instance of the MainWindow

    w.show();              // Display the MainWindow
    return a.exec();       // Start the event loop
}
