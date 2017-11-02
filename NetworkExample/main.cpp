#include <QCoreApplication>
#include "networkmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    NetworkManager manager;

    manager.loadWebPage();

    return a.exec();
}
