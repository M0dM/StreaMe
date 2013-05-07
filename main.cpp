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

#include <QApplication>
#include "controller.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("StreaMe");

    Controller *controller = new Controller();

    //Project *newProject = new Project(controller);
    //newProject->addUsedSource(new Source("Microphone (Realtek High Definition Audio)","audio"));
    //controller->setProject(newProject);

    controller->showMainWindow();

    controller->displayFreeSources();
    controller->displayUsedSources();

    controller->blockInterface();
    controller->blockStreamingStop();
    return a.exec();

}
