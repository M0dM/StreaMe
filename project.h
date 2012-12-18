#ifndef PROJECT_H
#define PROJECT_H
#include "controller.h"
class Project
{
public:
    Project(Controller* controller);
private:
    Controller controller;
};

#endif // PROJECT_H
