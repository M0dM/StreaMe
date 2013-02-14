#ifndef PLATFORMSELECTIONWINDOW_H
#define PLATFORMSELECTIONWINDOW_H

#include <QWidget>
#include "controller.h"
#include <QMessageBox>
namespace Ui {
class platformSelectionWindow;
}

class PlatformSelectionWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlatformSelectionWindow(Controller* controller, QWidget *parent = 0);
    ~PlatformSelectionWindow();
    Controller* getController();
    void setController(Controller* controller);
    
private:
    Ui::platformSelectionWindow *ui;
    Controller* controller;

public slots:
    void okPushButtonClicked();
    void cancelPushButtonClicked();
    void advancedButtonClicked();
};

#endif // PLATFORMSELECTIONWINDOW_H
