#include "uvc_qobject.h"

UVCQObject::UVCQObject()
{
    if (init() != UVC_SUCCESS)
    {
        throw std::runtime_error("Failed to initialize");
    }
    uvc_error res;
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
    dev_ = NULL;
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

void UVCQObject::open_device(uvc_device_t *device)
{
    uvc_device_handle *devh;
    /* Try to open the device: requires exclusive access */
    uvc_error_t res = uvc_open(device, &devh);

    if (res < 0)
    {
        uvc_perror(res, "uvc_open"); /* unable to open device */
    }
    else
    {
        puts("Device opened");
        // uvc_print_diag(devh, stderr);
        uvc_close(devh);
    }
}

UVCQObject::~UVCQObject()
{
    uvc_exit(ctx_);
    puts("UVC exited");
}

uvc_error UVCQObject::init()
{
    uvc_error res = uvc_init(&ctx_, NULL);

    if (res < 0)
    {
        uvc_perror(res, "uvc_init");
        return res;
    }

    puts("UVC initialized");
    return res;
}