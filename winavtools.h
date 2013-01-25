#ifndef WINAVTOOLS_H
#define WINAVTOOLS_H

#include <string>
#include <vector>
#include <iostream>
#include <direct.h>

#include <QProcess>
#include <QDebug>

#include <string>

#include "source.h"


class Source;
class Controller;

class WinAvTools
{
public:
    WinAvTools();
    std::vector<Source> getVideoSources();
    std::vector<Source> getAudioSources();

private:
    std::vector<Source> audioSources;
    std::vector<Source> videoSources;
    void detectSources(); //detect all sources and add them into the correspondant vector (audioSources or videoSources)
    void setVideoSources(std::vector<Source>);
    void setAudioSources(std::vector<Source>);
    void pushVideoSource(Source videoSource);
    void pushAudioSource(Source audioSource);

protected:
    std::string devicesCommand; // the attribute part of the ffmpeg command that is dependent of the OS
    std::string getDevicesCommand();
    void setDevicesCommand(std::string videoDevice);
    void setDevicesCommand(std::string videoDevice, std::string audioDevice);
};

#endif // WINAVTOOLS_H
