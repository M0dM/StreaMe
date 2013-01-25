#include "source.h"
using namespace std;

Source::Source(WinAvTools *avTools, string name, string type)
{
    this->avTools = avTools;
    this->name = name;
    this->type = type;
}

string Source::getName(){
    return name;
}

string Source::getType(){
    return type;
}
