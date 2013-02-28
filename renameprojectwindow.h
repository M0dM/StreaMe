#ifndef RENAMEPROJECTWINDOW_H
#define RENAMEPROJECTWINDOW_H

#include <QWidget>
#include "controller.h"

namespace Ui {
class RenameProjectWindow;
}

class RenameProjectWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit RenameProjectWindow(Controller* controller, QWidget *parent = 0);
    ~RenameProjectWindow();
    Controller* getController();
    void setController(Controller* controller);

private:
    Ui::RenameProjectWindow *ui;
    Controller* controller;

public slots:
    void okPushButtonClicked();
    void cancelPushButtonClicked();
};

#endif // RENAMEPROJECTWINDOW_H
