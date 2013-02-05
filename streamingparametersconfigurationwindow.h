#ifndef STREAMINGPARAMETERSCONFIGURATIONWINDOW_H
#define STREAMINGPARAMETERSCONFIGURATIONWINDOW_H

#include <QWidget>
#include <controller.h>

namespace Ui {
class StreamingParametersConfigurationWindow;
}

class StreamingParametersConfigurationWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit StreamingParametersConfigurationWindow(QWidget *parent = 0);
    ~StreamingParametersConfigurationWindow();
    
private:
    Ui::StreamingParametersConfigurationWindow *ui;

//public slots:
//    void videoSizeComboBoxIndexChanged(int);
//    void videoFormatComboBoxIndexChanged(int);
//    void enableAutoConfigurationRadioButtonClicked(bool);
//    void disableAutoConfigurationRadioButtonClicked(bool);
//    void uploadSpeedHorizontalSliderClicked(int);
//    void audioBitrateComboBoxIndexChanged(int);
//    void stereoRadioButtonClicked(bool);
//    void monoRadioButtonClicked(bool);
//    void okPushButtonClicked();
//    void exitPushButtonClicked();

};

#endif // STREAMINGPARAMETERSCONFIGURATIONWINDOW_H
