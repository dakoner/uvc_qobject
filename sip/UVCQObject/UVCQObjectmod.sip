%Module(name=QUVCObject, use_limited_api=True, keyword_arguments="Optional")
%Import QtCore/QtCoremod.sip

%DefaultSupertype PyQt6.sip.simplewrapper


int QUVCObject_VERSION;
const char *QUVCObject_VERSION_STR;

%ModuleCode
static int QUVCObject_VERSION = 0x060402;
static const char *QUVCObject_VERSION_STR = "6.4.2";
struct uvc_device;
 //enum uvc_error;

%End


class QUVCObject: QObject {

%TypeHeaderCode
#include "QUVCObject.h"
#include <QList>
%End

public:

    struct ::uvc_device;
    QUVCObject();
    QList<::uvc_device *> find_devices();
    //QUVCObject::uvc_error find_device(::uvc_device **device, int vid, int pid, const char *sn);

};