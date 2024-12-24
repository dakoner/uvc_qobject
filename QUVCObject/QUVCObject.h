#ifndef _QUVCObject_H
#define _QUVCObject_H

#include <QtCore/qobject.h>
#include <QtCore/qlist.h>
#include <QTimer>
#include "libuvc/libuvc.h"


typedef uvc_frame_format UVCFrameFormat;


class UVCDevice
{
public:
    uvc_device_t *device_;
    UVCDevice();
    UVCDevice(uvc_device_t *device);
};

class UVCDeviceHandle
{
public:
    uvc_device_handle_t *device_handle_;
    UVCDeviceHandle();
    UVCDeviceHandle(uvc_device_handle_t *device_handle);
};

class UVCFrame {
    public:
    UVCFrame(uvc_frame *frame);
    uvc_frame *frame_;
};

class QUVCObject : public QObject
{
    Q_OBJECT

public:
    QUVCObject();
    ~QUVCObject();
    void find_device(UVCDevice *device, int vid, int pid, const char *sn);
    void open_device(UVCDevice &device, UVCDeviceHandle *devh);
    void close_device(UVCDeviceHandle &device_handle_);
    void stream(UVCDeviceHandle &device_handle, UVCFrameFormat frame_format, int width, int height, int fps);
    static void cb(uvc_frame_t *frame, void *user_data);

private:
    ::uvc_context_t *ctx_;

signals:
    void frameChanged(UVCFrame *frame);
};

#endif // !_QUVCObject_H