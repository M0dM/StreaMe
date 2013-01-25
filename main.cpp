#include <QApplication>

#include <iostream>

#include "controller.h"
#include "winavtools.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller controller;

    controller.ShowMainWindow();

    cout << "Video devices : " << endl;
    controller.displayVideoSources();
    cout << "Audio devices : " << endl;
    controller.displayAudioSources();

    return a.exec();
}
