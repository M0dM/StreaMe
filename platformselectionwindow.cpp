#include "platformselectionwindow.h"
#include "ui_platformselectionwindow.h"


platformSelectionWindow::platformSelectionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::platformSelectionWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->okPushButton, SIGNAL(clicked()),this,SLOT(okPushButtonClicked()));
    QObject::connect(ui->exitPushButton, SIGNAL(clicked()),this,SLOT(exitPushButtonClicked()));
}

platformSelectionWindow::~platformSelectionWindow()
{
    delete ui;
}

void platformSelectionWindow::okPushButtonClicked(){

}

void platformSelectionWindow::exitPushButtonClicked(){

}
