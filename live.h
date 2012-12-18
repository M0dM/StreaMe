#ifndef LIVE_H
#define LIVE_H
#include "project.h"
class Project;
class Live
{
private:
    Project* project;
public:
    Live(Project* project);
};

#endif // LIVE_H
