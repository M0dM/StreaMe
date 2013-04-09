#ifndef STREAMTHREAD_H
#define STREAMTHREAD_H

#include "QThread"
#include "QString"
#include "streamtools.h"

class StreamTools;

class StreamThread : public QThread
{

public:
    StreamThread(StreamTools *stools,std::string rtmpUrl = "rtmp://live.twitch.tv/app/live_39774900_NpAMoM4dg3MTooePEZREpKUkynwivr", std::string size = "480x360", std::string videoBitrate = "300k", std::string audioBitrate = "64k");
    void setParameters(std::string rtmpUrl, std::string size, std::string videoBitrate, std::string audioBitrate);
    void run();
private:
    StreamTools *stools;
    std::string rtmpUrl;
    std::string size;
    std::string videoBitrate;
    std::string audioBitrate;
    QString qdata;
};

#endif // STREAMTHREAD_H
