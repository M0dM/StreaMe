#ifndef STREAMTOOLS_H
#define STREAMTOOLS_H

#include "windows.h"
#include <string>

#include "winavtools.h"


class StreamTools : public WinAvTools
{
public:
    StreamTools(Controller *controller);
    void captureVideoFile(int time = 10, std::string preset = "ultrafast", std::string file = "out.mp4");
    void captureAudioVideoFile(int time = 10, std::string preset = "ultrafast", std::string file = "out.mp4");
    std::vector<Source*> getVideoSources();
    std::vector<Source*> getAudioSources();

private:
    Controller *controller;
    std::string streamCommand;
    std::string getStreamCommand();
    void setStreamCommand(std::string streamCommand);

};

#endif // STREAMTOOLS_H
