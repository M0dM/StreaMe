#ifndef CHOOSECREATEOPENPROJECT_H
#define CHOOSECREATEOPENPROJECT_H

#include <QDialog>
#include "controller.h"
namespace Ui {
class ChooseCreateOpenProject;
}

class ChooseCreateOpenProject : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChooseCreateOpenProject(Controller* controller,QWidget *parent = 0);
    ~ChooseCreateOpenProject();
    
public slots:
    void nextClicked();
private:
    Controller* controller;
    Ui::ChooseCreateOpenProject *ui;
};

#endif // CHOOSECREATEOPENPROJECT_H
