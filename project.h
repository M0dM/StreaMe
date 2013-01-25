#ifndef PROJECT_H
#define PROJECT_H

#include "source.h"
#include "live.h"

class Controller;
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
