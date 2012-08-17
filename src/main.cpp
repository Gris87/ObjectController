#include <QtGui/QApplication>
#include "src/other/global.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Resources);

    QApplication a(argc, argv);

    a.setApplicationName("ObjectController");
    a.setApplicationVersion(applicationVersion);

    a.setOrganizationName("None");
    a.setOrganizationDomain("None");

    allowDumpCrashes();



    dir=QApplication::applicationDirPath()+"/";



    mainWindow=new MainWindow;
    mainWindow->show();

    int res=a.exec();

    delete mainWindow;



    return res;
}
