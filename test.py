import time
import QUVCObject
import sys
from PyQt6.QtCore import QCoreApplication, QTimer
def frameChanged(*args):
    print("frame", *args)



if __name__ == "__main__":
    app = QCoreApplication(sys.argv)

    print("Hello from QCoreApplication!")
    q = QUVCObject.QUVCObject()
    d = QUVCObject.UVCDevice()
    print(q.find_device(d, 0x4b4, 0x477, None))
    dh = QUVCObject.UVCDeviceHandle()
    q.open_device(d, dh)
    format = 3
    q.frameChanged.connect(frameChanged)
    q.stream(dh, format, 1280, 720, 120)
    t = QTimer()
    t.singleShot(10000, app.quit)
    sys.exit(app.exec())