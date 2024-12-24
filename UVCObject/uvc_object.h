#ifndef _UVC_OBJECT_H
#define _UVC_OBJECT_H

#include "libuvc/libuvc.h"
#include <list>

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
    UVCFrame(uvc_frame *frame, void* user_ptr);
    uvc_frame *frame_;
    void *user_ptr_;
};

typedef void(UVCFrameCallback(UVCFrame *frame, void *user_data));

struct UVCCallbackAndData {
    UVCFrameCallback* cb;
    void *user_data;
};


class UVCObject
{
public:
    UVCObject();
    ~UVCObject();
    void find_device(UVCDevice *device, int vid, int pid, const char *sn);
    std::list<UVCDevice> find_devices();
    void open_device(UVCDevice &device, UVCDeviceHandle *devh);
    void close_device(UVCDeviceHandle &device_handle_);
    // std::list<FormatAndFrameDescriptors *> *get_formats(::uvc_device_handle *devh);
    void stream(UVCDeviceHandle device_handle, UVCFrameFormat frame_format, int width, int height, int fps, UVCFrameCallback *cb, void *user_data);
    static void cb(uvc_frame* frame, void* user_ptr);
    // UVCFrameCallback *cb_;
    // void *user_data_;
    UVCCallbackAndData *cb_and_data_;
private:
    ::uvc_context_t *ctx_;
};

#endif // !_UVC_OBJECT_H