#include "streamingparametersconfigurationwindow.h"
#include "ui_streamingparametersconfigurationwindow.h"

StreamingParametersConfigurationWindow::StreamingParametersConfigurationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StreamingParametersConfigurationWindow)
{
    ui->setupUi(this);
}

StreamingParametersConfigurationWindow::~StreamingParametersConfigurationWindow()
{
    delete ui;
}
