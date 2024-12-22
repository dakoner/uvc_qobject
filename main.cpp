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

#include <QLabel>
int main(int argc, char *argv[])
{
    // Creates an instance of QApplication
    QApplication a(argc, argv);

    // This is our MainWidget class containing our GUI and functionality
    MainWidget w;
    w.show(); // Show main window
  
    // run the application and return execs() return value/code
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
