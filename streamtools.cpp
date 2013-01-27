#include "streamtools.h"

using namespace std;

StreamTools::StreamTools(Controller *controller) : WinAvTools(){
    this->controller = controller;
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


void StreamTools::captureVideoFile(int time, string preset, string file){

    // build the device command by peeking the first item in each source vector -for testing...)
    this->setDevicesCommand(peekVideoSource()->getName());
    // build the rest of the command (prest and file name) For testing also...
    this->setStreamCommand(" -preset  " + preset + " " + file);

    cout << getDevicesCommand() << getStreamCommand() << endl;
    QProcess *captAvFile = new QProcess();

    QString path("..\\StreaMe\\ffmpeg\\bin\\ffmpeg.exe");
    string pathVideoFiles("..\\StreaMe\\ffmpeg\\catchedFiles\\" + file);

    //The string containing arguments. /!\ Each part has to be delimited with the operator "<<"
    QStringList arguments;
    arguments << QString::fromStdString("-f") << QString::fromStdString("dshow") << QString::fromStdString("-i") << QString::fromStdString(getDevicesCommand()) << QString::fromStdString("-preset") << QString::fromStdString(preset) << QString::fromStdString(pathVideoFiles);

    //Starting the process
    captAvFile->start(path,arguments,QIODevice::ReadWrite);

    if (captAvFile->waitForStarted()){

        Sleep(time * 1000);

        captAvFile->write(new char('q')); // needs a pointer of character (here the letter 'q')
        // Extremely important : without waiting for bytes written, the character written in not read
        captAvFile->waitForBytesWritten();
    }
}

void StreamTools::captureAudioVideoFile(int time, string preset, string file){

    // build the device command by peeking the first item in each source vector -for testing...)
    this->setDevicesCommand(peekVideoSource()->getName(),peekAudioSource()->getName());
    // build the rest of the command (prest and file name) For testing also...
    this->setStreamCommand(" -preset  " + preset + " " + file);

    QProcess *captAvFile = new QProcess();

    QString path("..\\StreaMe\\ffmpeg\\bin\\ffmpeg.exe");
    string pathVideoFiles("..\\StreaMe\\ffmpeg\\catchedFiles\\" + file);

    //The string containing arguments. /!\ Each part has to be delimited with the operator "<<"
    QStringList arguments;
    arguments << QString::fromStdString("-f") << QString::fromStdString("dshow") << QString::fromStdString("-i") << QString::fromStdString(getDevicesCommand()) << QString::fromStdString("-preset") << QString::fromStdString(preset) << QString::fromStdString(pathVideoFiles);

    //Starting the process
    captAvFile->start(path,arguments,QIODevice::ReadWrite);

    if (captAvFile->waitForStarted()){

        Sleep(time * 1000);

        captAvFile->write(new char('q')); // needs a pointer of character (here the letter 'q')
        // Extremely important : without waiting for bytes written, the character written in not read
        captAvFile->waitForBytesWritten();
    }
}
