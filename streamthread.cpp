#include "streamthread.h"

using namespace std;

StreamThread::StreamThread(StreamTools *stools, string rtmpUrl, string size, string videoBitrate, string audioBitrate)
{
    this->stools = stools;
    setParameters(rtmpUrl,size,videoBitrate,audioBitrate);
}

void StreamThread::setParameters(string rtmpUrl, string size, string videoBitrate, string audioBitrate){
    this->rtmpUrl = rtmpUrl;
    this->size = size;
    this->videoBitrate = videoBitrate;
    this->audioBitrate = audioBitrate;
}

void StreamThread::run() //The function called for threading
{    

    QString path("..\\StreaMe\\ffmpeg\\bin\\ffmpeg.exe");

    QStringList arguments;

    arguments << QString::fromStdString("-f") << QString::fromStdString("dshow") << QString::fromStdString("-i") << QString::fromStdString(stools->getHardDevicesCommand());
        arguments << QString::fromStdString("-s") << QString::fromStdString(this->size);
        arguments << QString::fromStdString("-r") << QString::fromStdString("30");
        arguments << QString::fromStdString("-b:v") << QString::fromStdString(this->videoBitrate);
        arguments << QString::fromStdString("-c:v") << QString::fromStdString("libx264");
        arguments << QString::fromStdString("-pix_fmt") << QString::fromStdString("yuv420p");
        arguments << QString::fromStdString("-c:a") << QString::fromStdString("libmp3lame");
        arguments << QString::fromStdString("-b:a") << QString::fromStdString(this->audioBitrate);
        arguments << QString::fromStdString("-ar") << QString::fromStdString("22050");
        arguments << QString::fromStdString("-threads") << QString::fromStdString("2");
        arguments << QString::fromStdString("-f") << QString::fromStdString("flv");
        arguments << QString::fromStdString(this->rtmpUrl);
        arguments << QString::fromStdString("why.mpeg");

    stools->resetHardDevicesCommand();

    //    cout << stools->getHardDevicesCommand() << endl;
    //    cout << endl << endl;
    //    for(int i(0); i < arguments.size(); i++)
    //        cout << arguments.value(i).toStdString() + " ";
    //    cout << endl << endl;

    //stools->getFFmpegProcess()->setProcessChannelMode(QProcess::MergedChannels); // get all channels for the output

    stools->getFFmpegProcess()->start(path,arguments,QIODevice::ReadWrite); //Starting the process

    if(stools->getFFmpegProcess()->waitForStarted())
        stools->streamThreadStarted();

    //    string data;
    //    if(stools->getFFmpegProcess()->waitForStarted()){
    //        while(stools->getFFmpegProcess()->waitForReadyRead())
    //            data.append(stools->getFFmpegProcess()->readAll());
    //    }
    //    cout << data << endl;

    stools->getFFmpegProcess()->waitForFinished(); // wait the end of the FFmpeg process

    exit(); // stop the thread
}

