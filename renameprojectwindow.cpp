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
