#include "uvc_qobject.h"

UVCQObject::UVCQObject()
{
    uvc_error res = uvc_init(&ctx_, NULL);

    if (res < 0)
    {
        uvc_perror(res, "uvc_init");
        throw std::runtime_error("Failed to initialize");
    }
}

UVCQObject::~UVCQObject()
{
    uvc_exit(ctx_);
    puts("UVC exited");
}

uvc_error UVCQObject::find_device(uvc_device_t **device, int vid, int pid, const char *sn)
{
    uvc_error_t res = uvc_find_device(ctx_, device, vid, pid, sn);
    if (res < 0)
    {
        uvc_perror(res, "uvc_find_devices"); /* no devices found */
        return res;
    }
    else
    {
        puts("Devices found");
    }
    return UVC_SUCCESS;
}

QList<uvc_device_t *> UVCQObject::find_devices()
{
    uvc_device_t **devs;

    uvc_error_t res = uvc_find_devices(ctx_, &devs, 0, 0, NULL);
    if (res < 0)
    {
        uvc_perror(res, "uvc_find_devices"); /* no devices found */
    }
    else
    {
        puts("Devices found");
    }
    uvc_device_t *d = *devs;
    // select device by index
    int dev_idx = 0;
    QList<uvc_device_t *> devices;

    while (devs[dev_idx] != NULL)
    {
        uvc_device_descriptor *desc;
        uvc_get_device_descriptor(devs[dev_idx], &desc);
        printf("Device: %u %u\n", uvc_get_bus_number(devs[dev_idx]), uvc_get_device_address(devs[dev_idx]));
        printf("Descriptor: %d %d %s %s %s\n", desc->idVendor, desc->idProduct, desc->serialNumber, desc->manufacturer, desc->product);
        devices.push_back(devs[dev_idx]);
        dev_idx++;
    }
    return devices;
}

uvc_error_t UVCQObject::open_device(uvc_device_t *device, uvc_device_handle **devh)
{
    /* Try to open the device: requires exclusive access */
    uvc_error_t res = uvc_open(device, devh);

    if (res < 0)
    {
        uvc_perror(res, "uvc_open"); /* unable to open device */
        return res;
    }
    else
    {
        puts("Device opened");
    }
    return UVC_SUCCESS;
}

QList<FormatAndFrameDescriptors *> *UVCQObject::get_formats(uvc_device_handle *devh)
{
    QList<FormatAndFrameDescriptors *> *lf = new QList<FormatAndFrameDescriptors *>;

    const uvc_format_desc_t *format_desc = uvc_get_format_descs(devh);

    while (format_desc != NULL)
    {
        FormatAndFrameDescriptors *f = new FormatAndFrameDescriptors;
        f->devh = devh;
        f->format_desc = format_desc;
        const uvc_frame_desc_t *frame_desc = format_desc->frame_descs;
        while (frame_desc != NULL)
        {
            f->frame_desc.push_back(frame_desc);
            frame_desc = frame_desc->next;
        }
        lf->push_back(f);
        format_desc = format_desc->next;
    }
    return lf;
}

void UVCQObject::close_device(uvc_device_handle *devh)
{
    uvc_close(devh);
}

void UVCQObject::cb(uvc_frame *frame, void *ptr)
{
    uvc_frame_t *bgr;
    uvc_error_t ret;

    printf("callback! frame_format = %d, width = %d, height = %d, length = %lu, ptr = %p\n",
           frame->frame_format, frame->width, frame->height, frame->data_bytes, ptr);
    if (frame->frame_format == UVC_COLOR_FORMAT_YUYV)
    {
        if (frame->width * frame->height * 2 != frame->data_bytes)
        {
            printf("Invalid frame\n");
            return;
        }
        bgr = uvc_allocate_frame(frame->width * frame->height * 3);
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
        ((UVCQObject *)ptr)->updateFrame(bgr);
    }
}

void UVCQObject::updateFrame(uvc_frame *frame)
{
    printf("updateFrame! frame_format = %d, width = %d, height = %d, length = %lu\n",
           frame->frame_format, frame->width, frame->height, frame->data_bytes);
}

uvc_error UVCQObject::stream(uvc_device_handle *devh, uvc_frame_format frame_format, int width, int height, int fps)
{
    uvc_stream_ctrl_t ctrl;

    uvc_error res = uvc_get_stream_ctrl_format_size(
        devh, &ctrl, /* result stored in ctrl */
        frame_format,
        width, height, fps /* width, height, fps */
    );

    /* Print out the result */
    uvc_print_stream_ctrl(&ctrl, stderr);

    if (res < 0)
    {
        uvc_perror(res, "get_mode"); /* device doesn't provide a matching stream */
    }

    else
    {
        /* Start the video stream. The library will call user function cb:
         *   cb(frame, (void *) 12345)
         */
        res = uvc_start_streaming(devh, &ctrl, &UVCQObject::cb, this, 0);

        if (res < 0)
        {
            uvc_perror(res, "start_streaming"); /* unable to start stream */
            return res;
        }
    }
    return UVC_SUCCESS;
}
