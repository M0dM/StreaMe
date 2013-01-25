#include "controller.h"
using namespace std;

Controller::Controller()
{
    this->mainwindow = new MainWindow(this);
    this->streamTools = new StreamTools(this);

}

void Controller::ShowMainWindow(){
    this->mainwindow->showMaximized();
}

void Controller::displayVideoSources(){

    vector<Source> videoDevices = streamTools->getVideoSources();

    for(int i(0); i < videoDevices.size(); i++){
        cout << videoDevices[i].getName() << endl;
    }
}

void Controller::displayAudioSources(){

    vector<Source> audioDevices = streamTools->getAudioSources();

    for(int i(0); i < audioDevices.size(); i++){
        cout << audioDevices[i].getName() << endl;
    }
}
