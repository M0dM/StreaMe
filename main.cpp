#include <QApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    ControllerView controllerView();
    return a.exec();*/


    QApplication a(argc, argv);

    Controller controller;
    controller.ShowMainWindow();
    return a.exec();


}
