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

#ifndef STREAMTHREAD_H
#define STREAMTHREAD_H

#include "QThread"
#include "QString"
#include "streamtools.h"

class StreamTools;

class StreamThread : public QThread
{

public:
    StreamThread(StreamTools *stools,std::string rtmpUrl = "rtmp://live.twitch.tv/app/live_39774900_NpAMoM4dg3MTooePEZREpKUkynwivr", std::string size = "480x360", std::string videoBitrate = "300k", std::string audioBitrate = "64k");
    void setParameters(std::string rtmpUrl, std::string size, std::string videoBitrate, std::string audioBitrate);
    void run();
private:
    StreamTools *stools;
    std::string rtmpUrl;
    std::string size;
    std::string videoBitrate;
    std::string audioBitrate;
    QString qdata;
};

#endif // STREAMTHREAD_H
