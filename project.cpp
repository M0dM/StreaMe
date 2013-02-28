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
    this->setName("");

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

void Project::setName(string name){
    this->name = name;
}

string Project::getName(){
    return this->name;
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
        writer.writeTextElement("name", QString::fromStdString(this->getName()));
            writer.writeStartElement("sources");
            for(unsigned int i=0; i < usedSources.size(); i++){
                writer.writeStartElement("source");
                    writer.writeTextElement("name", QString::fromStdString(usedSources[i]->getName()));
                    writer.writeTextElement("type", QString::fromStdString(usedSources[i]->getType()));
                writer.writeEndElement();
            }
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

bool Project::isSource(string sourceName){
    vector<Source*> sources = this->getController()->getAllSources();
    for(unsigned int i=0; i < sources.size(); i++){
        if (sources[i]->getName() == sourceName){
            return true;
        }
    }
    return false;
}

bool Project::load(string fileUrl){

    // empty usedSources
    usedSources.clear();

    QXmlStreamReader reader;
    QString fileName = fileUrl.c_str();
    QFile file(fileName);
    cout << fileName.toStdString() << endl;
    file.open(QFile::ReadOnly | QFile::Text); // Openning the XML file in text mode
    reader.setDevice(&file); // Initialising the reader object on the xml file
    cout << endl << "*  OPENNING PROJECT FILE:" << fileName.toStdString() << endl;
    cout << endl << ">> LOADING CONFIGURATION: " << endl << endl;
    cout << "Sources: " << endl;
    while (!reader.atEnd()){
        if(reader.readNextStartElement()){
            if(reader.name().toString().toStdString() == "name"){
                    this->setName(reader.readElementText().toStdString());
            }
            if(reader.name().toString().toStdString() == "source"){
                cout << "\tSource: " << endl;
                if(reader.readNextStartElement()){
                    if(reader.name().toString().toStdString() == "name"){
                        string sourceName = reader.readElementText().toStdString();
                        if(this->isSource(sourceName)){
                            this->getController()->useSource(sourceName);
                        }
                        cout << "\tname: " << sourceName << endl;
                        if(reader.readNextStartElement()){
                            string sourceType = reader.readElementText().toStdString();
                            if(reader.name().toString().toStdString() == "type"){
                                cout << "\ttype: " << sourceType << endl;

                            }
                        }
                    }
                }
            }
            if(reader.name().toString().toStdString() == "platform"){
                cout << "Platform: " << endl;
                if(reader.readNextStartElement()){
                    if(reader.name().toString().toStdString() == "index"){
                        this->setPlatformIndex(reader.readElementText());
                        cout << "\tindex: " << this->getPlatformIndex() << endl;
                        if(reader.readNextStartElement()){
                            if(reader.name().toString().toStdString() == "key"){
                                this->setStreamingKey(reader.readElementText());
                                cout << "\tkey: " << this->getStreamingKeyQstring().toStdString() << endl << endl;
                            }
                        }
                    }
                }

            }
            if(reader.name().toString().toStdString() == "streaming_quality"){
                cout << "Streaming Quality: " << endl;
                if(reader.readNextStartElement()){
                    if(reader.name().toString().toStdString() == "video_size"){
                        this->setVideoSizeIndex(reader.readElementText());
                        cout << "\tvideo size: " << this->getVideoSizeIndexQstring().toStdString() << endl;
                        if(reader.readNextStartElement()){
                            if(reader.name().toString().toStdString() == "video_format"){
                                this->setVideoFormatIndex(reader.readElementText());
                                cout << "\tvideo format: " << this->getVideoFormatIndexQstring().toStdString() << endl;
                                if(reader.readNextStartElement()){
                                    if(reader.name().toString().toStdString() == "auto_configuration"){
                                        this->setAutoConfiguration(reader.readElementText());
                                        cout << "\tauto configuration: " << this->getAutoConfigurationQstring().toStdString() << endl;
                                        if(reader.readNextStartElement()){
                                            if(reader.name().toString().toStdString() == "upload_speed"){
                                                this->setUploadSpeed(reader.readElementText());
                                                cout << "\tupload speed: " << this->getUploadSpeedQstring().toStdString() << endl;
                                                if(reader.readNextStartElement()){
                                                    if(reader.name().toString().toStdString() == "video_bitrate"){
                                                        this->setVideoBitrate(reader.readElementText());
                                                        cout << "\tvideo bitrate: " << this->getVideoBitrateQstring().toStdString() << endl;
                                                        if(reader.readNextStartElement()){
                                                            if(reader.name().toString().toStdString() == "audio_bitrate"){
                                                                this->setAudioBitrateIndex(reader.readElementText());
                                                                cout << "\taudio bitrate: " << this->getAudioBitrateIndexQstring().toStdString() << endl;
                                                                if(reader.readNextStartElement()){
                                                                    if(reader.name().toString().toStdString() == "stereo_configuration"){
                                                                        this->setStereoConfiguration(reader.readElementText());
                                                                        cout << "\tstereo configuration: " << this->getStereoConfigurationQstring().toStdString() << endl << endl;
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
    cout << ">> CONFIGURATION LOADED" << endl;
    this->getController()->setProjectFileUrl(fileName.toStdString());
    controller->setMainWindowTitle(this->getName(), false);
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

void Project::setPlatformIndex(QString index){
    this->platformIndex = index.toInt();
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

void Project::setVideoSizeIndex(QString index){
    this->videoSizeIndex = index.toInt();
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

void Project::setVideoFormatIndex(QString index){
    this->videoFormatIndex = index.toInt();
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

void Project::setAutoConfiguration(QString value){
    this->autoConfiguration = value.toInt();
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

void Project::setUploadSpeed(QString uploadSpeed){
    this->uploadSpeed = uploadSpeed.toInt();
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

void Project::setVideoBitrate(QString videoBitrate){
    this->videoBitrate = videoBitrate.toInt();
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

void Project::setAudioBitrateIndex(QString index){
    this->audioBitrateIndex = index.toInt();
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


void Project::setStereoConfiguration(QString value){
    this->stereoConfiguration = value.toInt();
}
