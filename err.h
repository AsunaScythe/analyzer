#ifndef ERR_H
#define ERR_H

#include "signalinterface.h"
#include <QWidget>
#include <QGridLayout>
#include "qcustomplot.h"
#include  "rangeslider.h"
#include "signal.h"

//Noise generator
class Err : public SignalInterface
{
    Q_OBJECT
    std::vector<double> sample;
    ctkRangeSlider * range;
    QSlider * amplitude;
    QGridLayout * grid;
    QSpinBox *ampl,* max, *min;
    QLabel * D, *A;
public:
    Err(int,QWidget *parent = nullptr);
    ~Err();
    // SignalInterface interface
public:
    double getValue(double t);
public slots:
    void resample();

};

#endif // ERR_H
