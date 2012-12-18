#ifndef CONTROLLERVIEW_H
#define CONTROLLERVIEW_H
#include "controller.h"
#include "mainwindow.h"

//#include "project.h"

class ControllerView : public Controller
{
public:
    ControllerView();
    void ShowMainWindow();
private:
    MainWindow * mainwindow;
    //Project* project;
};

#endif // CONTROLLERVIEW_H
