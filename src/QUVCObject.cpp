#include "QUVCObject.h"
#include <QPixmap>

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

QUVCObject::QUVCObject()
{
    ::uvc_error res = ::uvc_init(&ctx_, NULL);

    if (res < 0)
    {
        ::uvc_perror(res, "::uvc_init");
        throw std::runtime_error("Failed to initialize");
    }
}

QUVCObject::~QUVCObject()
{
    ::uvc_exit(ctx_);
    puts("UVC exited");
}

void QUVCObject::find_device(UVCDevice *device, int vid, int pid, const char *sn)
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

void QUVCObject::open_device(UVCDevice &device, UVCDeviceHandle *devh)
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

void QUVCObject::stream(UVCDeviceHandle &device_handle, UVCFrameFormat frame_format, int width, int height, int fps)
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

    res = ::uvc_start_streaming(device_handle.device_handle_, &ctrl, &QUVCObject::cb, this, 0);

    if (res < 0)
    {

        ::uvc_perror(res, "start_streaming"); /* unable to start stream */
        throw std::runtime_error("Failed to start streaming");
    }
}

void QUVCObject::stop_streaming(UVCDeviceHandle &device_handle)
{
    uvc_stop_streaming(device_handle.device_handle_);
}

void QUVCObject::close_device(UVCDeviceHandle &device_handle)
{
    ::uvc_close(device_handle.device_handle_);
    puts("Device closed");
}

void uvc_free_frame_void(void *bgr)
{
    uvc_free_frame((uvc_frame_t *)bgr);
}

void QUVCObject::cb(uvc_frame_t *frame, void *user_data)
{
    uvc_error ret;
    // signal data
    uvc_frame_t *bgr;
    bgr = uvc_allocate_frame(frame->data_bytes);
    if (!bgr)
    {
        printf("unable to allocate bgr frame!\n");
        return;
    }
    ret = uvc_any2bgr(frame, bgr);
    if (ret)
    {
        uvc_perror(ret, "uvc_any2bgr");
        uvc_free_frame(bgr);
        return;
    }
    QUVCObject *this_ = (QUVCObject *)user_data;
    QImage image((unsigned char *)bgr->data, frame->width, frame->height, QImage::Format::Format_BGR888, uvc_free_frame_void, (void *)bgr);
    emit this_->frameChanged(image);
}

uint8_t QUVCObject::get_ae_mode(UVCDeviceHandle &device_handle, unsigned char req_code)
{
    uint8_t mode;
    uvc_error_t ret = uvc_get_ae_mode(device_handle.device_handle_, &mode, (enum uvc_req_code)req_code);
    if (ret)
    {
        uvc_perror(ret, "uvc_get_ae_mode");
    }
    return mode;
}

void QUVCObject::set_ae_mode(UVCDeviceHandle &device_handle, uint8_t mode)
{
    uvc_error_t ret = uvc_set_ae_mode(device_handle.device_handle_, mode);
    if (ret)
    {
        uvc_perror(ret, "uvc_set_ae_mode");
    }
}


uint32_t QUVCObject::get_exposure_abs(UVCDeviceHandle &device_handle, unsigned char req_code)
{
    uint32_t time;
    uvc_error_t ret = uvc_get_exposure_abs(device_handle.device_handle_, &time, (enum uvc_req_code)req_code);
    if (ret)
    {
        uvc_perror(ret, "uvc_get_exposure_abs");
    }
    return time;
}

void QUVCObject::set_exposure_abs(UVCDeviceHandle &device_handle, uint32_t time)
{
    uvc_error_t ret = uvc_set_exposure_abs(device_handle.device_handle_, time);
    if (ret)
    {
        uvc_perror(ret, "uvc_set_ae_mode");
    }
}
