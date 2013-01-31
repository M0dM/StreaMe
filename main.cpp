#include <QApplication>

#include "controller.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller controller;

    controller.ShowMainWindow();

    controller.displayFreeSources();

    //controller.twitchStream();

    return a.exec();

}
