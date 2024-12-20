#include "uvc_qobject.h"

UVCQObject::UVCQObject()
{
    if (init() != UVC_SUCCESS)
    {
        throw("Failed to initialize");
    }
    uvc_error res;

    /* Locates the first attached UVC device, stores in dev */
    res = uvc_find_device(
        ctx_, &dev_,
        0, 0, NULL); /* filter devices: vendor_id, product_id, "serial_num" */

    if (res < 0)
    {
        uvc_perror(res, "uvc_find_device"); /* no devices found */
    }
    else
    {
        puts("Device found");
    }
    uvc_device_t **devs;

    res = uvc_find_devices(ctx_, &devs, 0, 0, NULL);
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
    while (devs[dev_idx] != NULL)
    {
        uvc_device_descriptor *desc;
        uvc_get_device_descriptor(devs[dev_idx], &desc);
        printf("Device: %u %u\n", uvc_get_bus_number(devs[dev_idx]), uvc_get_device_address(devs[dev_idx]));
        printf("Descriptor: %d %d %s %s %s\n", desc->idVendor, desc->idProduct, desc->serialNumber, desc->manufacturer, desc->product);
        
        uvc_device_handle *devh;
        /* Try to open the device: requires exclusive access */
        res = uvc_open(devs[dev_idx], &devh);

        if (res < 0)
        {
            uvc_perror(res, "uvc_open"); /* unable to open device */
        }
        else
        {
            puts("Device opened");
            //uvc_print_diag(devh, stderr);
            uvc_close(devh);
        }
        dev_idx++;
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