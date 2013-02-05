#include "streamtools.h"

using namespace std;


StreamTools::StreamTools(Controller *controller) : WinAvTools(){
    this->controller = controller;
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


void StreamTools::startStream(string rtmpUrl, string size, string videoBitrate , string audioBitrate){
    switch(this->controller->getProjectUsedSouces().size()){ //make decisions regarding on the size of the sources vector
    case 1:
        if(this->controller->getProjectUsedSouces()[0]->getType() == "video"){
            this->setDevicesCommand(this->controller->getProjectUsedSouces()[0]->getName());
            this->stream(rtmpUrl,size,videoBitrate,audioBitrate);
        }
        else
            cout << "Error : StreaMe can accept only one video input as single source" << endl; // REPLACE BY EXCEPTION
        break;
    case 2:
        if (this->controller->getProjectUsedSouces()[0]->getType() == "video"){
            if(this->controller->getProjectUsedSouces()[1]->getType() == "video")
                cout << "Error : StreaMe can accept only a single video input " << endl; // REPLACE BY EXCEPTION
            else if(this->controller->getProjectUsedSouces()[1]->getType() == "audio"){
                this->setDevicesCommand(this->controller->getProjectUsedSouces()[0]->getName(),this->controller->getProjectUsedSouces()[1]->getName());
                this->stream(rtmpUrl,size,videoBitrate,audioBitrate);
            }
            else
                cout << "Stream input list error" <<endl; // REPLACE BY EXCEPTION
        }
        else if (this->controller->getProjectUsedSouces()[0]->getType() == "audio"){
            if(this->controller->getProjectUsedSouces()[1]->getType() == "audio")
                cout << "Error : StreaMe can accept only a single audio intput source with a at least one video source " << endl; // REPLACE BY EXCEPTION
            else if(this->controller->getProjectUsedSouces()[1]->getType() == "video"){
                this->setDevicesCommand(this->controller->getProjectUsedSouces()[1]->getName(),this->controller->getProjectUsedSouces()[0]->getName());
                this->stream(rtmpUrl,size,videoBitrate,audioBitrate);
            }
            else
                cout << "Error : Stream input list error" <<endl; // REPLACE BY EXCEPTION
        }
        else
            cout << "Error : Unrecognized source type while trying to stream" <<endl; // REPLACE BY EXCEPTION
        break;
    default:
        cout << "Error : StreaMe can handle only one video source, or one video source and one audio source together" <<endl; // REPLACE BY EXCEPTION
    }
}

void StreamTools::stopStream(){
    if(ffmpegProcess->pid() > 0) //if the process is running, the pid is > 0
        ffmpegProcess->kill(); // we kill the running process
}

void StreamTools::stream(string rtmpUrl, string size, string videoBitrate, string audioBitrate){
    //cout << this->controller->getProjectUsedSouces().size() << endl;
    //string data;

    QString path("..\\StreaMe\\ffmpeg\\bin\\ffmpeg.exe");

    QStringList arguments;

    arguments << QString::fromStdString("-f") << QString::fromStdString("dshow") << QString::fromStdString("-i") << QString::fromStdString(getDevicesCommand());
    //        arguments << QString::fromStdString("-s") << QString::fromStdString(size) << QString::fromStdString("30");
    //        arguments << QString::fromStdString("-c:v") << QString::fromStdString("libx264");
    //        arguments << QString::fromStdString("-pix_fmt") << QString::fromStdString("yuv420p");
    //        arguments << QString::fromStdString("-c:a") << QString::fromStdString("libmp3lame");
    //        arguments << QString::fromStdString("-ab") << QString::fromStdString(audioBitrate);
    //        arguments << QString::fromStdString("-ar") << QString::fromStdString("22050");
    //        arguments << QString::fromStdString("-threads") << QString::fromStdString("2");
    //        arguments << QString::fromStdString("-f") << QString::fromStdString("flv");
    //        arguments << QString::fromStdString(rtmpUrl);
    arguments << QString::fromStdString("pourquoi.mpeg");

    cout << this->getDevicesCommand() << endl;
    this->setDevicesCommand("","");

    //            cout << endl << endl;
    //            for(int i(0); i < arguments.size(); i++)
    //                cout << arguments.value(i).toStdString() + " ";
    //            cout << endl << endl;
    //            ffmpegProcess->setProcessChannelMode(QProcess::MergedChannels); // get all channels for the output

    ffmpegProcess->start(path,arguments,QIODevice::ReadWrite); //Starting the process

    //        if(ffmpegProcess->waitForStarted()){
    //            while(ffmpegProcess->waitForReadyRead())
    //                data.append(ffmpegProcess->readAll());
    //        }
    //        cout << data << endl;
}
