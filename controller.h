#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "mainwindow.h"
#include "project.h"
class MainWindow;
class Project;
class Controller
{
public:
    Controller();
    void ShowMainWindow();
private:
    MainWindow * mainwindow;
    Project* project;
};

#endif // CONTROLLER_H
