#include "microphone.h"

Microphone::Microphone(WinAvTools *avTools, std::string name, std::string type) : Source(name,type)
{
    this->avTools = avTools;
}
