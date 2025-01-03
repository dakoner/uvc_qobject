%Module(name=QUVCObject, use_limited_api=True, keyword_arguments="Optional")
%Import QtCore/QtCoremod.sip
%Import QtGui/QtGuimod.sip
%DefaultSupertype PyQt6.sip.wrapper

int QUVCObject_VERSION;
const char *QUVCObject_VERSION_STR;

%ModuleCode
static int QUVCObject_VERSION = 0x060402;
static const char *QUVCObject_VERSION_STR = "6.4.2";
%End

typedef int UVCFrameFormat;

class UVCDevice
{

%TypeHeaderCode
#include "QUVCObject.h"
%End
public:
    UVCDevice();
};

class UVCDeviceHandle
{

%TypeHeaderCode
#include "QUVCObject.h"
%End
public:
    UVCDeviceHandle();
};
void my_free_frame(void *frame);

class QUVCObject: QObject {


%TypeHeaderCode
#include "QUVCObject.h"
%End

public:

    QUVCObject();
    void find_device(UVCDevice *device, int vid, int pid, const char *sn);
    void open_device(UVCDevice &device, UVCDeviceHandle *devh);
    void close_device(UVCDeviceHandle &device_handle_);
    void stream(UVCDeviceHandle &device_handle, UVCFrameFormat frame_format, int width, int height, int fps);

    unsigned char get_ae_mode(UVCDeviceHandle &device_handle,  unsigned char req_code);
    void set_ae_mode(UVCDeviceHandle &device_handle, unsigned char mode);

    unsigned int get_exposure_abs(UVCDeviceHandle &device_handle,  unsigned char req_code);
    void set_exposure_abs(UVCDeviceHandle &device_handle, unsigned int time);

    unsigned short get_white_balance_temperature(UVCDeviceHandle &device_handle,  unsigned char req_code);
    void set_white_balance_temperature(UVCDeviceHandle &device_handle, unsigned short mode);

    unsigned char get_white_balance_temperature_auto(UVCDeviceHandle &device_handle,  unsigned char req_code);
    void set_white_balance_temperature_auto(UVCDeviceHandle &device_handle, unsigned char mode);


signals:
    void frameChanged(QImage image);
    void yuvFrameChanged(void *frame_data, int width, int height, int data_bytes, int step);

};