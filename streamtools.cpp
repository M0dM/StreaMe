#include "streamtools.h"

using namespace std;


StreamTools::StreamTools(Controller *controller, QObject *parent) : WinAvTools(), QThread(parent){
    this->controller = controller;
}

StreamTools::~StreamTools(){
    if(ffmpegProcess->pid() > 0){ //if the process is running, the pid is > 0
        ffmpegProcess->kill(); // we kill the running process
        cout << "I killed the process like a pig ! :)" << endl;
    }
    else
        cout << "I didn't kill the process like a pig ! :(" << endl;
}


void StreamTools::run() //The function called for threading
{
    this->stream();
    exec();
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

void StreamTools::captureAudioVideoFile(int time, string preset, string file){ //Depreciated

    // build the device command by peeking the first item in each source vector -for testing...)
    this->setDevicesCommand(peekVideoSource()->getName(),peekAudioSource()->getName());
    // build the rest of the command (prest and file name) For testing also...
    this->setStreamCommand(" -preset  " + preset + " " + file);

    ffmpegProcess = new QProcess();

    QString path("..\\StreaMe\\ffmpeg\\bin\\ffmpeg.exe");
    string pathVideoFiles("..\\StreaMe\\ffmpeg\\catchedFiles\\" + file);

    //The string containing arguments. /!\ Each part has to be delimited with the operator "<<"
    QStringList arguments;
    arguments << QString::fromStdString("-f") << QString::fromStdString("dshow") << QString::fromStdString("-i") << QString::fromStdString(getDevicesCommand()) << QString::fromStdString("-preset") << QString::fromStdString(preset) << QString::fromStdString(pathVideoFiles);

    //Starting the process
    ffmpegProcess->start(path,arguments,QIODevice::ReadWrite);

    if (ffmpegProcess->waitForStarted()){

        Sleep(time * 1000);

        ffmpegProcess->write(new char('q')); // needs a pointer of character (here the letter 'q')
        // Extremely important : without waiting for bytes written, the character written in not read
        ffmpegProcess->waitForBytesWritten();
    }

}
void StreamTools::stream(string size, string videoBitrate, string audioBitrate , string rtmpUrl)
{
    string data;
    // build the device command by peeking the first item in each source vector -for testing...)
    this->setDevicesCommand(peekVideoSource()->getName(),peekAudioSource()->getName());

    ffmpegProcess = new QProcess();

    QString path("..\\StreaMe\\ffmpeg\\bin\\ffmpeg.exe");

    QStringList arguments;
    arguments << QString::fromStdString("-f") << QString::fromStdString("dshow") << QString::fromStdString("-i") << QString::fromStdString(getDevicesCommand()) << QString::fromStdString("-s") << QString::fromStdString(size) << QString::fromStdString("-b") << QString::fromStdString(videoBitrate) << QString::fromStdString("-r") << QString::fromStdString("30") << QString::fromStdString("-c:v") << QString::fromStdString("libx264") << QString::fromStdString("-pix_fmt") << QString::fromStdString("yuv420p") << QString::fromStdString("-c:a") << QString::fromStdString("libmp3lame") << QString::fromStdString("-ab") << QString::fromStdString(audioBitrate) << QString::fromStdString("-ar") << QString::fromStdString("22050") << QString::fromStdString("-threads") << QString::fromStdString("2") << QString::fromStdString("-f") << QString::fromStdString("flv") << QString::fromStdString(rtmpUrl);

    ffmpegProcess->setProcessChannelMode(QProcess::MergedChannels); // get all channels for the output
    ffmpegProcess->start(path,arguments,QIODevice::ReadWrite); //Starting the process

    if(ffmpegProcess->waitForStarted()){
        while(ffmpegProcess->waitForReadyRead())
            data.append(ffmpegProcess->readAll());
    }

    //cout << data << endl;
}

