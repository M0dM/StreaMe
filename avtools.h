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
