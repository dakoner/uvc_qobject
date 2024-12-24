#include <stdexcept>
#include <list>
#include "uvc_object.h"

UVCDevice::UVCDevice() : device_(NULL)
{
}

UVCDevice::UVCDevice(uvc_device_t *device) : device_(device)
{
}

UVCDeviceHandle::UVCDeviceHandle() : device_handle_(NULL)
{
}

UVCDeviceHandle::UVCDeviceHandle(uvc_device_handle_t *device_handle) : device_handle_(device_handle)
{
}

UVCFrame::UVCFrame(uvc_frame *frame, void* user_ptr): frame_(frame), user_ptr_(user_ptr) {
}

UVCObject::UVCObject()
{
    ::uvc_error res = ::uvc_init(&ctx_, NULL);

    if (res < 0)
    {
        ::uvc_perror(res, "::uvc_init");
        throw std::runtime_error("Failed to initialize");
    }
}

UVCObject::~UVCObject()
{
    ::uvc_exit(ctx_);
    puts("UVC exited");
}

void UVCObject::find_device(UVCDevice *device, int vid, int pid, const char *sn)
{
    uvc_device_t *d;
    ::uvc_error_t res = ::uvc_find_device(ctx_, &d, vid, pid, sn);
    if (res < 0)
    {
        ::uvc_perror(res, "::uvc_find_devices"); /* no devices found */
        throw std::runtime_error("Failed to find deevice");
    }
    else
    {
        device->device_ = d;
        puts("Devices found");
    }
}

std::list<::UVCDevice> UVCObject::find_devices()
{
    ::uvc_device_t **devs;

    ::uvc_error_t res = ::uvc_find_devices(ctx_, &devs, 0, 0, NULL);
    if (res < 0)
    {
        ::uvc_perror(res, "::uvc_find_devices"); /* no devices found */
    }
    else
    {
        puts("Devices found");
    }
    ::uvc_device_t *d = *devs;
    // select device by index
    int dev_idx = 0;
    std::list<UVCDevice> devices;

    while (devs[dev_idx] != NULL)
    {
        ::uvc_device_descriptor *desc;
        ::uvc_get_device_descriptor(devs[dev_idx], &desc);
        printf("Device: %u %u\n", ::uvc_get_bus_number(devs[dev_idx]), ::uvc_get_device_address(devs[dev_idx]));
        printf("Descriptor: %d %d %s %s %s\n", desc->idVendor, desc->idProduct, desc->serialNumber, desc->manufacturer, desc->product);
        UVCDevice d(devs[dev_idx]);
        devices.push_back(d);
        dev_idx++;
    }
    return devices;
}

void UVCObject::open_device(UVCDevice &device, UVCDeviceHandle *devh)
{
    /* Try to open the device: requires exclusive access */
    uvc_device_handle_t *device_handle;
    ::uvc_error_t res = ::uvc_open(device.device_, &device_handle);

    if (res < 0)
    {
        ::uvc_perror(res, "::uvc_open"); /* unable to open device */
        throw std::runtime_error("Failed to open device");
    }
    else
    {
        devh->device_handle_ = device_handle;
        puts("Device opened");
    }
}

// std::list<FormatAndFrameDescriptors *> *UVCObject::get_formats(::uvc_device_handle *devh)
// {
//     std::list<FormatAndFrameDescriptors *> *lf = new std::list<FormatAndFrameDescriptors *>;

//     const ::uvc_format_desc_t *format_desc = ::uvc_get_format_descs(devh);

//     while (format_desc != NULL)
//     {
//         FormatAndFrameDescriptors *f = new FormatAndFrameDescriptors;
//         f->devh = devh;
//         f->format_desc = format_desc;
//         const ::uvc_frame_desc_t *frame_desc = format_desc->frame_descs;
//         while (frame_desc != NULL)
//         {
//             f->frame_desc.push_back(frame_desc);
//             frame_desc = frame_desc->next;
//         }
//         lf->push_back(f);
//         format_desc = format_desc->next;
//     }
//     return lf;
// }

void UVCObject::close_device(UVCDeviceHandle &device_handle)
{
    ::uvc_close(device_handle.device_handle_);
    puts("Device closed");
}

void UVCObject::stream(UVCDeviceHandle device_handle, UVCFrameFormat frame_format, int width, int height, int fps, UVCFrameCallback* cb, void *user_data)
{
    ::uvc_stream_ctrl_t ctrl;

    ::uvc_error res = ::uvc_get_stream_ctrl_format_size(
        device_handle.device_handle_, &ctrl, /* result stored in ctrl */
        frame_format,
        width, height, fps /* width, height, fps */
    );

    if (res < 0)
    {
        ::uvc_perror(res, "::uvc_get_stream_ctrl_format_size"); /* device doesn't provide a matching stream */
        throw std::runtime_error("Failed to get matching format");
    }

    /* Print out the result */
    ::uvc_print_stream_ctrl(&ctrl, stderr);

    cb_and_data_ = new UVCCallbackAndData();
    cb_and_data_->cb = cb;
    cb_and_data_->user_data = user_data;
    res = ::uvc_start_streaming(device_handle.device_handle_, &ctrl, &UVCObject::cb, this, 0);

    if (res < 0)
    {

        ::uvc_perror(res, "start_streaming"); /* unable to start stream */
        throw std::runtime_error("Failed to start streaming");
    }
}

void UVCObject::cb(uvc_frame_t *frame, void *user_data) {
    UVCObject *this_ = (UVCObject *)user_data;
    UVCFrame *frame_ = new UVCFrame(frame, NULL);
    printf("Callback: %p %p\n", (void *)this_, (void *)frame_);
    
    this_->cb_and_data_->cb(frame_, this_->cb_and_data_->user_data);
}