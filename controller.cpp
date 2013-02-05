#include "controller.h"
using namespace std;

Controller::Controller()
{
    this->mainwindow = new MainWindow(this);
    this->streamTools = new StreamTools(this);
}

Controller::~Controller(){
    delete this->mainwindow;  
    delete this->streamTools;
}

void Controller::ShowMainWindow(){
    this->mainwindow->show();
    //this->mainwindow->testFile();
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

void Controller::twitchStream(){
    streamTools->start();
}

void Controller::displayAllSources(){
    cout << streamTools->getAllSources().size() << endl;

    QStringList listFSources;
    for(unsigned int i(0); i < streamTools->getAllSources().size(); i++){
        listFSources.push_back(QString::fromStdString(streamTools->getAllSources()[i]->getName()));
        cout << streamTools->getAllSources()[i]->getName();

    }
    mainwindow->setFreeSources(listFSources);
}





