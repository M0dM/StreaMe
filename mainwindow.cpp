#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller* controller,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->controller=controller;
    ui->setupUi(this);

    QString fileName("Futurama [1x01] The Space Pilot 3000.avi");


         ui->volumeSlider->setAudioOutput(ui->videoPlayer->audioOutput());

    ui->videoPlayer->load(fileName);
    ui->videoPlayer->play();
    ui->videoPlayer->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
