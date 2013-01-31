#ifndef PROJECT_H
#define PROJECT_H

#include "source.h"
#include "live.h"
#include <vector>
#include <string>

class Controller;
class Source;
class Live;

class Project
{
public:
    Project(Controller* controller);
    bool save(string fileUrl); // return true if successfull
    bool load(string fileUrl); // return true if successfull
private:
    Controller* controller;
    vector<Source> sources;
    Live* live;
    Controller* getController();
    vector<Source> getSources();
    void setLive(Live* live);
    void setSources(vector<Source> sources);
};

#endif // PROJECT_H
