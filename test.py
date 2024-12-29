import time
import QUVCObject
import sys
from PyQt6.QtCore import QTimer
from PyQt6.QtGui import QPixmap, QImage
from PyQt6.QtWidgets import QApplication, QWidget, QLabel



class ImageViewer:
    def __init__(self):
        self.app = QApplication(sys.argv)
        self.window = QWidget()
        self.window.setWindowTitle("My PyQt6 App")

        self.label = QLabel(parent=self.window)
        self.label.show()
        self.label.resize(1280,720)
        self.window.show()
        self.q = QUVCObject.QUVCObject()
        self.d = QUVCObject.UVCDevice()
        self.q.find_device(self.d, 0x4b4, 0x477, None)
        self.dh = QUVCObject.UVCDeviceHandle()
        self.q.open_device(self.d, self.dh)
        format = 3
        self.q.frameChanged.connect(self.frameChanged)
        self.q.stream(self.dh, format, 1280, 720, 120)
    
    def closeEvent(self, event):
        print("window closed")
        self.q.stop_streaming(self.dh)
        self.q.close_device(self.dh)
        
    def frameChanged(self, image):
        pixmap = QPixmap.fromImage(image)
        self.label.setPixmap(pixmap)

if __name__ == "__main__":
    iv = ImageViewer()
    sys.exit(iv.app.exec())
