#ifndef STREAMTOOLS_H
#define STREAMTOOLS_H

#include "windows.h"
#include "winavtools.h"


class StreamTools : public WinAvTools
{
public:
    StreamTools(Controller *controller);
    void captureVideoFile(int time) const; // time = seconds

private:
    Controller *controller;
};

#endif // STREAMTOOLS_H
