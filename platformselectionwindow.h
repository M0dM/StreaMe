#ifndef PLATFORMSELECTIONWINDOW_H
#define PLATFORMSELECTIONWINDOW_H

#include <QWidget>
#include "controller.h"

namespace Ui {
class platformSelectionWindow;
}

class platformSelectionWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit platformSelectionWindow(Controller* controller, QWidget *parent = 0);
    ~platformSelectionWindow();
    Controller* getController();
    void setController(Controller* controller);
    
private:
    Ui::platformSelectionWindow *ui;
    Controller* controller;

public slots:
    void okPushButtonClicked();
    void exitPushButtonClicked();
};

#endif // PLATFORMSELECTIONWINDOW_H
