#include "streamingparametersconfigurationwindow.h"
#include "ui_streamingparametersconfigurationwindow.h"
#include <iostream>
#include <sstream>

using namespace std;

StreamingParametersConfigurationWindow::StreamingParametersConfigurationWindow(Controller* controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StreamingParametersConfigurationWindow)
{
    StreamingParametersConfigurationWindow::setController(controller);
    ui->setupUi(this);

    // set values
    ui->videoSizeComboBox->setCurrentIndex(this->getController()->getProject()->getVideoSizeIndex());
    ui->videoFormatComboBox->setCurrentIndex(this->getController()->getProject()->getVideoFormatIndex());

    if(this->getController()->getProject()->getAutoConfiguration() == true){
        ui->enableAutoConfigurationRadioButton->setChecked(true);
        ui->disableAutoConfigurationRadioButton->setChecked(false);
        ui->groupBox->setEnabled(false);
        ui->uploadSpeedHorizontalSlider->setEnabled(true);
        ui->uploadSpeedLabel->setEnabled(true);
        ui->uploadSpeedValueLabel->setEnabled(true);
    }
    else{
        ui->uploadSpeedHorizontalSlider->setEnabled(false);
        ui->uploadSpeedLabel->setEnabled(false);
        ui->uploadSpeedValueLabel->setEnabled(false);
    }

    ui->uploadSpeedHorizontalSlider->setValue(this->getController()->getProject()->getUploadSpeed());
    ui->uploadSpeedValueLabel->setText(this->getController()->getProject()->getUploadSpeedQstring());
    ui->videoBitrateLineEdit->setText(this->getController()->getProject()->getVideoBitrateQstring());
    ui->audioBitrateComboBox->setCurrentIndex(this->getController()->getProject()->getAudioBitrateIndex());

    if(this->getController()->getProject()->getStereoConfiguration() == true){
        ui->stereoRadioButton->setChecked(true);
        ui->monoRadioButton->setChecked(false);
    }else
    {
        ui->stereoRadioButton->setChecked(false);
        ui->monoRadioButton->setChecked(true);
    }

    // Connect signal buttons
   QObject::connect(ui->videoSizeComboBox, SIGNAL(currentIndexChanged(int)),this,SLOT(videoSizeComboBoxIndexChanged(int)));
   QObject::connect(ui->videoFormatComboBox, SIGNAL(currentIndexChanged(int)),this,SLOT(videoFormatComboBoxIndexChanged(int)));
   QObject::connect(ui->enableAutoConfigurationRadioButton, SIGNAL(clicked(bool)),this,SLOT(enableAutoConfigurationRadioButtonClicked(bool)));
   QObject::connect(ui->disableAutoConfigurationRadioButton, SIGNAL(clicked(bool)),this,SLOT(disableAutoConfigurationRadioButtonClicked(bool)));
   QObject::connect(ui->uploadSpeedHorizontalSlider, SIGNAL(valueChanged(int)),this,SLOT(uploadSpeedHorizontalSliderChanged(int)));
   QObject::connect(ui->audioBitrateComboBox, SIGNAL(currentIndexChanged(int)),this,SLOT(audioBitrateComboBoxIndexChanged(int)));
   QObject::connect(ui->stereoRadioButton, SIGNAL(clicked(bool)),this,SLOT(stereoRadioButtonClicked(bool)));
   QObject::connect(ui->monoRadioButton, SIGNAL(clicked(bool)),this,SLOT(monoRadioButtonClicked(bool)));
   QObject::connect(ui->okPushButton, SIGNAL(clicked()),this,SLOT(okPushButtonClicked()));
   QObject::connect(ui->cancelButton, SIGNAL(clicked()),this,SLOT(cancelButtonClicked()));
}

Controller* StreamingParametersConfigurationWindow::getController(){
    return controller;
}

void StreamingParametersConfigurationWindow::setController(Controller* controller){
    this->controller = controller;
}

StreamingParametersConfigurationWindow::~StreamingParametersConfigurationWindow()
{
    delete ui;
}

void StreamingParametersConfigurationWindow::videoSizeComboBoxIndexChanged(int index){
    //cout << "video size choosed index: " << index << endl;
}

void StreamingParametersConfigurationWindow::videoFormatComboBoxIndexChanged(int index){
    cout << "video format choosed index: " << index << endl;
}

void StreamingParametersConfigurationWindow::enableAutoConfigurationRadioButtonClicked(bool value){
    if(value){
        ui->uploadSpeedHorizontalSlider->setEnabled(true);
        ui->uploadSpeedLabel->setEnabled(true);
        ui->uploadSpeedValueLabel->setEnabled(true);
        ui->groupBox->setEnabled(false);
   }
}

void StreamingParametersConfigurationWindow::disableAutoConfigurationRadioButtonClicked(bool value){
    if(value){
        ui->uploadSpeedHorizontalSlider->setEnabled(false);
        ui->uploadSpeedLabel->setEnabled(false);
        ui->uploadSpeedValueLabel->setEnabled(false);
        ui->groupBox->setEnabled(true);
    }
}

void StreamingParametersConfigurationWindow::uploadSpeedHorizontalSliderChanged(int value){

    // convert integer values to string
    value = value - value%50;
    std::ostringstream oss;
    oss << value;
    string stdStringValue = oss.str();

    // convert to qstring
    QString qstringValue = QString::fromStdString(stdStringValue);
    ui->uploadSpeedValueLabel->setText(qstringValue);

    if(value <1000){
        ui->videoBitrateLineEdit->setText(QString::fromStdString("500"));
        ui->audioBitrateComboBox->setCurrentIndex(0);
        ui->stereoRadioButton->setChecked(false);
        ui->monoRadioButton->setChecked(true);
    }
    else if (value <2000 && value > 1000){
        ui->videoBitrateLineEdit->setText(QString::fromStdString("1000"));
        ui->audioBitrateComboBox->setCurrentIndex(1);
        ui->stereoRadioButton->setChecked(true);
        ui->monoRadioButton->setChecked(false);
    }
    else if (value <3000 && value > 2000){
        ui->videoBitrateLineEdit->setText(QString::fromStdString("1300"));
        ui->audioBitrateComboBox->setCurrentIndex(2);
        ui->stereoRadioButton->setChecked(true);
        ui->monoRadioButton->setChecked(false);
    }
    else if (value <5000 && value >3000){
        ui->videoBitrateLineEdit->setText(QString::fromStdString("1500"));
        ui->audioBitrateComboBox->setCurrentIndex(3);
        ui->stereoRadioButton->setChecked(true);
        ui->monoRadioButton->setChecked(false);
    }
    else if (value > 5000){
        ui->videoBitrateLineEdit->setText(QString::fromStdString("1800"));
        ui->audioBitrateComboBox->setCurrentIndex(3);
        ui->stereoRadioButton->setChecked(true);
        ui->monoRadioButton->setChecked(false);
    }
}

void StreamingParametersConfigurationWindow::audioBitrateComboBoxIndexChanged(int index){
    //cout << "audio bitrate changed to index: " << index << endl;
}

void StreamingParametersConfigurationWindow::stereoRadioButtonClicked(bool value){
    if(value){
        //cout << "stereo audio choosed" << endl;
    }
}

void StreamingParametersConfigurationWindow::monoRadioButtonClicked(bool value){
    if(value){
        //cout << "mono audio choosed" << endl;
    }
}

void StreamingParametersConfigurationWindow::okPushButtonClicked(){

    if(ui->enableAutoConfigurationRadioButton->isChecked()){
        this->getController()->setProjectAutoConfiguration(true);
    }
    else{
        this->getController()->setProjectAutoConfiguration(false);
    }

    string stdStringUploadString = ui->uploadSpeedValueLabel->text().toStdString();
    string stdStringVideoBitrate = ui->videoBitrateLineEdit->text().toStdString();
    istringstream bufferUploadString(stdStringUploadString);
    istringstream bufferVideoBitrate(stdStringVideoBitrate);
    int intUploadSpeed, intVideoBitrate;
    bufferUploadString >> intUploadSpeed;
    bufferVideoBitrate >> intVideoBitrate;

    this->getController()->setStreamingParametersValue(ui->videoSizeComboBox->currentIndex(), ui->videoFormatComboBox->currentIndex(),
                                                       intUploadSpeed, intVideoBitrate, ui->audioBitrateComboBox->currentIndex());

    if(ui->stereoRadioButton->isChecked()){
        this->getController()->setProjectStereoConfiguration(true);
    }
    else{
        this->getController()->setProjectStereoConfiguration(false);
    }

    this->close();
}

void StreamingParametersConfigurationWindow::cancelButtonClicked(){
    this->close();
}
