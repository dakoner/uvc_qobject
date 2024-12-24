#include "uvc_object.h"

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <chrono>
#include <thread>

static void sigHandl(int sig)
{
    if (sig == 2)
    {
        _exit(1);
    }
}
int main(int argc, char *argv[])
{
    signal(SIGINT, sigHandl);

    UVCObject uvc_object;
    //std::list<UVCDevice> devices = uvc_object.find_devices();
    UVCDevice device;
    uvc_object.find_device(
        &device,
        0x4b4, 0x477, 0); /* filter devices: vendor_id, product_id, "serial_num" */
    UVCDeviceHandle device_handle;
    uvc_object.open_device(device, &device_handle);
    UVCFrameFormat format = UVC_FRAME_FORMAT_YUYV;
    uvc_object.stream(device_handle, format, 1280, 720, 120);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    uvc_object.close_device(device_handle);
}