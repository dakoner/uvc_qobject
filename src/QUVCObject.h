#ifndef _QUVCObject_H
#define _QUVCObject_H

#include <QtCore/qobject.h>
#include <QImage>
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

class UVCFrame
{
public:
    UVCFrame(uvc_frame *frame) : frame_(frame)
    {
    }
    ~UVCFrame()
    {
        uvc_free_frame(frame_);
    }
    uvc_frame *frame_;
    int width() { return frame_->width; }
    int height() { return frame_->width; }
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
    void stop_streaming(UVCDeviceHandle &device_handle);
    void free_frame();
    static void cb(uvc_frame_t *frame, void *user_data);

private:
    ::uvc_context_t *ctx_;

signals:
    void frameChanged(UVCFrame *uvc_frame);
};

#endif // !_QUVCObject_H