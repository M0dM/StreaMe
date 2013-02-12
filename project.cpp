#include "project.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QString>
#include <source.h>
#include <iostream>

using namespace std;

Project::Project(Controller* controller)
{
    this->controller=controller;

    // setting default values for the streaming platform
    this->setPlatformIndex(0);
    this->setStreamingKey(QString::fromStdString(""));

    // setting default values for streaming configuration
    this->setVideoSizeIndex(0);
    this->setVideoFormatIndex(0);
    this->setAutoConfiguration(true);
    this->setUploadSpeed(1000);
    this->setVideoBitrate(1000);
    this->setAudioBitrateIndex(0);
    this->setAudioBitrateIndex(0);
    this->setStereoConfiguration(true);
}

Controller* Project::getController(){
    return this->controller;
}

vector<Source*> Project::getUsedSources(){
    return this->usedSources;
}

void Project::setUsedSources(vector<Source*> sources){
    this->usedSources=sources;
}

void Project::addUsedSource(Source* source){
    this->usedSources.push_back(source);
}

void Project::removeUsedSource(string sourceName){
    //remove the item by finding his position in the usedSource vector, and remove the item on this position

    unsigned int i(0);
    bool found(false);
    while(i < usedSources.size() && !found){
        if(usedSources[i]->getName() == sourceName)
            found=true;
        i++;
    }
    usedSources.erase(usedSources.begin() + --i); // remove on the position 'i'
}

void Project::test_displayUsedSources(){
    for(unsigned int i(0); i<usedSources.size();i++)
        cout << usedSources[i]->getName() <<" (" << usedSources[i]->getType() << ")" << endl;
    cout << "---" <<endl;
}

void Project::setLive(Live* live){
    this->live=live;
}

bool Project::save(string fileUrl){

    QString fileName = fileUrl.c_str();
    QFile file(fileName);

    // Openning file in writting only mode
    file.open(QFile::WriteOnly | QFile::Text);
    QXmlStreamWriter writer(&file);

    // Allow Xml indentation
    writer.setAutoFormatting(true);

    // Writing XML Header : <?xml version="1.0" encoding="UTF-8" ?>
    writer.writeStartDocument();
        writer.writeStartElement("project");
            writer.writeStartElement("sources");
            //for (vector<Source>::iterator i = sources.begin(); i != sources.end(); ++i)
            //@todo : test avec boucle
            //{
                writer.writeStartElement("source");
                    writer.writeTextElement("name", "NAMETEST");
                    //writer.writeTextElement("type", (*i).getType().c_str());
                    writer.writeTextElement("type", "TYPETEST");
                    writer.writeTextElement("used", "used_bool_value");
                writer.writeEndElement();
            //i++;
            //}
            writer.writeEndElement();


            writer.writeStartElement("platform");
                writer.writeTextElement("index", this->getPlatformIndexQstring());
                writer.writeTextElement("key", this->getStreamingKeyQstring());
            writer.writeEndElement();

            writer.writeStartElement("streaming_quality");
                writer.writeTextElement("video_size", this->getVideoSizeIndexQstring());
                writer.writeTextElement("video_format", this->getVideoFormatIndexQstring());
                writer.writeTextElement("auto_configuration", this->getAutoConfigurationQstring());
                writer.writeTextElement("upload_speed", this->getUploadSpeedQstring());
                writer.writeTextElement("video_bitrate", this->getVideoBitrateQstring());
                writer.writeTextElement("audio_bitrate", this->getAudioBitrateIndexQstring());
                writer.writeTextElement("stereo_configuration", this->getStereoConfigurationQstring());
            writer.writeEndElement();
        writer.writeEndElement();
    writer.writeEndDocument();

    // Closing file
    file.close();
    return true;
}

bool Project::load(string fileUrl){

    QXmlStreamReader reader;
    QString fileName = fileUrl.c_str();
    QFile file(fileName);
    cout << fileName.toStdString() << endl;
    file.open(QFile::ReadOnly | QFile::Text); // Openning the XML file in text mode
    reader.setDevice(&file); // Initialising the reader object on the xml file
    while (!reader.atEnd()){
        if(reader.readNextStartElement()){
            if(reader.name().toString().toStdString() == "source"){
                cout << "SOURCE: " << endl;
                if(reader.readNextStartElement()){
                    if(reader.name().toString().toStdString() == "name"){
                        cout << "NAME: " << reader.readElementText().toStdString() << endl;
                        if(reader.readNextStartElement()){
                            if(reader.name().toString().toStdString() == "type")
                                cout << "TYPE: " << reader.readElementText().toStdString() << endl;
                                if(reader.readNextStartElement()){
                                    if(reader.name().toString().toStdString() == "used")
                                        cout << "USED: " << reader.readElementText().toStdString() << endl;
                                }
                        }
                    }
                }
            }
            if(reader.name().toString().toStdString() == "platform"){
                cout << "PLATFORM: " << endl;
                if(reader.readNextStartElement()){
                    if(reader.name().toString().toStdString() == "index"){
                        cout << "INDEX: " << reader.readElementText().toStdString() << endl;
                        if(reader.readNextStartElement()){
                            if(reader.name().toString().toStdString() == "key"){
                                cout << "KEY: " << reader.readElementText().toStdString() << endl;
                            }
                        }
                    }
                }

            }
            if(reader.name().toString().toStdString() == "streaming_quality"){
                cout << "STREAMING_QUALITY: " << endl;
                if(reader.readNextStartElement()){
                    if(reader.name().toString().toStdString() == "video_size"){
                        cout << "VIDEO_SIZE: " << reader.readElementText().toStdString() << endl;
                        if(reader.readNextStartElement()){
                            if(reader.name().toString().toStdString() == "video_format"){
                                cout << "VIDEO_FORMAT: " << reader.readElementText().toStdString() << endl;
                                if(reader.readNextStartElement()){
                                    if(reader.name().toString().toStdString() == "auto_configuration"){
                                        cout << "AUTO_CONFIGURATION: " << reader.readElementText().toStdString() << endl;
                                        if(reader.readNextStartElement()){
                                            if(reader.name().toString().toStdString() == "upload_speed"){
                                                cout << "UPLOAD_SPEED: " << reader.readElementText().toStdString() << endl;
                                                if(reader.readNextStartElement()){
                                                    if(reader.name().toString().toStdString() == "video_bitrate"){
                                                        cout << "VIDEO_BITRATE: " << reader.readElementText().toStdString() << endl;
                                                        if(reader.readNextStartElement()){
                                                            if(reader.name().toString().toStdString() == "audio_bitrate"){
                                                                cout << "AUDIO_BITRATE: " << reader.readElementText().toStdString() << endl;
                                                                if(reader.readNextStartElement()){
                                                                    if(reader.name().toString().toStdString() == "stereo_configuration"){
                                                                        cout << "STEREO_CONFIGURATION: " << reader.readElementText().toStdString() << endl;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }
    }
    file.close();
    return true;
}

// Streaming platform attributes acessors
int Project::getPlatformIndex(){
    return this->platformIndex;
}

QString Project::getPlatformIndexQstring(){
    QString qstringIndex = QString::number(this->platformIndex);
    return qstringIndex;
}

QString Project::getStreamingKeyQstring(){
    return this->streamingKey;
}

// Streaming platform attributes mutators
void Project::setPlatformIndex(int index){
    this->platformIndex = index;
}

void Project::setStreamingKey(QString key){
    this->streamingKey = key;
}

// Streaming configuration attributes acessors and mutators
int Project::getVideoSizeIndex(){
    return this->videoSizeIndex;
}

QString Project::getVideoSizeIndexQstring(){
    QString qstringIndex = QString::number(this->videoSizeIndex);
    return qstringIndex;
}

void Project::setVideoSizeIndex(int index){
    this->videoSizeIndex = index;
}

int Project::getVideoFormatIndex(){
    return this->videoFormatIndex;
}

QString Project::getVideoFormatIndexQstring(){
    QString qstringIndex = QString::number(this->videoFormatIndex);
    return qstringIndex;
}

void Project::setVideoFormatIndex(int index){
    this->videoFormatIndex = index;
}

bool Project::getAutoConfiguration(){
    return this->autoConfiguration;
}

QString Project::getAutoConfigurationQstring(){
    QString qstringBool = QString::number(this->autoConfiguration);
    return qstringBool;
}

void Project::setAutoConfiguration(bool value){
    this->autoConfiguration = value;
}

int Project::getUploadSpeed(){
    return this->uploadSpeed;
}

QString Project::getUploadSpeedQstring(){
    QString qstringInt = QString::number(this->uploadSpeed);
    return qstringInt;
}

void Project::setUploadSpeed(int uploadSpeed){
    this->uploadSpeed = uploadSpeed;
}

int Project::getVideoBitrate(){
    return this->videoBitrate;
}

QString Project::getVideoBitrateQstring(){
    QString qstringInt = QString::number(this->videoBitrate);
    return qstringInt;
}


void Project::setVideoBitrate(int videoBitrate){
    this->videoBitrate = videoBitrate;
}

int Project::getAudioBitrateIndex(){
    return this->audioBitrateIndex;
}

QString Project::getAudioBitrateIndexQstring(){
    QString qstringIndex = QString::number(this->audioBitrateIndex);
    return qstringIndex;
}

void Project::setAudioBitrateIndex(int index){
    this->audioBitrateIndex = index;
}

bool Project::getStereoConfiguration(){
    return this->stereoConfiguration;
}

QString Project::getStereoConfigurationQstring(){
    QString qstringBool = QString::number(this->stereoConfiguration);
    return qstringBool;
}

void Project::setStereoConfiguration(bool value){
    this->stereoConfiguration = value;
}


