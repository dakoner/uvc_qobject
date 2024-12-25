#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "QUVCObject.h"
#include <QElapsedTimer>
#include <QImage>

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
   QUVCObject QUVCObject_;
   QPushButton* button_;
   QLabel* label_;
   void cb(QImage *);
   QElapsedTimer fps_timer_;
   int size_;
   qint64 ns_average_;
};

#endif // MAINWIDGET_H