#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("synrand");
    a.setOrganizationDomain("synrand.de");
    a.setApplicationName("edim");
    a.setApplicationDisplayName(a.applicationName());

    MainWindow w;
    w.show();

    return a.exec();
}
