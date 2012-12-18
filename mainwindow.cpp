#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller* controller,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->controller=controller;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
