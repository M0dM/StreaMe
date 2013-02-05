#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"

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
    QObject::connect(ui->videoPlayer->mediaObject(),SIGNAL(seekableChanged(bool)),SLOT(seekchange()));


    //Set the volume slider
    ui->volumeSlider->setAudioOutput(ui->videoPlayer->audioOutput());


    //test new player
    mediaObject = new Phonon::MediaObject(this);

    videoWidget = new Phonon::VideoWidget(ui->videoPlayer);
    Phonon::createPath(mediaObject, videoWidget);
    audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory, this);
    Phonon::createPath(mediaObject, audioOutput);

    videoWidget->setMinimumWidth(610);
    videoWidget->setMinimumHeight(300);

    bu = new QBuffer();
    array1= new QByteArray();
    bu2 = new QBuffer();
    array2= new QByteArray();
    file = new QFile();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startVideo(QBuffer *someBuffer){
    file->setFileName("C:\\Users\\Romaric\\Documents\\Cours\\StreaMe\\ffmpeg\\bin\\out2.mpeg");
    file->open(QIODevice::ReadOnly);

    *array1 += file->read(300000);
    bu->setBuffer(array1);


    mediaObject->setCurrentSource(bu);
    mediaObject->play();
    QObject::connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)), SLOT(setNewTime()));
    QObject::connect(mediaObject, SIGNAL(aboutToFinish()), SLOT(enqueueNextSource()));

}

void MainWindow::stopClicked(){
    ui->videoPlayer->stop();
    cout << "Stop clicked" << endl;
}

void MainWindow::playClicked(){

    startVideo(bu);
    //controller->playVideo();
    //controller->showVideo();
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

void MainWindow::seekchange(){
    cout << "SEEK Change" << endl ;
}

void MainWindow::enqueueNextSource(){
    cout << "enqueue " << endl;
    pos=mediaObject->totalTime();
    file->close();
    //file->~QFile();
    //file = new QFile();
    //file->setFileName("C:\\Users\\Romaric\\Documents\\Cours\\StreaMe\\ffmpeg\\bin\\out2.mpeg");
    file->open(QIODevice::ReadOnly);
    //file->seek(pos);
    cout << "media pos :" << pos <<endl;
    *array2 = file->read(file->size());
    bu2->setBuffer(array2);
    mediaObject->enqueue(bu2);
}

void MainWindow::setNewTime(){
    cout << "changed !!!!" << endl ;
    mediaObject->seek(pos);
}
