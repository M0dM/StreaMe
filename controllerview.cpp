#include "controllerview.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
using namespace std;

ControllerView::ControllerView()
{
}
void ControllerView::mainWindow(){
    MainWindow w;
    w.showMaximized();
    cout << "yoooo"<<endl;

}
