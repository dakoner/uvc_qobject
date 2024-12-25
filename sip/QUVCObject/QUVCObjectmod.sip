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
signals:
    void frameChanged(QImage image);
};