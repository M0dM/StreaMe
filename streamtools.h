#ifndef STREAMTOOLS_H
#define STREAMTOOLS_H


#include <string>

#include "winavtools.h"
#include "controller.h"
#include "streamthread.h"

class StreamThread;

class StreamTools : public WinAvTools
{

public:
    StreamTools(Controller *controller);
    ~StreamTools();
    std::vector<Source*> getVideoSources();
    std::vector<Source*> getAudioSources();
    vector<Source*> getAllSources();
    QProcess *getFFmpegProcess();
    std::string getHardDevicesCommand() const;
    void startStream(std::string rtmpUrl = "rtmp://live.twitch.tv/app/live_39774900_NpAMoM4dg3MTooePEZREpKUkynwivr", std::string size = "480x360", std::string videoBitrate = "300k", std::string audioBitrate = "64k");
    void stopStream();
    void resetHardDevicesCommand();
    void streamThreadStarted();

private:
    Controller *controller;
    StreamThread *sThread;
    QProcess *ffmpegProcess;
    std::string streamCommand;
    std::string getStreamCommand();
    void setStreamCommand(std::string streamCommand);
};


#endif // STREAMTOOLS_H
