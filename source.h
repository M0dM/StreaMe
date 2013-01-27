#ifndef SOURCE_H
#define SOURCE_H

#include <string>

using namespace std;

class Source
{
public:
    Source(std::string name ="null", string type="null");
    string getName();
    string getType();

private:
    string name;
    string type;
};

#endif // SOURCE_H
