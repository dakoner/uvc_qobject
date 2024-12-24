#ifndef _UVC_QOBJECT_H
#define _UVC_QOBJECT_H

#include <QtCore/qobject.h>
#include <QtCore/qlist.h>
#include <QTimer>
#include "../UVCObject/uvc_object.h"

class QUVCDevice
{
public:
    QUVCDevice();
    QUVCDevice(UVCDevice *device);
    UVCDevice *device_;
};

class QUVCDeviceHandle
{
public:
    QUVCDeviceHandle();
    QUVCDeviceHandle(UVCDeviceHandle *device_handle);
    UVCDeviceHandle *device_handle_;
};

typedef UVCFrameFormat QUVCFrameFormat;

class QUVCFrame
{
public:
    QUVCFrame(UVCFrame *frame);
    UVCFrame *frame_;
};

typedef void(QUVCFrameCallback(UVCFrame *frame, void *user_data));

struct QUVCCallbackAndData
{
    QUVCFrameCallback *cb;
    void *user_data;
};

class UVCQObject : public QObject
{
    Q_OBJECT

public:
    UVCQObject();
    ~UVCQObject();
    void find_device(QUVCDevice *device, int vid, int pid, const char *sn);
    QList<QUVCDevice> find_devices();
    void open_device(QUVCDevice &device, QUVCDeviceHandle *devh);
    void close_device(QUVCDeviceHandle &device_handle_);
    // std::list<FormatAndFrameDescriptors *> *get_formats(::uvc_device_handle *devh);
    void stream(QUVCDeviceHandle &device_handle, QUVCFrameFormat frame_format, int width, int height, int fps);
    static void cb(UVCFrame *frame, void *user_data);

private:
    UVCObject *uvc_object_;
    QUVCCallbackAndData *cb_and_data_;

signals:
    void frameChanged(QUVCFrame *frame);
};

#endif // !_UVC_QOBJECT_H