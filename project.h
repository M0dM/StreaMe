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
    vector<Source*> getUsedSources();
    void addUsedSource(Source* source);
    void removeUsedSource(std::string sourceName);
    void test_displayUsedSources();

private:
    Controller* controller;
    vector<Source*> usedSources;
    Live* live;
    Controller* getController();
    void setLive(Live* live);
    void setUsedSources(vector<Source*> usedSources);
};

#endif // PROJECT_H
