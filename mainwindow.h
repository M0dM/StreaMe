#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Phonon>
#include <QUrl>
#include <QFile>
#include <phonon/MediaSource>
#include <Phonon/VideoPlayer>
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
    void startVideo(QBuffer *someBuffer);
    Controller* getController();
private:
    Ui::MainWindow *ui;
    Controller* controller;
    qint64 pos;
    Phonon::MediaObject *mediaObject ;
    Phonon::VideoWidget *videoWidget ;
    Phonon::AudioOutput *audioOutput ;
    QBuffer *bu2 ;
    QBuffer *bu ;
    QByteArray *array1;
    QByteArray *array2;
    QFile *file;
    QWidget *StreamingParametersUi;
    QWidget *PlatformSelectionUi;
public slots :
    void stopClicked();
    void playClicked();
    void rewindClicked();
    void seekchange();
    void enqueueNextSource();
    void setNewTime();
    void newProjectTriggered();
    void openProjectTriggered();
    void useSourceClicked();
    void notUseSourceClicked();
    void configureParametersTrigged();
    void choosePlatformTrigged();
    void windowResized();
};

#endif // MAINWINDOW_H
