#ifndef STREAMINGPARAMETERSCONFIGURATIONWINDOW_H
#define STREAMINGPARAMETERSCONFIGURATIONWINDOW_H

#include <QObject>
#include "controller.h"

namespace Ui {
class StreamingParametersConfigurationWindow;
}

class StreamingParametersConfigurationWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit StreamingParametersConfigurationWindow(Controller* controller, QWidget *parent = 0);
    ~StreamingParametersConfigurationWindow();
    Controller* getController();
    void setController(Controller* controller);
    
private:
    Ui::StreamingParametersConfigurationWindow *ui;
    Controller* controller;

public slots:
    void videoSizeComboBoxIndexChanged(int);
    void videoFormatComboBoxIndexChanged(int);
    void enableAutoConfigurationRadioButtonClicked(bool);
    void disableAutoConfigurationRadioButtonClicked(bool);
    void uploadSpeedHorizontalSliderChanged(int);
    void audioBitrateComboBoxIndexChanged(int);
    void stereoRadioButtonClicked(bool);
    void monoRadioButtonClicked(bool);
    void okPushButtonClicked();
    void exitPushButtonClicked();

};

#endif // STREAMINGPARAMETERSCONFIGURATIONWINDOW_H
