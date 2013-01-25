#ifndef STREAMTOOLS_H
#define STREAMTOOLS_H

#include "winavtools.h"


class StreamTools : public WinAvTools
{
public:
    StreamTools(Controller *controller);

private:
    Controller *controller;
};

#endif // STREAMTOOLS_H
