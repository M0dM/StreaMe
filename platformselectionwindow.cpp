#include "platformselectionwindow.h"
#include "ui_platformselectionwindow.h"
#include <QString>
#include <QMessageBox>

PlatformSelectionWindow::PlatformSelectionWindow(Controller* controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::platformSelectionWindow)
{
    PlatformSelectionWindow::setController(controller);
    ui->setupUi(this);

    // set window values
    ui->comboBox->setCurrentIndex(this->getController()->getProject()->getPlatformIndex());
    ui->streamKeylineEdit->setText(this->getController()->getProject()->getStreamingKeyQstring());

    // Connect signal buttons
    QObject::connect(ui->okButton, SIGNAL(clicked()),this,SLOT(okPushButtonClicked()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()),this,SLOT(cancelPushButtonClicked()));
    QObject::connect(ui->advancedButton, SIGNAL(clicked()),this,SLOT(advancedButtonClicked()));
}

Controller* PlatformSelectionWindow::getController(){
    return controller;
}

void PlatformSelectionWindow::setController(Controller* controller){
    this->controller = controller;
}

PlatformSelectionWindow::~PlatformSelectionWindow()
{
    delete ui;
}

void PlatformSelectionWindow::okPushButtonClicked(){


    if(!ui->streamKeylineEdit->text().isEmpty()){
        this->getController()->setPlatformParameters(ui->comboBox->currentIndex(), ui->streamKeylineEdit->text().toStdString());
        controller->deBlockInterface();
        this->close();
    }
    else{
         QMessageBox::critical(this,QString::fromStdString("Mising value"),QString::fromStdString("You must specify a streaming key"));
    }
}

void PlatformSelectionWindow::cancelPushButtonClicked(){
    this->close();
}

void PlatformSelectionWindow::advancedButtonClicked(){
    controller->displayParametersWindow();
}
