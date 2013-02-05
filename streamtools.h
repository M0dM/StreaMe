#ifndef STREAMTOOLS_H
#define STREAMTOOLS_H

#include "windows.h"
#include <string>
#include "QThread"

#include "winavtools.h"


class StreamTools : public WinAvTools, public QThread
{

public:
    StreamTools(Controller *controller, QObject* parent = 0);
    virtual ~StreamTools();
    void run();
    std::vector<Source*> getVideoSources();
    std::vector<Source*> getAudioSources();
    void captureAudioVideoFile(int time = 10, std::string preset = "ultrafast", std::string file = "out.mp4");
    void stream(std::string size = "640x360", std::string videoBitrate = "1000k", std::string audioBitrate = "22050", std::string rtmpUrl = "rtmp://live.twitch.tv/app/live_39774900_NpAMoM4dg3MTooePEZREpKUkynwivr");
    vector<Source*> getAllSources();

private:
    Controller *controller;
    QProcess *ffmpegProcess;
    std::string streamCommand;
    std::string getStreamCommand();
    void setStreamCommand(std::string streamCommand);


    // from Qthread :
signals:
    //void streamFinished();

public slots:
    //void setData(int someData);



};

#endif // STREAMTOOLS_H
