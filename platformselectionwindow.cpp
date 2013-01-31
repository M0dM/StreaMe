#include "platformselectionwindow.h"
#include "ui_platformselectionwindow.h"

platformSelectionWindow::platformSelectionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::platformSelectionWindow)
{
    ui->setupUi(this);
}

platformSelectionWindow::~platformSelectionWindow()
{
    delete ui;
}
