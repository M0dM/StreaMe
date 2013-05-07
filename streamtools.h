/**
 *
 *  StreaMe is a cross-platform live streaming broadcasting client, written in C++, using QT and FFMPEG library.
 *  Copyright (C) 2013, Benoit Brayer, Nans Plancher, Romaric Delaunoy.
 *  This program is free software: you can redistribute it and/or modify it under the terms of
 *  the GNU General Public License as published by the Free Software Foundation,
 *  either version 3 of the License, or (at your option) any later version.
 *  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU General Public License for more details.
 *  You should have received a copy of the GNU General Public License along with this program.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#ifndef STREAMTOOLS_H
#define STREAMTOOLS_H


#include <string>

#include "avtools.h"
#include "controller.h"
#include "streamthread.h"

class StreamThread;

class StreamTools : public AvTools
{
public:
    StreamTools(Controller *controller);
    ~StreamTools();
    std::vector<Source*> getVideoSources();
    std::vector<Source*> getAudioSources();
    std::vector<Source*> getAllSources();
    QProcess *getFFmpegProcess();
    std::string getHardDevicesCommand() const;
    void startStream(std::string rtmpUrl = "rtmp://live.twitch.tv/app/live_39774900_NpAMoM4dg3MTooePEZREpKUkynwivr", std::string size = "480x360", std::string videoBitrate = "300k", std::string audioBitrate = "64k");
    void stopStream();
    void resetHardDevicesCommand();
    void streamThreadStarted();
    void transmitFFmpegFeedback(QString feedback);

private:
    Controller *controller;
    StreamThread *sThread;
    QProcess *ffmpegProcess;
    std::string streamCommand;
    std::string getStreamCommand();
    void setStreamCommand(std::string streamCommand);
};


#endif // STREAMTOOLS_H
