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

#include "newprojectassistant.h"
#include "ui_newprojectassistant.h"

NewProjectAssistant::NewProjectAssistant(Controller* controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewProjectAssistant)
{
    ui->setupUi(this);
    this->controller = controller;
    QObject::connect(ui->nextButton, SIGNAL(clicked()),this,SLOT(nextButtonClicked()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()),this,SLOT(close()));
}

NewProjectAssistant::~NewProjectAssistant()
{
    delete ui;
}

void NewProjectAssistant::setController(Controller* controller){
    this->controller = controller;
}

Controller* NewProjectAssistant::getController(){
    return this->controller;
}

void NewProjectAssistant::nextButtonClicked(){
    this->close();
    controller->displayPlatformsWindow();
    controller->setProjectName(ui->projectTitleLineEdit->text().toStdString());
    controller->setMainWindowTitle(ui->projectTitleLineEdit->text().toStdString(), true);
}
