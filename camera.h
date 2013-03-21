#ifndef CAMERA_H
#define CAMERA_H

#include "source.h"
#include "avtools.h"

class AvTools;

class Camera : public Source
{
public:
    Camera(AvTools *avTools, std::string name, std::string type, std::string systemName);
private:
    AvTools *avTools;
};

#endif // CAMERA_H
