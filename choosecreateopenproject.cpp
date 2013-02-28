#include "choosecreateopenproject.h"
#include "ui_choosecreateopenproject.h"

ChooseCreateOpenProject::ChooseCreateOpenProject(Controller* controller,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseCreateOpenProject)
{
    ui->setupUi(this);
    this->controller=controller;
    QObject::connect(ui->nextButton, SIGNAL(clicked()),this,SLOT(nextClicked()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()),this,SLOT(close()));
}

ChooseCreateOpenProject::~ChooseCreateOpenProject()
{
    delete ui;
}

void ChooseCreateOpenProject::nextClicked(){
    if(ui->radioCreate->isChecked())
        this->controller->chooseProjectCreate(true);
    else if(ui->radioOpen->isChecked())
        this->controller->chooseProjectCreate(false);
}
