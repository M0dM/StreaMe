#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <phonon/VideoWidget>
#include <QUrl>
#include <QFile>
#include <QString>
#include <phonon/MediaSource>
#include <phonon/VideoPlayer>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <phonon/effect.h>
#include <phonon/effectparameter.h>
#include <phonon/objectdescriptionmodel.h>
#include <QBuffer>
#include <QMainWindow>
#include <QWidget>
#include "controller.h"
//#include "windows.h"

class Controller;
class Source;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Controller* controller,QWidget *parent = 0);
    void closeEvent(QCloseEvent *event = 0);
    ~MainWindow();
    void setFreeSources(QStringList freeSources);
    void setUsedSources(QStringList usedSources);
    void emptySourcesLists();
    void startVideo();
    Controller* getController();
    void setController(Controller* controller);
    void generateNewProject();
    void disableInterfaceForNewProject();
    void enableInterfaceForNewProject();
    void blockPlay();
    void blockStop();
    void unblockPlay();
    void unblockStop();
    void addLineFeedback(QString line);
    void addFFmpegLineFeedback(QString feedback);
private:
    Ui::MainWindow *ui;
    Controller* controller;
    qint64 pos,fileSize,oldFileSize;
    Phonon::MediaObject *mediaObject ;
    Phonon::VideoWidget *videoWidget ;
    Phonon::AudioOutput *audioOutput ;
    QBuffer *bu2 ;
    QBuffer *bu ;
    QByteArray *array1;
    QByteArray *array2;
    QFile *file;
    QTimer *m_chrono;
    QUrl *url;
    int chrono_value;
    int minute;
    bool playerOn, firstPlay, seekBool;
protected:
    void resizeEvent(QResizeEvent * event );
public slots :
    void stopClicked();
    void playClicked();
    void enqueueNextSource();
    void setNewTime();
    void newProjectTriggered();
    void openProjectTriggered();
    void saveProjectTriggered();
    void saveProjectAsTriggered();
    void renameProjectTriggered();
    void useSourceClicked();
    void notUseSourceClicked();
    void configureParametersTrigged();
    void choosePlatformTrigged();
    void videoAlmostFinished();
    void update_chrono();
};

#endif // MAINWINDOW_H
