#include <cmath>
#include <QtWidgets>
#include "MainWidget.h"
#include "uvc_qobject.h"

// Constructor for main widget
MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    button_ = new QPushButton(tr("Push Me!"));
    label_ = new QLabel();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(button_, 0, 0);
    mainLayout->addWidget(label_, 1, 0);
    setLayout(mainLayout);
    setWindowTitle(tr("Connecting buttons to processes.."));

    size_ = 0;
    ns_average_ = 0;
    init();
    fps_timer_.start();
    QObject::connect(&uvc_qobject_, &UVCQObject::frameChanged,
                     this, &MainWidget::cb);
}

void MainWidget::init()
{
    UVCDevice device;

    uvc_qobject_.find_device(
        &device,
        0x4b4, 0x477, 0); /* filter devices: vendor_id, product_id, "serial_num" */
    UVCDeviceHandle device_handle;
    uvc_qobject_.open_device(device, &device_handle);
    UVCFrameFormat format = UVC_FRAME_FORMAT_YUYV;
    uvc_qobject_.stream(device_handle, format, 1280, 720, 120);
    // uvc_object.close_device(device_handle);
}


double addToAverage(double average, int size, double value)
{
    double result = (size * average + value) / (size + 1);
    return result;
}

qint64 addToAverage_int64(qint64 average, int size, qint64 value)
{
    qint64 result = (size * average + value) / (size + 1);
    return result;
}

void MainWidget::cb(UVCFrame *frame)
{
    printf("Main widget got frame\n");
    // qint64 dt = fps_timer_.nsecsElapsed();
    // ns_average_ = addToAverage_int64(ns_average_, size_, dt);
    // if (size_ % 120 == 0)
    //     printf("fps: %lld\n", (1000*1000*1000/ns_average_));
    // fps_timer_.restart();
    // size_++;
    // QImage i((uchar *)frame->data, frame->width, frame->height, QImage::Format::Format_RGB888);
    // QPixmap p = QPixmap::fromImage(i);
    // label_->setPixmap(p);
    // uvc_free_frame(frame);
}

// Destructor
MainWidget::~MainWidget()
{
    delete button_;
    delete label_;
}