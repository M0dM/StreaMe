#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Phonon>
#include <QUrl>
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
#include "platformselectionwindow.h"
#include "streamingparametersconfigurationwindow.h"
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
    ~MainWindow();
    void setFreeSources(QStringList freeSources);
    void setUsedSources(QStringList usedSources);
private:
    Ui::MainWindow *ui;
    Controller* controller;
    Controller* getController();
    QWidget *StreamingParametersUi;
    QWidget *PlatformSelectionUi;
public slots :
    void newProjectTriggered();
    void openProjectTriggered();
    void stopClicked();
    void playClicked();
    void rewindClicked();
    void useSourceClicked();
    void notUseSourceClicked();
    void configureParametersTrigged();
    void choosePlatformTrigged();
};

#endif // MAINWINDOW_H
