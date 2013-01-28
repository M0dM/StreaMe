#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller* controller,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->controller=controller;
    ui->setupUi(this);

    // Connect signal buttons
    QObject::connect(ui->buttonStop, SIGNAL(clicked()),this,SLOT(stopClicked()));
    QObject::connect(ui->buttonPlay, SIGNAL(clicked()),this,SLOT(playClicked()));
    QObject::connect(ui->buttonRewind, SIGNAL(clicked()),this,SLOT(rewindClicked()));

    //Set the volume slider
    ui->volumeSlider->setAudioOutput(ui->videoPlayer->audioOutput());

    //Test reading a video file
    QString fileName("test.avi");
    //QString fileName("C:\\Users\\Romaric\\Documents\\Cours\\StreaMe-build-Desktop-Debug\\test.avi");
    //QBuffer *someBuffer;
    ui->videoPlayer->load(fileName);
    ui->videoPlayer->play();
    ui->videoPlayer->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::stopClicked(){
    ui->videoPlayer->stop();
    cout << "Stop clicked" << endl;
}

void MainWindow::playClicked(){
    ui->videoPlayer->pause();
    cout << "Play clicked" << endl;
}

void MainWindow::rewindClicked(){
    ui->videoPlayer->stop();
    ui->videoPlayer->play();
    cout << "Rewind clicked" << endl;
}

void MainWindow::setFreeSources(QStringList freeSources){
    ui->listFreeSources->addItems(freeSources);
}
