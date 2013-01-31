#ifndef PLATFORMSELECTIONWINDOW_H
#define PLATFORMSELECTIONWINDOW_H

#include <QWidget>

namespace Ui {
class platformSelectionWindow;
}

class platformSelectionWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit platformSelectionWindow(QWidget *parent = 0);
    ~platformSelectionWindow();
    
private:
    Ui::platformSelectionWindow *ui;
};

#endif // PLATFORMSELECTIONWINDOW_H
