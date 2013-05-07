/**
 *
 *  StreaMe is a cross-platform live streaming broadcasting client, written in C++, using QT and FFMPEG library.
 *  Copyright (C) 2013, Benoit Brayer, Nans Plancher, Romaric Delaunoy.
 *  This program is free software: you can redistribute it and/or modify it under the terms of
 *  the GNU General Public License as published by the Free Software Foundation,
 *  either version 3 of the License, or (at your option) any later version.
 *  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU General Public License for more details.
 *  You should have received a copy of the GNU General Public License along with this program.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#include "controller.h"
#include <QFileDialog>
#include <QMessageBox>
using namespace std;


Controller::Controller()
{
    this->mainwindow = new MainWindow(this);
    this->streamTools = new StreamTools(this);

    this->project = new Project(this);
    this->ProjectFileUrl = "";

    this->newProjectAssistantUi = new NewProjectAssistant(this);
    this->streamingParametersUi = new StreamingParametersConfigurationWindow(this);
    this->platformSelectionUi = new PlatformSelectionWindow(this);
    this->renameProjectUi = new RenameProjectWindow(this);
    this->chooseCreateOpenProject = new  ChooseCreateOpenProject(this);

}

Controller::~Controller(){
    delete this->newProjectAssistantUi;
    delete this->streamingParametersUi;
    delete this->platformSelectionUi;
    delete this->renameProjectUi;
    delete this->streamTools;
    delete this->chooseCreateOpenProject;
}

MainWindow* Controller::getMainwindow(){
    return this->mainwindow;
}

QWidget* Controller::getStreamingParametersUi(){
    return this->streamingParametersUi;
}

QWidget* Controller::getPlatformSelectionUi(){
    return this->platformSelectionUi;
}

QWidget* Controller::getNewProjectAssistantUi(){
    return this->newProjectAssistantUi;
}

QWidget* Controller::getRenameProjectUi(){
    return this->renameProjectUi;
}

void Controller::showMainWindow(){
    this->mainwindow->show();
    this->chooseCreateOpenProject->show();
}

void Controller::displayVideoSources(){

    vector<Source*> videoDevices = streamTools->getVideoSources();

    for(unsigned int i(0); i < videoDevices.size(); i++){
        cout << videoDevices[i]->getName() << endl;
    }
}

void Controller::displayAudioSources(){

    vector<Source*> audioDevices = streamTools->getAudioSources();

    for(unsigned int i(0); i < audioDevices.size(); i++){
        cout << audioDevices[i]->getName() << endl;
    }
}

void Controller::stream(){

    string url, size, videoBitrate, audioBitrate;

    //Switching to define the streaming platform
    switch(project->getPlatformIndex())
    {
    case 0: //Platform == Justin.tv
        url = "rtmp://live.twitch.tv/app/";
        url += project->getStreamingKeyQstring().toStdString();
        break;
    case 1: // Platform == Ustream
        url = "rtmp://1.13181675.fme.ustream.tv/ustreamVideo/13181675/";
        url += project->getStreamingKeyQstring().toStdString();
        url += " flashver=FMLE/3.0\20(compatible;\20FMSc/1.0)";
        break;
    default:
        break;
    }

    //Switching to define the streaming video size ("480x360" for example)
    switch(project->getVideoSizeIndex())
    {
    case 0: // size = 360p
        if(project->getVideoFormatIndex() == 0)// if format == 16/9
            size = "640x360";
        else // else if format == 4/3
            size = "480x360";
        break;
    case 1: // size = 480p
        if(project->getVideoFormatIndex() == 0)// if format == 16/9
            size = "720x480";
        else // else if format == 4/3
            size = "640x480";
        break;
    case 2: // size = 720p
        size = "1280x720";
        break;
    default:
        break;
    }

    //Construct the video bitrate string
    stringstream stringVBitrate(videoBitrate);
    stringVBitrate << project->getVideoBitrate();
    videoBitrate = stringVBitrate.str() + "k";

    switch(project->getAudioBitrateIndex())
    {
    case 0:
        audioBitrate = "56k";
        break;
    case 1:
        audioBitrate = "128k";
        break;
    case 2:
        audioBitrate = "256k";
        break;
    case 3:
        audioBitrate = "320k";
        break;
    default:
        break;
    }

    this->addFeedback("Streaming to : " + url);
    this->addFeedback("Video size : " + size);
    this->addFeedback("Video bitrate : " + videoBitrate);
    this->addFeedback("Audio bitrate : " + audioBitrate);
    streamTools->startStream(url,size,videoBitrate,audioBitrate);

}

void Controller::stopStream(){
    streamTools->stopStream();
}

void Controller::displayFreeSources(){
    vector<Source*> allSources(streamTools->getAllSources()), usedSources(project->getUsedSources());
    //usedSources.push_back(new Source("Microphone (Realtek High Definition Audio)","audio"));
    bool used(false);
    unsigned int j(0);
    QStringList listFSources;

    for(unsigned int i(0); i < allSources.size(); i++){

        while( (j < usedSources.size()) && !used){ // browse the used vector to check if the source is used
            if(allSources[i]->getName() == usedSources[j]->getName())
                used = true;
            else
                j++;
        }

        if(!used) //if not used, the source is free, so we add it on the list
            listFSources.push_back(QString::fromStdString((allSources[i]->getName())));

        used = false; // used = false to enter in the next iteration
        j = 0; // same thing
    }
    mainwindow->setFreeSources(listFSources);
}

void Controller::displayUsedSources(){
    QStringList listUSources;
    for(unsigned int i(0); i < project->getUsedSources().size(); i++){
        listUSources.push_back(QString::fromStdString((project->getUsedSources()[i]->getName())));
    }
    mainwindow->setUsedSources(listUSources);
}

Project* Controller::getProject(){
    return this->project;
}

void Controller::setProject(Project* newProject){
    this->project = newProject;
}

void Controller::useSource(string sourceName){

    Source *selectedSource(0);

    for(unsigned int i(0); i < streamTools->getAllSources().size(); i++){
        if(streamTools->getAllSources()[i]->getName() == sourceName)
            selectedSource = streamTools->getAllSources()[i];
    }

    if(selectedSource != 0){
        project->addUsedSource(selectedSource);
        this->addFeedback("Source \"" + sourceName + "\" used");
        displayFreeSources();
        displayUsedSources();
    }
}

void Controller::notUseSource(string sourceName){

    project->removeUsedSource(sourceName);
    this->addFeedback("Source \"" + sourceName + "\" not used anymore" ) ;
    displayFreeSources();
    displayUsedSources();
}

vector<Source*> Controller::getProjectUsedSouces(){
    return project->getUsedSources();
}

void Controller::streamStarted(){
    this->addFeedback("Streaming started");
    mutSleep(5000);
    mainwindow->startVideo();

}

void Controller::mutSleep(int time){
    QMutex mutexSleep;
    mutexSleep.lock();
    QWaitCondition waitCondition;
    waitCondition.wait(&mutexSleep, time);
    mutexSleep.unlock();
}


string Controller::getProjectFileUrl(){
    return this->ProjectFileUrl;
}

void Controller::setProjectFileUrl(string url){
    this->ProjectFileUrl = url;
}

bool Controller::isProjectFile(){
    if(this->ProjectFileUrl != ""){
        return true;
    }
    return false;
}

void Controller::generateNewProject(){
    delete(this->getProject());
    delete(this->getNewProjectAssistantUi());
    delete(this->getRenameProjectUi());
    delete(this->getStreamingParametersUi());
    delete(this->getPlatformSelectionUi());
    this->project = new Project(this);
    this->renameProjectUi = new RenameProjectWindow(this);
    this->streamingParametersUi = new StreamingParametersConfigurationWindow(this);
    this->platformSelectionUi = new PlatformSelectionWindow(this);
    this->newProjectAssistantUi = new NewProjectAssistant(this);
    this->getMainwindow()->emptySourcesLists();
    this->displayFreeSources();
}

void Controller::displayAssistantWindow(){;
    newProjectAssistantUi->show();
}

void Controller::displayParametersWindow(){;
    streamingParametersUi->show();
}

void Controller::displayPlatformsWindow(){;
    platformSelectionUi->show();
}

void Controller::displayRenameProjectWindow(){
    renameProjectUi->show();
}

vector<Source*> Controller::getAllSources(){
    return this->streamTools->getAllSources();
}

void Controller::setProjectName(string projectName){
    this->getProject()->setName(projectName);
}

void Controller::setMainWindowTitle(string projectName, bool newProject){
    if(this->getProjectFileUrl() == "" || newProject){
        mainwindow->setWindowTitle(QString::fromStdString(projectName) + QString::fromStdString(" - ") + QString::fromStdString("Unsaved project") + QString::fromStdString(" - StreaMe"));
    }
    else{
        mainwindow->setWindowTitle(QString::fromStdString(projectName) + QString::fromStdString(" - ") + QString::fromStdString(this->getProjectFileUrl()) + QString::fromStdString(" - StreaMe"));
    }

}

void Controller::blockInterface(){
    mainwindow->disableInterfaceForNewProject();
}

void Controller::deBlockInterface(){
    mainwindow->enableInterfaceForNewProject();
}

void Controller::blockStreamingPlay(){
    mainwindow->blockPlay();
}
void Controller::blockStreamingStop(){
    mainwindow->blockStop();
}
void Controller::unblockStreamingPlay(){
    mainwindow->unblockPlay();
}

void Controller::unblockStreamingStop(){
    mainwindow->unblockStop();
}

void Controller::saveProject(){
    if(this->getProjectFileUrl() == ""){
        QString fileName = QFileDialog::getSaveFileName(this->mainwindow, "Save File", "/", "StreaMe File (*.sm)");
        if(fileName.toStdString() != ""){
            if(this->getProject()->save(fileName.toStdString()) == true){
                this->addFeedback("StreaMe project saved successfully");
                this->setProjectFileUrl(fileName.toStdString());
                this->setMainWindowTitle(this->getProject()->getName(), false);
            }
            else
                this->addFeedback("Problem when saving the new StreaMe project",true);
        }
    }
    else{
        this->getProject()->save(this->getProjectFileUrl());
        this->addFeedback("StreaMe project saved successfully");
     }
}

void Controller::saveProjectAs(){
    QString fileName = QFileDialog::getSaveFileName(this->mainwindow, "Save File","/","StreaMe File (*.sm)");
    if(fileName.toStdString() != ""){
        if(this->getProject()->save(fileName.toStdString()) == true){
            this->addFeedback("StreaMe project saved successfully in \"" + fileName.toStdString() + "\"" );
            this->setProjectFileUrl(fileName.toStdString());
        }
        else
            this->addFeedback("Problem when saving the new StreaMe project.",true);
    }
    this->setMainWindowTitle(this->getProject()->getName(), false);
}

void Controller::renameProject(string projectName){
    this->setProjectName(projectName);
    this->setMainWindowTitle(projectName, false);
    this->addFeedback("StreaMe project now known as \"" + projectName + "\"");
}

void Controller::setPlatformParameters(int platformIndex, string streamingKey){
    this->getProject()->setPlatformIndex(platformIndex);
    this->getProject()->setStreamingKey(QString::fromStdString(streamingKey));
}

void Controller::setProjectAutoConfiguration(bool value){
    this->getProject()->setAutoConfiguration(value);
}

void Controller::setStreamingParametersValue(int videoSizeIndex, int videoFormatIndex, int uploadSpeed, int videoBitrate, int audioBitrateIndex){
    this->getProject()->setVideoSizeIndex(videoSizeIndex);
    this->getProject()->setVideoFormatIndex(videoFormatIndex);
    this->getProject()->setUploadSpeed(uploadSpeed);
    this->getProject()->setVideoBitrate(videoBitrate);
    this->getProject()->setAudioBitrateIndex(audioBitrateIndex);
}

void Controller::setProjectStereoConfiguration(bool value){
    this->getProject()->setStereoConfiguration(value);
}

void Controller::openProjectFile(){
    QString fileName = QFileDialog::getOpenFileName(this->mainwindow, QString::fromStdString("Open file"),QString::fromStdString("/"),QString::fromStdString("StreaMe File (*.sm)"));
    if(fileName.toStdString() != ""){
        if(this->getProject()->load(fileName.toStdString())==true){
            this->deBlockInterface();
            this->addFeedback("Project successfully opened");
        }
        else{
            this->addFeedback("Problem when loading the StreaMe project.", true);
        }
    }
}

void Controller::chooseProjectCreate(bool choice){
    this->chooseCreateOpenProject->close();
    if(choice){
        displayAssistantWindow();
    }
    else{
        this->openProjectFile();
    }
}

void Controller::addFeedback(string feedback, bool error){
    if(error){
        mainwindow->addLineFeedback(QTime::currentTime().toString() + QString::fromStdString(" => Error : ") + QString::fromStdString(feedback));
        QMessageBox::critical(this->mainwindow,QString::fromStdString("Error"),QString::fromStdString(feedback));
    }
    else
        mainwindow->addLineFeedback(QTime::currentTime().toString() + QString::fromStdString(" => ") + QString::fromStdString(feedback));
}

void Controller::addFFmpegFeedback(QString feedback){
        mainwindow->addFFmpegLineFeedback(feedback);
}
