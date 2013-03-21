#ifndef AVTOOLS_H
#define AVTOOLS_H

#include <string>
#include <vector>
#include <iostream>
//#include <direct.h>

#include <QProcess>
#include <QDebug>

#include <string>

#include "source.h"
#include "camera.h"
#include "microphone.h"

class Source;
class Camera;
class Microphone;

class AvTools
{
public:
    AvTools();
    ~AvTools();
    Source *peekVideoSource() const;
    Source *peekAudioSource() const;

private:
    std::vector<Source*> sources; //all sources available on the computer
    void detectSources(); //detect all sources and add them to the sources vector
    void setSources(std::vector<Source*>);
    void pushSource(Source *source);

protected:
    std::string devicesCommand; // the attribute part of the ffmpeg command that is dependent of the OS
    std::string getDevicesCommand() const;
    void setDevicesCommand(std::string videoDevice);
    void setDevicesCommand(std::string videoDevice, std::string audioDevice);
    std::vector<Source*> getSources() const;
};

#endif // WINAVTOOLS_H
