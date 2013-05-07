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

#include "streamtools.h"

using namespace std;

StreamTools::StreamTools(Controller *controller) : AvTools(){
    this->controller = controller;
    this->sThread = new StreamThread(this);
    this->ffmpegProcess = new QProcess();
}

StreamTools::~StreamTools(){
    this->stopStream();
}

string StreamTools::getStreamCommand(){
    return this->streamCommand;
}

void StreamTools::setStreamCommand(string streamCommand){
    this->streamCommand = streamCommand;
}

vector<Source*> StreamTools::getVideoSources(){
    vector<Source*> videoSources;

    for(unsigned int i(0); i <getSources().size(); i++){
        if(getSources()[i]->getType() == "video")
            videoSources.push_back(getSources()[i]);
    }

    return videoSources;
}

vector<Source*> StreamTools::getAudioSources(){
    vector<Source*> audioSources;

    for(unsigned int i(0); i <getSources().size(); i++){
        if(getSources()[i]->getType() == "audio")
            audioSources.push_back(getSources()[i]);
    }

    return audioSources;
}

vector<Source*> StreamTools::getAllSources(){
    return getSources();
}

QProcess *StreamTools::getFFmpegProcess(){
    return this->ffmpegProcess;
}

string StreamTools::getHardDevicesCommand() const{
    return getDevicesCommand();
}

void StreamTools::startStream(string rtmpUrl, string size, string videoBitrate , string audioBitrate){
    //cout << rtmpUrl << " - " << size << " - " << videoBitrate << " - " << audioBitrate << endl;
    switch(this->controller->getProjectUsedSouces().size()){ //make decisions regarding on the size of the sources vector
    case 1:
        if(this->controller->getProjectUsedSouces()[0]->getType() == "video"){
            this->setDevicesCommand(this->controller->getProjectUsedSouces()[0]->getSystemName());
            ffmpegProcess->moveToThread(sThread);
            sThread->setParameters(rtmpUrl,size,videoBitrate,audioBitrate);
            controller->blockStreamingPlay();
            controller->unblockStreamingStop();
            sThread->start();
        }
        else
            controller->addFeedback("StreaMe can accept only one video input as single source",true); //ADD EXCEPTION
        break;
    case 2:
        if (this->controller->getProjectUsedSouces()[0]->getType() == "video"){
            if(this->controller->getProjectUsedSouces()[1]->getType() == "video")
                controller->addFeedback("StreaMe can accept only a single video input", true); // ADD EXCEPTION
            else if(this->controller->getProjectUsedSouces()[1]->getType() == "audio"){
                this->setDevicesCommand(this->controller->getProjectUsedSouces()[0]->getSystemName(),this->controller->getProjectUsedSouces()[1]->getSystemName());
                ffmpegProcess->moveToThread(sThread);
                sThread->setParameters(rtmpUrl,size,videoBitrate,audioBitrate);
                controller->blockStreamingPlay();
                controller->unblockStreamingStop();
                sThread->start();
            }
            else
                controller->addFeedback("Anormal stream input list", true); // ADD EXCEPTION
        }
        else if (this->controller->getProjectUsedSouces()[0]->getType() == "audio"){
            if(this->controller->getProjectUsedSouces()[1]->getType() == "audio")
                controller->addFeedback("StreaMe can accept only a single audio intput source with a at least one video source", true); // REPLACE BY EXCEPTION
            else if(this->controller->getProjectUsedSouces()[1]->getType() == "video"){
                this->setDevicesCommand(this->controller->getProjectUsedSouces()[1]->getSystemName(),this->controller->getProjectUsedSouces()[0]->getSystemName());
                ffmpegProcess->moveToThread(sThread);
                sThread->setParameters(rtmpUrl,size,videoBitrate,audioBitrate);
                controller->blockStreamingPlay();
                controller->unblockStreamingStop();
                sThread->start();
            }
            else
                controller->addFeedback("Stream input list error", true); // ADD EXCEPTION
        }
        else
            controller->addFeedback("Unrecognized source type while trying to stream", true); // ADD EXCEPTION
        break;
    default:
        controller->addFeedback("StreaMe can handle only one video source, or one video source and one audio source together", true); // ADD EXCEPTION
    }
}
void StreamTools::stopStream(){
    if(ffmpegProcess->pid() > 0) //if the process is running, the pid is > 0
        ffmpegProcess->kill(); // we kill the running process
    sThread->wait(); // we wait the thread to terminate
    controller->addFeedback("Streaming stoped");
}

void StreamTools::resetHardDevicesCommand(){
    this->setDevicesCommand("","");
}

void StreamTools::streamThreadStarted(){
    controller->streamStarted();
}

void StreamTools::transmitFFmpegFeedback(QString feedback){
    controller->addFFmpegFeedback(feedback);
}
