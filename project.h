#ifndef PROJECT_H
#define PROJECT_H

#include "source.h"
#include "live.h"
#include <vector>
#include <string.h>
#include <QString>
#include <controller.h>

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
    void setUsedSources(vector<Source*> usedSources);
    void addUsedSource(Source* source);
    void removeUsedSource(std::string sourceName);
    void test_displayUsedSources();

    // Streaming platform attributes acessors and mutators
    int getPlatformIndex();
    QString getPlatformIndexQstring();
    void setPlatformIndex(int index);
    void setPlatformIndex(QString index);

    QString getStreamingKeyQstring();
    void setStreamingKey(QString key);

    // Streaming configuration attributes acessors and mutators
    int getVideoSizeIndex();
    QString getVideoSizeIndexQstring();
    void setVideoSizeIndex(int index);
    void setVideoSizeIndex(QString index);

    int getVideoFormatIndex();
    QString getVideoFormatIndexQstring();
    void setVideoFormatIndex(int index);
    void setVideoFormatIndex(QString index);

    bool getAutoConfiguration();
    QString getAutoConfigurationQstring();
    void setAutoConfiguration(bool value);
    void setAutoConfiguration(QString value);

    int getUploadSpeed();
    QString getUploadSpeedQstring();
    void setUploadSpeed(int uploadSpeed);
    void setUploadSpeed(QString uploadSpeed);

    int getVideoBitrate();
    QString getVideoBitrateQstring();
    void setVideoBitrate(int videoBitrate);
    void setVideoBitrate(QString videoBitrate);

    int getAudioBitrateIndex();
    QString getAudioBitrateIndexQstring();
    void setAudioBitrateIndex(int index);
    void setAudioBitrateIndex(QString index);

    bool getStereoConfiguration();
    QString getStereoConfigurationQstring();
    void setStereoConfiguration(bool value);
    void setStereoConfiguration(QString value);

    bool isSource(string sourceName);

private:
    Controller* controller;
    vector<Source*> usedSources;
    Live* live;
    Controller* getController();
    void setLive(Live* live);

    // platform attributes
    int platformIndex;
    QString streamingKey;

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
