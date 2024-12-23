%Module(name=UVCQObject, use_limited_api=True, keyword_arguments="Optional")
%Import QtCore/QtCoremod.sip

%DefaultSupertype PyQt6.sip.simplewrapper


int UVCQOBJECT_VERSION;
const char *UVCQOBJECT_VERSION_STR;

%ModuleCode
static int UVCQOBJECT_VERSION = 0x060402;
static const char *UVCQOBJECT_VERSION_STR = "6.4.2";
struct uvc_device;
 //enum uvc_error;

%End


class UVCQObject: QObject {

%TypeHeaderCode
#include "uvc_qobject.h"
#include <QList>
%End

public:

    struct ::uvc_device;
    UVCQObject();
    QList<::uvc_device *> find_devices();
    //UVCQObject::uvc_error find_device(::uvc_device **device, int vid, int pid, const char *sn);

};