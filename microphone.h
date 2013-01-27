#ifndef MICROPHONE_H
#define MICROPHONE_H

#include "source.h"
#include "winavtools.h"

class WinAvTools;

class Microphone  : public Source
{
public:
    Microphone(WinAvTools *avTools, std::string name, std::string type);
private:
    WinAvTools *avTools;
};

#endif // MICROPHONE_H
