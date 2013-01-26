#include "streamtools.h"

StreamTools::StreamTools(Controller *controller) : WinAvTools(){
    this->controller = controller;
}

void StreamTools::captureVideoFile(int time) const{
    Sleep(time);
}
