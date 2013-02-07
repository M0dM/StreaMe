#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "project.h"
#include "streamtools.h"

#include "windows.h"

class MainWindow;
class Project;
class StreamTools;

class Controller
{
public:
    Controller();
    ~Controller();
    void ShowMainWindow();
    void displayVideoSources();
    void displayAudioSources();
    void useSource(string sourceName);
    void notUseSource(string sourceName);
    void twitchStream();
    void stopStream();
    void displayFreeSources(); //display the free sources in the interface => = (all sources) - (used sources)
    void displayUsedSources(); //display the used sources (given by the project class)
    Project* getProject();
    void setProject(Project*);
    vector<Source*> getProjectUsedSouces();
    void streamStarted();
private:
    MainWindow * mainwindow;
    Project *project;
    StreamTools *streamTools;
};

#endif // CONTROLLER_H
