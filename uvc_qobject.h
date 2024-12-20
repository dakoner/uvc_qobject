#ifndef _UVC_THREAD_H
#define _UVC_THREAD_H

#include <QtCore/qobject.h>
#include "libuvc/libuvc.h"

class UVCQObject : public QObject
{
    Q_OBJECT
public:
    UVCQObject();
    ~UVCQObject();

private:
    uvc_error init();
    uvc_context_t *ctx_;
    uvc_device_t *dev_;
    uvc_device_handle_t *devh_;
    uvc_stream_ctrl_t ctrl_;
};

#endif // !_UVC_THREAD_H