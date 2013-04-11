#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "streamingparametersconfigurationwindow.h"
#include "ui_streamingparametersconfigurationwindow.h"
#include "platformselectionwindow.h"
#include "ui_platformselectionwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(Controller* controller,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    MainWindow::setController(controller);
    ui->setupUi(this);


    // Connect signal buttons
    QObject::connect(ui->buttonUseSource, SIGNAL(clicked()),this,SLOT(useSourceClicked()));
    QObject::connect(ui->buttonNotUseSource, SIGNAL(clicked()),this,SLOT(notUseSourceClicked()));
    QObject::connect(ui->actionAdd_source, SIGNAL(triggered()),this,SLOT(useSourceClicked()));
    QObject::connect(ui->actionRemove_source, SIGNAL(triggered()),this,SLOT(notUseSourceClicked()));
    QObject::connect(ui->buttonStop, SIGNAL(clicked()),this,SLOT(stopClicked()));
    QObject::connect(ui->buttonPlay, SIGNAL(clicked()),this,SLOT(playClicked()));
    QObject::connect(ui->actionStart, SIGNAL(triggered()),this,SLOT(playClicked()));
    QObject::connect(ui->actionStop, SIGNAL(triggered()),this,SLOT(stopClicked()));
    QObject::connect(ui->actionNew_Project, SIGNAL(triggered()),this,SLOT(newProjectTriggered()));
    QObject::connect(ui->actionOpen_Project, SIGNAL(triggered()),this,SLOT(openProjectTriggered()));
    QObject::connect(ui->actionSave_Project, SIGNAL(triggered()),this,SLOT(saveProjectTriggered()));
    QObject::connect(ui->actionSave_Project_As, SIGNAL(triggered()),this,SLOT(saveProjectAsTriggered()));
    QObject::connect(ui->actionRename, SIGNAL(triggered()),this,SLOT(renameProjectTriggered()));
    QObject::connect(ui->actionConfigure_parameters, SIGNAL(triggered()),this,SLOT(configureParametersTrigged()));
    QObject::connect(ui->actionChoose_Platform, SIGNAL(triggered()),this,SLOT(choosePlatformTrigged()));
    QObject::connect(ui->actionClose, SIGNAL(triggered()),this,SLOT(close()));
    QObject::connect(ui->actionAbout_StreaMe, SIGNAL(triggered()),this,SLOT(aboutStreaMe()));

    //Shortcuts
    this->shortcutSave = new QShortcut(QKeySequence("Ctrl+S"), this);
    this->shortcutPlay = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Space), this);
    this->shortcutStop = new QShortcut(QKeySequence(Qt::CTRL +Qt::SHIFT+ Qt::Key_Space), this);
    QObject::connect(new QShortcut(QKeySequence("Ctrl+N"), this), SIGNAL(activated()), this, SLOT(newProjectTriggered()));
    QObject::connect(new QShortcut(QKeySequence("Ctrl+O"), this), SIGNAL(activated()), this, SLOT(openProjectTriggered()));
    QObject::connect(shortcutSave, SIGNAL(activated()), this, SLOT(saveProjectTriggered()));
    QObject::connect(shortcutPlay, SIGNAL(activated()), this, SLOT(playClicked()));
    QObject::connect(shortcutStop, SIGNAL(activated()), this, SLOT(stopClicked()));

    //test new player
    mediaObject = new Phonon::MediaObject(this);
    videoWidget = new Phonon::VideoWidget(ui->videoPlayer);
    Phonon::createPath(mediaObject, videoWidget);
    audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory, this);
    Phonon::createPath(mediaObject, audioOutput);

    //Set the volume slider
    ui->volumeSlider->setAudioOutput(audioOutput);

    videoWidget->setMinimumWidth(ui->videoPlayer->width());
    videoWidget->setMinimumHeight(ui->videoPlayer->height());

    file = new QFile();
    file->setFileName("why.mpeg");
    file->remove();

    //Def chrono
    playerOn=false;
    firstPlay=false;
    m_chrono = new QTimer();
    minute=0;
    chrono_value=0;
    QObject::connect(m_chrono, SIGNAL(timeout()), SLOT(update_chrono()));
    m_chrono->setInterval(1000);
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
    playerOn=true;
    file->setFileName("why.mpeg");
    file->open(QIODevice::ReadOnly);
    fileSize=file->size();
    *array1 += file->read(file->size());
    bu->setBuffer(array1);

    mediaObject->setCurrentSource(bu);
    chrono_value=0;
    minute=0;
    mediaObject->play();
    mediaObject->setPrefinishMark(200);
    if(!firstPlay){
        QObject::connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)), SLOT(setNewTime()));
        QObject::connect(mediaObject, SIGNAL(aboutToFinish()), SLOT(enqueueNextSource()));
        QObject::connect(mediaObject, SIGNAL(prefinishMarkReached(qint32)), SLOT(videoAlmostFinished()));
        firstPlay=true;
    }


}

void MainWindow::update_chrono(){
    chrono_value++;
    int chrono_mod = chrono_value % 60;
    QString timeChrone = QString::number(minute) + QString::fromStdString(":") + QString::number(chrono_mod) ;
    if(playerOn)
        ui->timeNumber->display(timeChrone);
    if(chrono_mod==59)
        minute++;
}

void MainWindow::newProjectTriggered(){
    controller->generateNewProject();
    controller->displayAssistantWindow();
}

void MainWindow::openProjectTriggered(){
    this->getController()->openProjectFile();
}

void MainWindow::saveProjectTriggered(){
    this->getController()->saveProject();
}

void MainWindow::saveProjectAsTriggered(){
    this->getController()->saveProjectAs();
}



void MainWindow::stopClicked(){
    //Stop the stream and the player
    controller->addFeedback("Stopping streaming...");
    controller->stopStream();
    playerOn=false;
    mediaObject->stop();
    mediaObject->clear();
    //Stop and reinitialize the chrono
    m_chrono->stop();
    chrono_value=0;
    ui->timeNumber->display(0);
    //Clear the file and buffers for the player
    file->remove();
    bu->~QBuffer();
    bu2->~QBuffer();
    array1->~QByteArray();
    array2->~QByteArray();
    //Change the status bar
    ui->statutBarLabel->setText("StatusBar: Streaming status - stopped");
    controller->blockStreamingStop();
    controller->unblockStreamingPlay();

    //this->unblockArrows();
}

void MainWindow::playClicked(){
    bu = new QBuffer();
    array1= new QByteArray();
    bu2 = new QBuffer();
    array2= new QByteArray();

    controller->addFeedback("Starting streaming...");
    ui->statutBarLabel->setText("StatusBar: Streaming status - streaming");

    m_chrono->start();
    controller->stream();

    //this->blockArrows();
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
        this->controller->mutSleep(20);
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
    videoWidget->setFixedWidth(ui->videoPlayer->width());
    videoWidget->setFixedHeight(ui->videoPlayer->height());
    ui->listWidgetFFmpeg->setFixedWidth(ui->tabWidget->width());
    ui->listWidgetFeedback->setFixedWidth(ui->tabWidget->width());
}
void MainWindow::configureParametersTrigged(){
    this->getController()->displayParametersWindow();
}

void MainWindow::choosePlatformTrigged(){
    this->getController()->displayPlatformsWindow();
}

void MainWindow::renameProjectTriggered(){
    this->getController()->displayRenameProjectWindow();
}

void MainWindow::videoAlmostFinished(){
        float i=0.0;
        int val=0;
        while(i<1.0){
            this->controller->mutSleep(20);
            videoWidget->setBrightness(val-i);
            videoWidget->setContrast(val-i);
            i=i+0.1;
        }

}

void MainWindow::disableInterfaceForNewProject(){

    //1st : Block the main menu smartly
    ui->actionSave_Project->setEnabled(false);
    ui->actionSave_Project_As->setEnabled(false);
    ui->menuEdition->setEnabled(false);
    ui->menuConfig->setEnabled(false);
    ui->menuShow->setEnabled(false);
    ui->menuSources->setEnabled(false);

    //2nd : block all the remaining interface
    ui->centralWidget->setEnabled(false);

    //Shortcuts
    this->shortcutSave->setEnabled(false);
    this->shortcutPlay->setEnabled(false);
    this->shortcutStop->setEnabled(false);
}

void MainWindow::enableInterfaceForNewProject(){

    //1st : Block the main menu smartly
    ui->actionSave_Project->setEnabled(true);
    ui->actionSave_Project_As->setEnabled(true);
    ui->menuEdition->setEnabled(true);
    ui->menuConfig->setEnabled(true);
    ui->menuShow->setEnabled(true);
    ui->menuSources->setEnabled(true);

    //2nd : block all the remaining interface
    ui->centralWidget->setEnabled(true);

    //Shortcuts
    this->shortcutSave->setEnabled(true);
    this->shortcutPlay->setEnabled(true);
    this->shortcutStop->setEnabled(true);
}

void MainWindow::blockPlay(){
    ui->buttonPlay->setEnabled(false);
}

void MainWindow::blockStop(){
    ui->buttonStop->setEnabled(false);
}
void MainWindow::unblockPlay(){
    ui->buttonPlay->setEnabled(true);
}

void MainWindow::unblockStop(){
    ui->buttonStop->setEnabled(true);
}


void MainWindow::addLineFeedback(QString line){
    ui->listWidgetFeedback->addItem(line);
    ui->listWidgetFeedback->scrollToBottom();
}

void MainWindow::emptySourcesLists(){
    this->ui->listFreeSources->clear();
    this->ui->listUsedSources->clear();
}

void MainWindow::addFFmpegLineFeedback(QString feedback){
    ui->listWidgetFFmpeg->addItem(feedback.mid(0,1000));
    //cout << feedback.length() << endl;
    if(ui->listWidgetFFmpeg->isVisible())
        ui->listWidgetFFmpeg->scrollToBottom();
}

void MainWindow::aboutStreaMe(){
    QMessageBox::information(this,QString::fromStdString("About StreaMe"),QString::fromStdString("StreaMe is an open source software developped for a school project by Benoit Brayer, Nans Plancher and Romaric Delaunoy in 2013."));
}

void MainWindow::blockArrows(){
    ui->buttonUseSource->setEnabled(false);
    ui->buttonNotUseSource->setEnabled(false);
}

void MainWindow::unblockArrows(){
    ui->buttonUseSource->setEnabled(true);
    ui->buttonNotUseSource->setEnabled(true);
}
