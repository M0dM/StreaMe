#include "controllerview.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
using namespace std;

ControllerView::ControllerView()
{
}
void ControllerView::mainWindow(){

    MainWindow * w = new MainWindow;
    w->showMaximized();
}
