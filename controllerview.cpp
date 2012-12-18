#include "controllerview.h"
#include <QApplication>
#include <iostream>
using namespace std;

ControllerView::ControllerView()
{
    this->mainwindow = new MainWindow(this);
}
void ControllerView::ShowMainWindow(){
    this->mainwindow->showMaximized();
}
