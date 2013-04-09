#ifndef MICROPHONE_H
#define MICROPHONE_H

#include "source.h"
#include "avtools.h"

class AvTools ;

class Microphone  : public Source
{
public:
    Microphone(AvTools *avTools, std::string name, std::string type, std::string systemName);
private:
    AvTools *avTools;
};

#endif // MICROPHONE_H
