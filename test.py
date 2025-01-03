import ffmpeg
import time
import QUVCObject
import sys
from PyQt6.QtCore import QTimer
from PyQt6.QtGui import QPixmap, QImage
from PyQt6.QtWidgets import QApplication, QWidget, QLabel, QVBoxLayout



class ImageViewer:
    def __init__(self):
        self.app = QApplication(sys.argv)
        self.window = QWidget()
        self.dock_layout = QVBoxLayout()
        self.dock_layout.setSizeConstraint(QVBoxLayout.SizeConstraint.SetMinimumSize)

        self.label = QLabel()#parent=self.window)
        self.window.setLayout(self.dock_layout)

        self.label.show()
        #self.label.resize(1280,720)
        self.dock_layout.addWidget(self.label)
        self.window.show()
        self.label.setScaledContents(True)
        self.q = QUVCObject.QUVCObject()
        self.d = QUVCObject.UVCDevice()
        self.q.find_device(self.d, 0x4b4, 0x477, None)
        self.dh = QUVCObject.UVCDeviceHandle()
        self.q.open_device(self.d, self.dh)

        self.q.set_ae_mode(self.dh, bytearray.fromhex('00'))
        self.q.set_exposure_abs(self.dh, 5)
        self.q.set_white_balance_temperature_auto(self.dh, bytearray.fromhex('00'))
        self.q.set_white_balance_temperature(self.dh, 5000)
                                                  
        format = 3
        #self.q.frameChanged.connect(self.frameChanged)
        fname = "test.mkv"
        self.process = (
            ffmpeg.input(
                "pipe:",
                format="rawvideo",
                pix_fmt="yuyv422",
                s="{}x{}".format(1280, 720),
            )
            .output(
                fname, pix_fmt="yuv420p", vcodec="libx264"
            )  
            .overwrite_output()
            .run_async(pipe_stdin=True)
        )
        self.q.yuvFrameChanged.connect(self.yuv_callback)
        self.q.stream(self.dh, format, 1280, 720, 120)

    def yuv_callback(self, frame, width, height, data_bytes):
        frame.setsize(data_bytes)
        print(width*height*2, data_bytes)
        s = frame.asstring()
        self.process.stdin.write(s)
        #QUVCObject.my_free_frame(frame)
        
    def __del__(self):
        self.process.stdin.close()

    def closeEvent(self, event):
        print("window closed")
        self.q.stop_streaming(self.dh)
        self.q.close_device(self.dh)
        self.process.stdin.close()
        
    def frameChanged(self, image):
        pixmap = QPixmap.fromImage(image)
        self.label.setPixmap(pixmap)
        #b = image.bits()
        #b.setsize(image.sizeInBytes())
        #self.process.stdin.write(b)

if __name__ == "__main__":
    iv = ImageViewer()
    sys.exit(iv.app.exec())
