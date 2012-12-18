#include "controller.h"

Controller::Controller()
{
    this->mainwindow = new MainWindow();
}

void Controller::ShowMainWindow(){
    this->mainwindow->showMaximized();
}
