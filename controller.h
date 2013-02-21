#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "newprojectassistant.h"
#include "streamingparametersconfigurationwindow.h"
#include "platformselectionwindow.h"
#include "project.h"
#include "streamtools.h"
#include <QTimer>
#include <QMutex>
#include <QWaitCondition>
#include <sstream>
#include <string.h>


#include "windows.h"

class MainWindow;
class Project;
class StreamTools;

class Controller
{
public:
    Controller();
    ~Controller();
    void showMainWindow();
    void displayVideoSources();
    void displayAudioSources();
    void useSource(string sourceName);
    void notUseSource(string sourceName);
    void stream();
    void stopStream();
    void displayFreeSources(); //display the free sources in the interface => = (all sources) - (used sources)
    void displayUsedSources(); //display the used sources (given by the project class)
    Project* getProject();
    void setProject(Project*);
    vector<Source*> getProjectUsedSouces();
    void streamStarted();
    string getProjectFileUrl();
    void setProjectFileUrl(string url = "");
    bool isProjectFile();
    void generateNewProject();
    void displayAssistantWindow();
    void displayParametersWindow();
    void displayPlatformsWindow();
    vector<Source*> getAllSources();
    void blockInterface();
    void deBlockInterface();

    void setMainWindowTitle(string projectName);
    void setProjectName(string projectName);
    void saveProject();
    void saveProjectAs();
    void setPlatformParameters(int platformIndex, string streamingKey);
    void setProjectAutoConfiguration(boolean value);
    void setStreamingParametersValue(int videoSizeIndex, int videoFormatIndex, int uploadSpeed, int videoBitrate, int audioBitrateIndex);
    void setProjectStereoConfiguration(boolean value);
    void mutSleep(int time);
private:
    MainWindow * mainwindow;
    QWidget *streamingParametersUi;
    QWidget *platformSelectionUi;
    QWidget *newProjectAssistantUi;
    Project *project;
    StreamTools *streamTools;
    string ProjectFileUrl;
};

#endif // CONTROLLER_H
