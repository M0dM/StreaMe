#include <QApplication>
#include "controllerview.h"

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    ControllerView controllerView();
    return a.exec();*/


    QApplication a(argc, argv);

    ControllerView controllerView;
    controllerView.ShowMainWindow();
    return a.exec();


}
