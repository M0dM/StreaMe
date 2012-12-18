#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controllerview.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(ControllerView* controller,QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    ControllerView controller;
};

#endif // MAINWINDOW_H
