#include "libuvc/libuvc.h"
#include "uvc_qobject.h"

#include <QCoreApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    UVCQObject uvc_qobject;
    QList<uvc_device_t *> devices = uvc_qobject.find_devices();
    qDebug() << devices;
    uvc_device_handle *devh = NULL;
    foreach (auto device,  devices) {
        if (uvc_qobject.open_device(device, &devh) == UVC_SUCCESS) {
            uvc_print_diag(devh, stderr);
            uvc_qobject.close_device(devh);
        }
    }
    QTimer::singleShot(1000, &app, &QCoreApplication::quit); // Quit after 1 second (1000 milliseconds)
    return app.exec();
}
