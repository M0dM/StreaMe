#include "source.h"
using namespace std;

Source::Source(string name, string type, string systemName)
{
    this->name = name;
    this->type = type;
    this->systemName = systemName;
}

string Source::getName(){
    return name;
}

string Source::getType(){
    return type;
}

string Source::getSystemName(){
    return systemName;
}
