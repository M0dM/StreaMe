#ifndef SOURCE_H
#define SOURCE_H

#include <string>

class Source
{
public:
    Source(std::string name ="null", std::string type="null", std::string systemName="null");
    std::string getName();
    std::string getType();
    std::string getSystemName();

private:
    std::string name;
    std::string type;
    std::string systemName;
};

#endif // SOURCE_H
