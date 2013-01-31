#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(Controller* controller,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->controller=controller;
    ui->setupUi(this);

    // Connect signal buttons
    QObject::connect(ui->buttonUseSource, SIGNAL(clicked()),this,SLOT(useSourceClicked()));
    QObject::connect(ui->buttonNotUseSource, SIGNAL(clicked()),this,SLOT(notUseSourceClicked()));
    QObject::connect(ui->buttonStop, SIGNAL(clicked()),this,SLOT(stopClicked()));
    QObject::connect(ui->buttonPlay, SIGNAL(clicked()),this,SLOT(playClicked()));
    QObject::connect(ui->buttonRewind, SIGNAL(clicked()),this,SLOT(rewindClicked()));
    QObject::connect(ui->actionNew_Project, SIGNAL(triggered()),this,SLOT(newProjectTriggered()));
    QObject::connect(ui->actionOpen_Project, SIGNAL(triggered()),this,SLOT(openProjectTriggered()));

    //Set the volume slider
    ui->volumeSlider->setAudioOutput(ui->videoPlayer->audioOutput());

    //Test reading a video file
    //QString fileName("test.avi");
    QString fileName("C:\\Users\\nansp_000\\Dropbox\\Projets\\Qt Creator\\StreaMe\\ffmpeg\\catchedFiles\\out.mpeg");
    //QBuffer *someBuffer;
    //ui->videoPlayer->load(fileName);
    ui->videoPlayer->play(fileName);
    ui->videoPlayer->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newProjectTriggered(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/",tr("StreaMe File (*.sm)"));
    if(this->getController()->getProject()->save(fileName.toStdString())==true){
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

void MainWindow::openProjectTriggered(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"),"/",tr("StreaMe File (*.sm)"));
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

void MainWindow::stopClicked(){
    ui->statutBarLabel->setText("StatusBar: Streaming status - stopped");
    ui->videoPlayer->stop();
    cout << "Stop clicked" << endl;
}

void MainWindow::playClicked(){
    ui->statutBarLabel->setText("StatusBar: Streaming status - streaming");
    ui->videoPlayer->pause();
    cout << "Play clicked" << endl;
}

void MainWindow::rewindClicked(){
    ui->statutBarLabel->setText("StatusBar: Streaming status - rewinding");
    ui->videoPlayer->stop();
    ui->statutBarLabel->setText("StatusBar: Streaming status - stopped");
    ui->videoPlayer->play();
    ui->statutBarLabel->setText("StatusBar: Streaming status - streaming");
    cout << "Rewind clicked" << endl;
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

Controller* MainWindow::getController(){
    return controller;
}
