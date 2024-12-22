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

//     //     QList<uvc_device_t *> devices = uvc_qobject.find_devices();
//     //     uvc_device_handle *devh = NULL;
//     //     QMap<uvc_device_handle *, QList<FormatAndFrameDescriptors *> *> device_to_format_and_frame_descriptors;

//     //     foreach (auto device, devices)
//     //     {
//     //         if (uvc_qobject.open_device(device, &devh) == UVC_SUCCESS)
//     //         {
//     //             // uvc_print_diag(devh, stderr);
//     //             QList<FormatAndFrameDescriptors *> *lf = uvc_qobject.get_formats(devh);
//     //             device_to_format_and_frame_descriptors[devh] = lf;
//     //             uvc_qobject.close_device(devh);
//     //         }
//     //     }
//     //     //uvc_qobject.stream(devh, frame_format, 1280, 720, 120 )

//     QTimer::singleShot(1000, &app, &QCoreApplication::quit); // Quit after 1 second (1000 milliseconds)
//     return app.exec();
// }
