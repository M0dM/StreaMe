#ifndef PROJECT_H
#define PROJECT_H
#include "controller.h"
#include "source.h"
#include "live.h"
class Source;
class Live;
class Project
{
public:
    Project(Controller* controller);
private:
    Controller * controller;
    Source* sources[];
    Live* live;
};

#endif // PROJECT_H
