#include "platformselectionwindow.h"
#include "ui_platformselectionwindow.h"
#include <QString>


platformSelectionWindow::platformSelectionWindow(Controller* controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::platformSelectionWindow)
{
    platformSelectionWindow::setController(controller);
    ui->setupUi(this);

    // get project for set the project saved values
    Project* project = this->getController()->getProject();

    // set values
    ui->comboBox->setCurrentIndex(project->getPlatformIndex());
    ui->streamKeylineEdit->setText(project->getStreamingKeyQstring());

    // Connect signal buttons
    QObject::connect(ui->okPushButton, SIGNAL(clicked()),this,SLOT(okPushButtonClicked()));
    QObject::connect(ui->exitPushButton, SIGNAL(clicked()),this,SLOT(exitPushButtonClicked()));
}

Controller* platformSelectionWindow::getController(){
    return controller;
}

void platformSelectionWindow::setController(Controller* controller){
    this->controller = controller;
}

platformSelectionWindow::~platformSelectionWindow()
{
    delete ui;
}

void platformSelectionWindow::okPushButtonClicked(){
    Project* project = this->getController()->getProject();
    project->setPlatformIndex(ui->comboBox->currentIndex());
    project->setStreamingKey(ui->streamKeylineEdit->text());
    delete this;
}

void platformSelectionWindow::exitPushButtonClicked(){
    delete this;
}


