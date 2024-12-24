#include "uvc_qobject.h"


QUVCDevice::QUVCDevice(UVCDevice *device): device_(device) {

}


QUVCDevice::QUVCDevice(): device_(new UVCDevice) {

}


QUVCDeviceHandle::QUVCDeviceHandle(UVCDeviceHandle *device_handle): device_handle_(device_handle) {

}


QUVCDeviceHandle::QUVCDeviceHandle(): device_handle_(new UVCDeviceHandle) {

}

QUVCFrame::QUVCFrame(UVCFrame *frame): frame_(frame) {

}


UVCQObject::UVCQObject(): uvc_object_(new UVCObject)
{
}

UVCQObject::~UVCQObject()
{
    delete(uvc_object_);
}

void UVCQObject::find_device(QUVCDevice *device, int vid, int pid, const char *sn)
{
    UVCDevice *d = new UVCDevice;
    uvc_object_->find_device(d, vid, pid, sn);
    device->device_ = d;
}

QList<QUVCDevice> UVCQObject::find_devices()
{
    // std::list<UVCDevice> devices = uvc_object_->find_devices();
    QList<QUVCDevice> qdevices;
    // for( auto di = devices.begin(); di != devices.end(); di++) {
    //     qdevices.push_back(QUVCDevice(di->device_))
    // }
    // (devices.begin(), devices.end());

    return qdevices;
}

void UVCQObject::open_device(QUVCDevice &device, QUVCDeviceHandle *device_handle)
{
    UVCDeviceHandle *dh = new UVCDeviceHandle();
    uvc_object_->open_device(*device.device_, dh);
    device_handle->device_handle_ = dh;
}

void UVCQObject::close_device(QUVCDeviceHandle &device_handle)
{
    uvc_object_->close_device(*device_handle.device_handle_);
}

void UVCQObject::stream(QUVCDeviceHandle &device_handle, QUVCFrameFormat frame_format, int width, int height, int fps)
{
    uvc_object_->stream(*device_handle.device_handle_, frame_format, width, height, fps, &UVCQObject::cb, this);
}

void UVCQObject::cb(UVCFrame *frame, void* user_data) {
    printf("Got UVCQObject cb\n");
    // signal data
    QUVCFrame *qf = new QUVCFrame(frame);

    UVCQObject *this_ = (UVCQObject*)user_data;
    emit this_->frameChanged(qf);
}
