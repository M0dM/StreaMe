#include "streamthread.h"

StreamThread::StreamThread(StreamTools *stools)
{
    this->stools = stools;
}

void StreamThread::run() //The function called for threading
{
    //stools->stream();
    exec();
}
