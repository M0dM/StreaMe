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

void StreamTools::captureVideoFile(int time, string preset, string file){

    char q = 'q';
    char * qPoint = &q; // in ffmpeg, q = quit while capturing video-audio

    // build the device command by peeking the first item in each source vector -for testing...)
    this->setDevicesCommand(peekVideoSource().getName());
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

        captAvFile->write(qPoint); // needs a pointer of character (here the letter 'q')
        // Extremely important : without waiting for bytes written, the character written in not read
        captAvFile->waitForBytesWritten();
    }

}


void StreamTools::captureAudioVideoFile(int time, string preset, string file){

    char q = 'q';
    char * qPoint = &q; // in ffmpeg, q = quit while capturing video-audio

    // build the device command by peeking the first item in each source vector -for testing...)
    this->setDevicesCommand(peekVideoSource().getName(),peekAudioSource().getName());
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

        captAvFile->write(qPoint); // needs a pointer of character (here the letter 'q')
        // Extremely important : without waiting for bytes written, the character written in not read
        captAvFile->waitForBytesWritten();
    }

}
