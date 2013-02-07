#include "platformselectionwindow.h"
#include "ui_platformselectionwindow.h"


platformSelectionWindow::platformSelectionWindow(Controller* controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::platformSelectionWindow)
{
    platformSelectionWindow::setController(controller);
    ui->setupUi(this);

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

}

void platformSelectionWindow::exitPushButtonClicked(){

}


