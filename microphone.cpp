#include "microphone.h"

Microphone::Microphone(AvTools *avTools, std::string name, std::string type, std::string systemName) : Source(name,type,systemName)
{
    this->avTools = avTools;
}
