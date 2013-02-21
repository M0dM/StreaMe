#include "newprojectassistant.h"
#include "ui_newprojectassistant.h"

NewProjectAssistant::NewProjectAssistant(Controller* controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewProjectAssistant)
{
    ui->setupUi(this);
    this->controller = controller;
    QObject::connect(ui->nextButton, SIGNAL(clicked()),this,SLOT(nextButtonClicked()));
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
    controller->setMainWindowTitle(ui->projectTitleLineEdit->text().toStdString());
}
