#include "controllerview.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
using namespace std;

ControllerView::ControllerView()
{
    //mainWindow();
}

void ControllerView::mainWindow(){

    MainWindow w;
    w.show();
    cout << "yoooo"<<endl;

}
