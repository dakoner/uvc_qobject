#ifndef _UVC_OBJECT_H
#define _UVC_OBJECT_H

#include "libuvc/libuvc.h"
#include <list>

typedef uvc_frame_format UVCFrameFormat;

class FormatAndFrameDescriptors
{
public:
    ::uvc_device_handle *devh;
    ::uvc_format_desc_t const *format_desc;
    std::list<::uvc_frame_desc_t const *> frame_desc;
};

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
    void stream(UVCDeviceHandle device_handle, UVCFrameFormat frame_format, int width, int height, int fps);
    static void cb(::uvc_frame *frame, void *ptr);

private:
    ::uvc_context_t *ctx_;
};

#endif // !_UVC_OBJECT_H