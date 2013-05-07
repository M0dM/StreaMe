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

#ifndef PLATFORMSELECTIONWINDOW_H
#define PLATFORMSELECTIONWINDOW_H

#include <QWidget>
#include "controller.h"
#include <QMessageBox>
namespace Ui {
class platformSelectionWindow;
}

class PlatformSelectionWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlatformSelectionWindow(Controller* controller, QWidget *parent = 0);
    ~PlatformSelectionWindow();
    Controller* getController();
    void setController(Controller* controller);
    
private:
    Ui::platformSelectionWindow *ui;
    Controller* controller;

public slots:
    void okPushButtonClicked();
    void cancelPushButtonClicked();
    void advancedButtonClicked();
    void helpButtonClicked();
};

#endif // PLATFORMSELECTIONWINDOW_H
