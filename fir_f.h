#ifndef FIR_F_H
#define FIR_F_H

#include "filtrinterface.h"
#include <x86intrin.h>
#include <immintrin.h>
#include "qcustomplot.h"
#include "time.h"

class FIR_F : public FiltrInterface
{
    Q_OBJECT
    int coef[32];
    __m128i coef_4[8];
    int buff[32];
    QGridLayout * grid;
    QLabel *type, *passband, *stopband;

public:
    FIR_F(QWidget *parent = nullptr);
    ~FIR_F();

    // FiltrInterface interface
public:
    double next(double);
};

#endif // FIR_F_H
