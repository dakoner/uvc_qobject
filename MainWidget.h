#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "uvc_qobject.h"

class QPushButton;
class QLabel;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwidget.cpp
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0); //Constructor
    ~MainWidget(); // Destructor
    void test(QPixmap);
    void init(void);
private:
   UVCQObject uvc_qobject_;
   QPushButton* button_;
   QLabel* label_;
   void cb(uvc_frame *);
   qint64 previousTime_;
};

#endif // MAINWIDGET_H