#include "libuvc/libuvc.h"
#include "uvc_qobject.h"

#include <QCoreApplication>
#include <QTimer>

#include <QApplication>
#include "MainWidget.h"
#include "libuvc/libuvc.h"
#include "uvc_qobject.h"
#include <stdio.h>
#include <unistd.h>

#include <signal.h>
#include <QLabel>

static void sigHandl(int sig)
{
    if (sig == 2)
    {
        QCoreApplication::quit();
    }
}
int main(int argc, char *argv[])
{
    signal(SIGINT, sigHandl);

    QApplication a(argc, argv);
    MainWidget w;
    w.show(); 
    return a.exec();
}
