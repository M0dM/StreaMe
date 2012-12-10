#include "mainwindow.h"
#include <QApplication>

#include "controllerview.h"

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    ControllerView controllerView();
    return a.exec();*/

    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();


}
