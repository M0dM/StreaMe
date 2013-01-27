#ifndef CAMERA_H
#define CAMERA_H

#include "source.h"
#include "winavtools.h"

class WinAvTools;

class Camera : public Source
{
public:
    Camera(WinAvTools *avTools, std::string name, std::string type);
private:
    WinAvTools *avTools;
};

#endif // CAMERA_H
