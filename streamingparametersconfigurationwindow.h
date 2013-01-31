#ifndef STREAMINGPARAMETERSCONFIGURATIONWINDOW_H
#define STREAMINGPARAMETERSCONFIGURATIONWINDOW_H

#include <QWidget>

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
};

#endif // STREAMINGPARAMETERSCONFIGURATIONWINDOW_H
