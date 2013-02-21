#ifndef NEWPROJECTASSISTANT_H
#define NEWPROJECTASSISTANT_H

#include <QWidget>
#include "controller.h"

class Controller;

namespace Ui {
class NewProjectAssistant;
}

class NewProjectAssistant : public QWidget
{
    Q_OBJECT
    
public:
    explicit NewProjectAssistant(Controller* controller, QWidget *parent = 0);
    void setController(Controller* controller);
    Controller* getController();
    ~NewProjectAssistant();
    
public slots:
    void nextButtonClicked();

private:
    Ui::NewProjectAssistant *ui;
    Controller* controller;

};

#endif // NEWPROJECTASSISTANT_H
