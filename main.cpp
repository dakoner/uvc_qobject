#include "libuvc/libuvc.h"
#include "uvc_qobject.h"

#include <QCoreApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    UVCQObject uvc_qobject;
    uvc_device_t *dev;

    uvc_error res = uvc_qobject.find_device(
        &dev,
        0x4b4, 0x477, 0); /* filter devices: vendor_id, product_id, "serial_num" */
    uvc_device_handle *devh = NULL;
    if (uvc_qobject.open_device(dev, &devh) == UVC_SUCCESS)
    {
        uvc_frame_format frame_format = UVC_FRAME_FORMAT_YUYV;
        uvc_qobject.stream(devh, frame_format, 1280, 720, 120);
    }
    //    uvc_qobject.close_device(devh);

    //     QList<uvc_device_t *> devices = uvc_qobject.find_devices();
    //     uvc_device_handle *devh = NULL;
    //     QMap<uvc_device_handle *, QList<FormatAndFrameDescriptors *> *> device_to_format_and_frame_descriptors;

    //     foreach (auto device, devices)
    //     {
    //         if (uvc_qobject.open_device(device, &devh) == UVC_SUCCESS)
    //         {
    //             // uvc_print_diag(devh, stderr);
    //             QList<FormatAndFrameDescriptors *> *lf = uvc_qobject.get_formats(devh);
    //             device_to_format_and_frame_descriptors[devh] = lf;
    //             uvc_qobject.close_device(devh);
    //         }
    //     }
    //     //uvc_qobject.stream(devh, frame_format, 1280, 720, 120 )

    QTimer::singleShot(1000, &app, &QCoreApplication::quit); // Quit after 1 second (1000 milliseconds)
    return app.exec();
}
