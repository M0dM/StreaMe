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
#include "controller.h"

class Controller;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Controller* controller,QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    Controller* controller;
public slots :
    void stopClicked();
    void playClicked();
    void rewindClicked();
};

#endif // MAINWINDOW_H
