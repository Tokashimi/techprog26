#include <QApplication>
#include "windowmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WindowManager manager;
    manager.showAuth();

    return a.exec();
}
