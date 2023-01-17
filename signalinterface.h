#ifndef SIGNALINTERFACE_H
#define SIGNALINTERFACE_H

#include <QWidget>
#include <QGridLayout>
#include "qcustomplot.h"


//InterFace for generator widgets
class SignalInterface : public QWidget
{
    Q_OBJECT
protected:
    QPushButton * Delete;
protected:
    int sampling_rate;
public:
    explicit SignalInterface(int,QWidget *parent = nullptr);
    virtual double getValue(double t) = 0;
    virtual ~SignalInterface();

signals:

};

#endif // SIGNALINTERFACE_H
