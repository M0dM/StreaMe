#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "newprojectassistant.h"
#include "streamingparametersconfigurationwindow.h"
#include "platformselectionwindow.h"
#include "renameprojectwindow.h"
#include "choosecreateopenproject.h"
#include "project.h"
#include "streamtools.h"
#include <QTimer>
#include <QMutex>
#include <QWaitCondition>
#include <sstream>
#include <string.h>
#include <QDateTime>

//#include "windows.h"

class MainWindow;
class Project;
class StreamTools;

class Controller
{
public:
    Controller();
    ~Controller();
    void showMainWindow();
    MainWindow* getMainwindow();
    QWidget* getStreamingParametersUi();
    QWidget* getPlatformSelectionUi();
    QWidget* getNewProjectAssistantUi();
    QWidget* getRenameProjectUi();
    void displayVideoSources();
    void displayAudioSources();
    void useSource(std::string sourceName);
    void notUseSource(std::string sourceName);
    void stream();
    void stopStream();
    void displayFreeSources(); //display the free sources in the interface => = (all sources) - (used sources)
    void displayUsedSources(); //display the used sources (given by the project class)
    Project* getProject();
    void setProject(Project*);
    std::vector<Source*> getProjectUsedSouces();
    void streamStarted();
    std::string getProjectFileUrl();
    void setProjectFileUrl(std::string url = "");
    bool isProjectFile();
    void generateNewProject();
    void displayAssistantWindow();
    void displayParametersWindow();
    void displayPlatformsWindow();
    void displayRenameProjectWindow();
    std::vector<Source*> getAllSources();
    void blockInterface();
    void deBlockInterface();
    void blockStreamingPlay();
    void blockStreamingStop();
    void unblockStreamingPlay();
    void unblockStreamingStop();

    void openProjectFile();
    void setMainWindowTitle(std::string projectName, bool newProject);
    void setProjectName(std::string projectName);
    void saveProject();
    void saveProjectAs();
    void renameProject(std::string projectName);
    void setPlatformParameters(int platformIndex, std::string streamingKey);
    void setProjectAutoConfiguration(bool value);
    void setStreamingParametersValue(int videoSizeIndex, int videoFormatIndex, int uploadSpeed, int videoBitrate, int audioBitrateIndex);
    void setProjectStereoConfiguration(bool value);
    void mutSleep(int time);
    void chooseProjectCreate(bool choice);

    void addFeedback(std::string feedback, bool error = false);
    void addFFmpegFeedback(QString feedback);

private:
    MainWindow * mainwindow;
    QWidget *streamingParametersUi;
    QWidget *platformSelectionUi;
    QWidget *newProjectAssistantUi;
    QWidget *renameProjectUi;
    QWidget *chooseCreateOpenProject;
    Project *project;
    StreamTools *streamTools;
    std::string ProjectFileUrl;
};

#endif // CONTROLLER_H
