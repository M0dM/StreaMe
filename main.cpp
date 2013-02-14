#include <QApplication>
#include "controller.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller *controller = new Controller();

    //Project *newProject = new Project(controller);
    //newProject->addUsedSource(new Source("Microphone (Realtek High Definition Audio)","audio"));
    //controller->setProject(newProject);

    controller->showMainWindow();

    controller->displayFreeSources();
    controller->displayUsedSources();

    return a.exec();

}
