#include <QApplication>

#include <iostream>

#include "controller.h"
#include "winavtools.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller controller;

    controller.ShowMainWindow();

    controller.captureFileTest();

    return a.exec();

}
