#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "streamingparametersconfigurationwindow.h"
#include "ui_streamingparametersconfigurationwindow.h"
#include "platformselectionwindow.h"
#include "ui_platformselectionwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(Controller* controller,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    MainWindow::setController(controller);
    ui->setupUi(this);


    // Connect signal buttons
    QObject::connect(ui->buttonUseSource, SIGNAL(clicked()),this,SLOT(useSourceClicked()));
    QObject::connect(ui->buttonNotUseSource, SIGNAL(clicked()),this,SLOT(notUseSourceClicked()));
    QObject::connect(ui->buttonStop, SIGNAL(clicked()),this,SLOT(stopClicked()));
    QObject::connect(ui->buttonPlay, SIGNAL(clicked()),this,SLOT(playClicked()));
    QObject::connect(ui->buttonRewind, SIGNAL(clicked()),this,SLOT(rewindClicked()));
    QObject::connect(ui->actionNew_Project, SIGNAL(triggered()),this,SLOT(newProjectTriggered()));
    QObject::connect(ui->actionOpen_Project, SIGNAL(triggered()),this,SLOT(openProjectTriggered()));
    QObject::connect(ui->actionSave_Project, SIGNAL(triggered()),this,SLOT(saveProjectTriggered()));
    QObject::connect(ui->actionSave_Project_As, SIGNAL(triggered()),this,SLOT(saveProjectAsTriggered()));
    QObject::connect(ui->videoPlayer->mediaObject(),SIGNAL(seekableChanged(bool)),SLOT(seekchange()));
    QObject::connect(ui->actionConfigure_parameters, SIGNAL(triggered()),this,SLOT(configureParametersTrigged()));
    QObject::connect(ui->actionChoose_Platform, SIGNAL(triggered()),this,SLOT(choosePlatformTrigged()));

    //Set the volume slider
    ui->volumeSlider->setAudioOutput(ui->videoPlayer->audioOutput());

    //test new player
    mediaObject = new Phonon::MediaObject(this);

    videoWidget = new Phonon::VideoWidget(ui->videoPlayer);
    Phonon::createPath(mediaObject, videoWidget);
    audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory, this);
    Phonon::createPath(mediaObject, audioOutput);

    videoWidget->setMinimumWidth(ui->videoPlayer->width());
    videoWidget->setMinimumHeight(ui->videoPlayer->height());

    bu = new QBuffer();
    array1= new QByteArray();
    bu2 = new QBuffer();
    array2= new QByteArray();
    file = new QFile();
    file->setFileName("why.mpeg");
    file->remove();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete controller;
}

Controller* MainWindow::getController(){
    return controller;
}

void MainWindow::setController(Controller* controller){
    this->controller = controller;
}

void MainWindow::closeEvent(QCloseEvent *event){
    delete this;
}


void MainWindow::startVideo(){
    file->setFileName("why.mpeg");
    file->open(QIODevice::ReadOnly);
    fileSize=file->size();
    *array1 += file->read(file->size());
    bu->setBuffer(array1);

    mediaObject->setCurrentSource(bu);
    mediaObject->play();
    //mediaObject->setTransitionTime(-100);
    mediaObject->setPrefinishMark(200);
    QObject::connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)), SLOT(setNewTime()));
    QObject::connect(mediaObject, SIGNAL(aboutToFinish()), SLOT(enqueueNextSource()));
    QObject::connect(mediaObject, SIGNAL(prefinishMarkReached(qint32)), SLOT(videoAlmostFinished()));
}


void MainWindow::newProjectTriggered(){
    controller->generateNewProject();
    controller->displayAssistantWindow();
}

void MainWindow::openProjectTriggered(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"),"/",tr("StreaMe File (*.sm)"));
    if(fileName.toStdString() != ""){
        if(this->getController()->getProject()->load(fileName.toStdString())==true){
            QMessageBox msgBox;
            msgBox.setText("The StreaMe project was corectly loaded.");
            msgBox.exec();
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("Problem when loading the StreaMe project.");
            msgBox.exec();
        }
    }
}

void MainWindow::saveProjectTriggered(){
    if(this->getController()->getProjectFileUrl() == ""){
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/",tr("StreaMe File (*.sm)"));
        if(fileName.toStdString() != ""){
            if(this->getController()->getProject()->save(fileName.toStdString()) == true){
                QMessageBox msgBox;
                msgBox.setText("The StreaMe project was saved successfully.");
                msgBox.exec();
            }
            else{
                QMessageBox msgBox;
                msgBox.setText("Problem when saving the new StreaMe project.");
                msgBox.exec();
            }
        }
    }
    else{
        this->getController()->getProject()->save(this->getController()->getProjectFileUrl());
    }
}

void MainWindow::saveProjectAsTriggered(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/",tr("StreaMe File (*.sm)"));
    if(fileName.toStdString() != ""){
        if(this->getController()->getProject()->save(fileName.toStdString()) == true){
            QMessageBox msgBox;
            msgBox.setText("The StreaMe project was saved successfully.");
            this->getController()->setProjectFileUrl(fileName.toStdString());
            msgBox.exec();
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("Problem when saving the new StreaMe project.");
            msgBox.exec();
        }
    }
}


void MainWindow::stopClicked(){
    controller->stopStream();
    //    ui->statutBarLabel->setText("StatusBar: Streaming status - stopped");
}

void MainWindow::playClicked(){
    controller->stream();
    //ui->statutBarLabel->setText("StatusBar: Streaming status - streaming");
}

void MainWindow::rewindClicked(){
    ui->statutBarLabel->setText("StatusBar: Streaming status - rewinding");
    ui->videoPlayer->stop();
    ui->statutBarLabel->setText("StatusBar: Streaming status - stopped");
    ui->videoPlayer->play();
    ui->statutBarLabel->setText("StatusBar: Streaming status - streaming");
    cout << "Rewind clicked" << endl;
}


void MainWindow::enqueueNextSource(){
    pos=mediaObject->totalTime();
    oldFileSize=fileSize;
    file->close();
    file->open(QIODevice::ReadOnly);
    fileSize=file->size();
    if(fileSize!=oldFileSize)
    {
        *array2 = file->read(file->size());
        bu2->close();
        bu2->setBuffer(array2);
        mediaObject->enqueue(bu2);
    }

}

void MainWindow::setNewTime(){
    float i=0.0;
    int val=-1;
    mediaObject->seek(pos);
    while(i<1.0){
        Sleep(20);
        videoWidget->setBrightness(val+i);
        videoWidget->setContrast(val+i);
        i=i+0.1;
    }
}

void MainWindow::setFreeSources(QStringList freeSources){
    ui->listFreeSources->clear();
    ui->listFreeSources->addItems(freeSources);
}

void MainWindow::setUsedSources(QStringList usedSources){
    ui->listUsedSources->clear();
    ui->listUsedSources->addItems(usedSources);
}

void MainWindow::useSourceClicked(){
    if(ui->listFreeSources->currentRow()>=0)
        controller->useSource(ui->listFreeSources->item(ui->listFreeSources->currentRow())->text().toStdString());
}

void MainWindow::notUseSourceClicked(){
    if(ui->listUsedSources->currentRow()>=0)
        controller->notUseSource(ui->listUsedSources->item(ui->listUsedSources->currentRow())->text().toStdString());
}

void MainWindow::resizeEvent (QResizeEvent * event){
    videoWidget->setMinimumWidth(ui->videoPlayer->width());
    videoWidget->setMinimumHeight(ui->videoPlayer->height());
    videoWidget->setMaximumHeight(ui->videoPlayer->maximumHeight());
    videoWidget->setMaximumWidth(ui->videoPlayer->maximumWidth());
}

void MainWindow::configureParametersTrigged(){
    controller->displayParametersWindow();
}

void MainWindow::choosePlatformTrigged(){
    controller->displayPlatformsWindow();
}

void MainWindow::videoAlmostFinished(){
        float i=0.0;
        int val=0;

        while(i<1.0){
            Sleep(20);
            videoWidget->setBrightness(val-i);
            videoWidget->setContrast(val-i);
            i=i+0.1;
        }
}

