%Module(name=UVCQObject, use_limited_api=True, keyword_arguments="Optional")
%Import QtCore/QtCoremod.sip

%DefaultSupertype PyQt6.sip.simplewrapper


int UVCQOBJECT_VERSION;
const char *UVCQOBJECT_VERSION_STR;

%ModuleCode
static int UVCQOBJECT_VERSION = 0x060402;
static const char *UVCQOBJECT_VERSION_STR = "6.4.2";
%End


class UVCQObject: QObject {

%TypeHeaderCode
#include "uvc_qobject.h"
%End
public:
    UVCQObject();

};