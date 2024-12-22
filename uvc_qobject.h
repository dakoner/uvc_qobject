#ifndef _UVC_THREAD_H
#define _UVC_THREAD_H

#include <QtCore/qobject.h>
#include <QtCore/qlist.h>
#include "libuvc/libuvc.h"

class FormatAndFrameDescriptors
{
    public:
    uvc_device_handle *devh;
    uvc_format_desc_t const *format_desc;
    QList<uvc_frame_desc_t const *> frame_desc;
};

class UVCQObject : public QObject
{
    Q_OBJECT
public:
    UVCQObject();
    ~UVCQObject();
    QList<uvc_device_t *> find_devices();
    uvc_error open_device(uvc_device_t *device, uvc_device_handle_t **devh);
    void close_device(uvc_device_handle_t *devh);
    QList<FormatAndFrameDescriptors *> *get_formats(uvc_device_handle *devh);

private:
    uvc_context_t *ctx_;
};

#endif // !_UVC_THREAD_H