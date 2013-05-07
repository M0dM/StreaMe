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

#include "renameprojectwindow.h"
#include "ui_renameprojectwindow.h"

RenameProjectWindow::RenameProjectWindow(Controller* controller,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenameProjectWindow)
{
    RenameProjectWindow::setController(controller);
    ui->setupUi(this);

    // Connect signal buttons
    QObject::connect(ui->okButton, SIGNAL(clicked()),this,SLOT(okPushButtonClicked()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()),this,SLOT(cancelPushButtonClicked()));
}

RenameProjectWindow::~RenameProjectWindow()
{
    delete ui;
}

void RenameProjectWindow::setController(Controller* controller){
    this->controller = controller;
}

Controller* RenameProjectWindow::getController(){
    return controller;
}

void RenameProjectWindow::okPushButtonClicked(){
    this->getController()->renameProject(ui->newNameLineEdit->text().toStdString());
    this->close();
}

void RenameProjectWindow::cancelPushButtonClicked(){
    this->close();
}
