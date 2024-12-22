#include <cmath>
#include <QtWidgets>
#include "MainWidget.h"
#include "uvc_qobject.h"


// Constructor for main widget
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
   button_ = new QPushButton(tr("Push Me!"));
   label_ = new QLabel();

   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(button_,0,0);
   mainLayout->addWidget(label_,1,0);
   setLayout(mainLayout);
   setWindowTitle(tr("Connecting buttons to processes.."));

   size_ = 0;
   average_ = 0;
   previousTime_ = QDateTime::currentDateTime().toMSecsSinceEpoch();

   init();
   QObject::connect(&uvc_qobject_, &UVCQObject::frameChanged,
                    this, &MainWidget::cb);
}

void MainWidget::init() {
   uvc_device_t *dev;

    uvc_error res = uvc_qobject_.find_device(
        &dev,
        0x4b4, 0x477, 0); /* filter devices: vendor_id, product_id, "serial_num" */
    uvc_device_handle *devh = NULL;
    if (uvc_qobject_.open_device(dev, &devh) == UVC_SUCCESS)
    {
        uvc_frame_format frame_format = UVC_FRAME_FORMAT_YUYV;
        uvc_qobject_.stream(devh, frame_format, 1280, 720, 120);
    }
}

double addToAverage(double average, int size, double value)
{
    printf("average=%5.2f size=%d value=%5.2f", average, size, value);
    double result = (size * average + value) / (size + 1);
    printf(" result=%5.2f\n", result);
    return result;
}

void MainWidget::cb(uvc_frame *frame) {
   qint64 currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
   qint64 delta = currentTime - previousTime_;
   double fps = 1000./delta;
   if (!std::isinf(fps)) {
    average_ = addToAverage(average_, size_, fps);
    size_++;
    printf("fps: %5.2f average fps: %5.2f\n", fps, average_);
   }
   QImage i((uchar *)frame->data, frame->width, frame->height, QImage::Format::Format_RGB888);
   QPixmap p = QPixmap::fromImage(i);
   label_->setPixmap(p);
   uvc_free_frame(frame);
   previousTime_ = currentTime;
}

// Destructor
MainWidget::~MainWidget()
{
   delete button_;
   delete label_;
}