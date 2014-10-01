#include "mainwindow.h"
#include "setupwizard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("synrand");
    a.setOrganizationDomain("synrand.de");
    a.setApplicationName("edim");
    a.setApplicationDisplayName(a.applicationName());

    // TODO: Check if settings are empty. If so, use wizard
    SetupWizard setupWizard;
    setupWizard.showNormal();

    MainWindow w;
    w.show();

    return a.exec();
}
