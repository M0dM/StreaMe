#include "streamingparametersconfigurationwindow.h"
#include "ui_streamingparametersconfigurationwindow.h"

StreamingParametersConfigurationWindow::StreamingParametersConfigurationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StreamingParametersConfigurationWindow)
{
    ui->setupUi(this);

    // Connect signal buttons
//    QObject::connect(ui->videoSizeComboBox, SIGNAL(currentIndexChanged(int)),this,SLOT(videoSizeComboBoxIndexChanged(int)));
//    QObject::connect(ui->videoFormatComboBox, SIGNAL(currentIndexChanged(int)),this,SLOT(videoFormatComboBoxIndexChanged(int)));
//    QObject::connect(ui->enableAutoConfigurationRadioButton, SIGNAL(clicked(bool)),this,SLOT(enableAutoConfigurationRadioButtonClicked(bool)));
//    QObject::connect(ui->disableAutoConfigurationRadioButton, SIGNAL(clicked(bool)),this,SLOT(disableAutoConfigurationRadioButtonClicked(bool)));
//    QObject::connect(ui->uploadSpeedHorizontalSlider, SIGNAL(valueChanged(int)),this,SLOT(uploadSpeedHorizontalSliderClicked(int)));
//    QObject::connect(ui->audioBitrateComboBox, SIGNAL(currentIndexChanged(int)),this,SLOT(audioBitrateComboBoxIndexChanged(int)));
//    QObject::connect(ui->stereoRadioButton, SIGNAL(clicked(bool)),this,SLOT(stereoRadioButtonClicked(bool)));
//    QObject::connect(ui->monoRadioButton, SIGNAL(clicked(bool)),this,SLOT(monoRadioButtonClicked(bool)));
//    QObject::connect(ui->okPushButton, SIGNAL(clicked()),this,SLOT(okPushButtonClicked()));
//    QObject::connect(ui->exitPushButton, SIGNAL(clicked()),this,SLOT(exitPushButtonClicked()));
}

StreamingParametersConfigurationWindow::~StreamingParametersConfigurationWindow()
{
    delete ui;
}

