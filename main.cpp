#include <QApplication>
#include "controller.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("StreaMe");

    Controller *controller = new Controller();

    //Project *newProject = new Project(controller);
    //newProject->addUsedSource(new Source("Microphone (Realtek High Definition Audio)","audio"));
    //controller->setProject(newProject);

    controller->showMainWindow();

    controller->displayFreeSources();
    controller->displayUsedSources();

    controller->blockInterface();
    controller->blockStreamingStop();
    return a.exec();

}
