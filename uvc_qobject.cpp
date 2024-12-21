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


void UVCQObject::close_device(uvc_device_handle *devh)
{
    uvc_close(devh);
}

UVCQObject::~UVCQObject()
{
    uvc_exit(ctx_);
    puts("UVC exited");
}
