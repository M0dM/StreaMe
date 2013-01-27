#include "source.h"
using namespace std;

Source::Source(string name, string type)
{
    this->name = name;
    this->type = type;
}

string Source::getName(){
    return name;
}

string Source::getType(){
    return type;
}
