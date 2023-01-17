#include "iir_f.h"

IIR_F::IIR_F(QWidget *parent):FiltrInterface{parent},
    //IIR coefficient
    b1{0.1801332242321223,0.5455000565852970,0.8000798681750893},
       b2{0.3274217481957748,0.6104470980353654,0.6391838327981532},
       b3{0.1801332242321223,0.5455000565852970,0.8000798681750893},
       a1{0.5409884119872004,-.07985315957921558,-.3898890039417893},
       a2{ -.2286813892424107,-.6672555331606418,-.9201516627799719},
       z1{0,0,0},
       z2{0,0,0},
       out{0,0,0,0}
{
    grid = new QGridLayout(this);
    type = new QLabel("IIR");
    stopband = new QLabel("Stopband\n1000-1600 Hz");
    passband = new QLabel("Passband\n0-900 Hz");

    type->setAlignment(Qt::AlignCenter);
    stopband->setAlignment(Qt::AlignCenter);
    passband->setAlignment(Qt::AlignCenter);

    grid->addWidget(type);
    grid->addWidget(passband);
    grid->addWidget(stopband);

    grid->setAlignment(Qt::AlignCenter);


}

IIR_F::~IIR_F()
{
    delete type;
    delete passband;
    delete stopband;
    delete grid;
}

double IIR_F::next(double input)
{
    out[0] = input;
    for(int i = 0;i < 3;i++){
        out[i+1] = out[i]*b1[i] + z1[i];
        z1[i] = out[i+1]*a1[i] + out[i]*b2[i] + z2[i];
        z2[i] = out[i]*b3[i] + out[i+1]*a2[i];
    }
    return out[3];
}
