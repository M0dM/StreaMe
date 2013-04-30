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
    int nextEndl(0), splitSize(100);
    QString path;
    QStringList arguments;


#ifdef _WIN32
    path = QString::fromStdString("ffmpeg\\bin\\ffmpeg.exe");
    arguments << QString::fromStdString("-f") << QString::fromStdString("dshow") << QString::fromStdString("-i") << QString::fromStdString(stools->getHardDevicesCommand());
#elif __linux__
    path = QString::fromStdString("/usr/local/bin/ffmpeg");
    arguments << QString::fromStdString("-f") << QString::fromStdString("video4linux2") << QString::fromStdString("-i") << QString::fromStdString(stools->getHardDevicesCommand());
#else
#error
#endif

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
            //arguments << QString::fromStdString(this->rtmpUrl);
            arguments << QString::fromStdString("why.mpeg");

    stools->resetHardDevicesCommand();

            cout << stools->getHardDevicesCommand() << endl;
            cout << endl << endl;
            for(int i(0); i < arguments.size(); i++)
                cout << arguments.value(i).toStdString() + " ";
            cout << endl << endl;

    stools->getFFmpegProcess()->setProcessChannelMode(QProcess::MergedChannels); // get all channels for the output

    stools->getFFmpegProcess()->start(path,arguments,QIODevice::ReadWrite); //Starting the process

    if(stools->getFFmpegProcess()->waitForStarted())
        stools->streamThreadStarted();

    if(stools->getFFmpegProcess()->waitForStarted()){
        while(stools->getFFmpegProcess()->waitForReadyRead()){
            qdata.clear();
            qdata.append(stools->getFFmpegProcess()->readAll());
            while(qdata.length()>0){
                nextEndl = qdata.indexOf("\n"); //we try the find the next \n
                if ((nextEndl < splitSize) && (nextEndl!=-1 && nextEndl !=0)){ //if the next \n is less far than 300 characters and non equal to zero
                    stools->transmitFFmpegFeedback(qdata.mid(0,nextEndl)); // we transmit this part
                    qdata=qdata.mid(nextEndl, qdata.length());
                }
                else{ // else... the \n is further, or there's no \n in the remaining string
                    if(nextEndl<=0){ // if there's no \n
                        nextEndl = qdata.length(); // we tell the programe that the next \n is the last character of the string...
                    }
                    while(qdata.mid(0,nextEndl).length() > splitSize){ // while the distance between the first element and the first \n is still > 300 characters
                        stools->transmitFFmpegFeedback(qdata.mid(0,splitSize)); // we transmit the 300 first characters
                        qdata = qdata.mid(splitSize,qdata.length()); // we remove these 300 characters from the string
                    }
                    if(qdata.mid(0,nextEndl).length() != 0){ // if there'are still few characters until the next \n...
                        stools->transmitFFmpegFeedback(qdata.mid(0,nextEndl)); // we transmit it
                        qdata = qdata.mid(nextEndl,qdata.length()); // and we remove it from the string
                    }
                }
            }
        }
        stools->getFFmpegProcess()->waitForFinished(); // wait the end of the FFmpeg process

        exit(); // stop the thread
    }
}
