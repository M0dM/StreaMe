#include "controller.h"

Controller::Controller()
{
    this->mainwindow = new MainWindow(this);
}

void Controller::ShowMainWindow(){
    this->mainwindow->showMaximized();
}
