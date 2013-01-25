#ifndef SOURCE_H
#define SOURCE_H

#include <string>

using namespace std;

class WinAvTools;

class Source
{
public:
    Source(WinAvTools *avTools, std::string name ="null", string type="null");
    string getName();
    string getType();

private:
    WinAvTools *avTools;
    string name;
    string type;
};

#endif // SOURCE_H
