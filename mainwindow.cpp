#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller* controller,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->controller=controller;
    ui->setupUi(this);

    QString fileName("test.avi");


         ui->volumeSlider->setAudioOutput(ui->videoPlayer->audioOutput());

    ui->videoPlayer->load(fileName);
    ui->videoPlayer->play();
    ui->videoPlayer->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFreeSources(QStringList freeSources){
    ui->listFreeSources->addItems(freeSources);
}
