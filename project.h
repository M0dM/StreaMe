#ifndef PROJECT_H
#define PROJECT_H

#include "source.h"
#include "live.h"
#include <vector>
#include <string>

class Controller;
class Source;
class Live;

class Project
{
public:
    Project(Controller* controller);
    bool save(string fileUrl); // return true if successfull
    bool load(string fileUrl); // return true if successfull
    vector<Source*> getUsedSources();
    void addUsedSource(Source* source);
    void removeUsedSource(std::string sourceName);
    void test_displayUsedSources();

    // Streaming platform attributes acessors and mutators
    int getPlatformIndex();
    void setPlatformIndex(int index);
    string getStreamingKey();
    void setStreamingKey(string key);

    // Streaming configuration attributes acessors and mutators
    int getVideoSizeIndex();
    void setVideoSizeIndex(int index);
    int getVideoFormatIndex();
    void setVideoFormatIndex(int index);
    bool getAutoConfiguration();
    void setAutoConfiguration(bool value);
    int getUploadSpeed();
    void setUploadSpeed(int uploadSpeed);
    int getVideoBitrate();
    void setVideoBitrate(int videoBitrate);
    int getAudioBitrateIndex();
    void setAudioBitrateIndex(int index);
    bool getStereoConfiguration();
    void setStereoConfiguration(bool value);

private:
    Controller* controller;
    vector<Source*> usedSources;
    Live* live;
    Controller* getController();
    void setLive(Live* live);
    void setUsedSources(vector<Source*> usedSources);

    // platform attributes
    int platformIndex;
    string streamingKey;

    // streaming configuration attributes
    int videoSizeIndex;
    int videoFormatIndex;
    bool autoConfiguration;
    int uploadSpeed;
    int videoBitrate;
    int audioBitrateIndex;
    bool stereoConfiguration;
};

#endif // PROJECT_H
