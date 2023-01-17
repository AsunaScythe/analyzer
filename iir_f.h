#ifndef IIR_F_H
#define IIR_F_H

#include "filtrinterface.h"
#include "qcustomplot.h"

class IIR_F : public FiltrInterface
{
    Q_OBJECT
    double b1[3],
           b2[3],
           b3[3],
           a1[3],
           a2[3],
           z1[3],
           z2[3],
           out[4];
    QGridLayout * grid;
    QLabel * type, *passband, *stopband;
public:
    IIR_F(QWidget *parent = nullptr);
    ~IIR_F();
    // FiltrInterface interface
public:
    double next(double);
};

#endif // IIR_F_H
