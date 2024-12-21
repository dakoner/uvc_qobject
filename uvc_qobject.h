#ifndef _UVC_THREAD_H
#define _UVC_THREAD_H

#include <QtCore/qobject.h>
#include <QtCore/qlist.h>
#include "libuvc/libuvc.h"

class UVCQObject : public QObject
{
    Q_OBJECT
public:
    UVCQObject();
    ~UVCQObject();
    QList<uvc_device_t *> find_devices();
    uvc_error open_device(uvc_device_t *device, uvc_device_handle_t **devh);
    void close_device(uvc_device_handle_t *devh);

private:
    uvc_context_t *ctx_;
    // uvc_device_t *dev_;
    // uvc_device_handle_t *devh_;
    // uvc_stream_ctrl_t ctrl_;
};

#endif // !_UVC_THREAD_H