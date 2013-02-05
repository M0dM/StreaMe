#ifndef STREAMTHREAD_H
#define STREAMTHREAD_H

#include "QThread"
#include "streamtools.h"

class StreamThread : public QThread
{
public:
    StreamThread(StreamTools *stools);
    void run();
private:
    StreamTools *stools;

    // from Qthread :
signals:
    //void streamFinished();

public slots:
    //void setData(int someData);

};

#endif // STREAMTHREAD_H
