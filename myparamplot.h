#ifndef MYPARAMPLOT_H
#define MYPARAMPLOT_H

#include <QWidget>
#include <QGridLayout>
#include "signalinterface.h"
#include "qcustomplot.h"


//Cosine generator
class MyParamPlot : public SignalInterface
{
    Q_OBJECT
    QGridLayout* gridLayout;

    QSlider * amplitude,
            * phase,
            * freq;
    QLabel * A, * P, *F;
    QSpinBox *A_SPIN, * P_SPIN, * F_SPIN;

public:
    explicit MyParamPlot(int,QWidget *parent = nullptr);
    ~MyParamPlot();
    double getA();
    double getP();
    double getF();

signals:


    // SignalInterface interface
public:
    double getValue(double t);
};

#endif // MYPARAMPLOT_H
