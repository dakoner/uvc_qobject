#include <QCoreApplication>
#include "libuvc/libuvc.h"
#include "uvc_qobject.h"
#include <stdio.h>
#include <unistd.h>

#include <QLabel>
int main(int argc, char *argv[])
{
    // Creates an instance of QApplication
    QCoreApplication a(argc, argv);
    UVCQObject uvc_qobject;

    // run the application and return execs() return value/code
    return a.exec();
}
