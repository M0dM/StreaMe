#include "camera.h"

Camera::Camera(WinAvTools *avTools, std::string name, std::string type) : Source(name, type)
{
    this->avTools=avTools;
}
