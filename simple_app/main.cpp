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

void cb(UVCFrame *f, void *ptr)
{
    uvc_frame_t *frame = f->frame_;
    printf("Frame!\n");
    ::uvc_frame_t *bgr; 
    ::uvc_error_t ret;
    if (frame->frame_format == UVC_COLOR_FORMAT_YUYV)
    {
        if (frame->width * frame->height * 2 != frame->data_bytes)
        {
            printf("Invalid frame\n");
            return;
        }
        bgr = ::uvc_allocate_frame(frame->width * frame->height * 3);
        if (!bgr)
        {
            printf("unable to allocate bgr frame!\n");
            return;
        }
        ret = ::uvc_any2bgr(frame, bgr);
        if (ret)
        {
            ::uvc_perror(ret, "::uvc_any2bgr");
            ::uvc_free_frame(bgr);
            return;
        }
        ::uvc_free_frame(bgr);
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
    uvc_object.stream(device_handle, format, 1280, 720, 120, &cb, NULL);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    uvc_object.close_device(device_handle);
}