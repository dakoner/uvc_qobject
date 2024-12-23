%Module UVCQObject 
%Import QtCore/QtCoremod.sip
class UVCQObject: QObject {

%TypeHeaderCode
#include "uvc_qobject.h"
%End
public:
    UVCQObject();

};