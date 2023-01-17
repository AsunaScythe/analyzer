#include "myparamplot.h"

MyParamPlot::MyParamPlot(int sampling_rate,QWidget *parent)
    : SignalInterface{sampling_rate,parent}
{
    gridLayout = new QGridLayout(this);
    amplitude   = new QSlider();
    phase = new QSlider();
    freq = new QSlider();

    A = new QLabel("A");
    P = new QLabel("P");
    F = new QLabel("F");

    A_SPIN = new QSpinBox();
    P_SPIN = new QSpinBox();
    F_SPIN = new QSpinBox();

    A_SPIN->setMaximum(100);
    P_SPIN->setMaximum(360);
    F_SPIN->setMaximum(sampling_rate);

    freq->setFixedSize(10,100);
    phase->setFixedSize(10,100);
    amplitude->setFixedSize(10,100);

    freq->setRange(0,3200);
    phase->setRange(0,360);
    amplitude->setRange(0,100);

    gridLayout->addWidget(amplitude,1,0);
    gridLayout->addWidget(phase,1,1);
    gridLayout->addWidget(freq,1,2);

    gridLayout->addWidget(A,0,0);
    gridLayout->addWidget(P,0,1);
    gridLayout->addWidget(F,0,2);

    gridLayout->addWidget(A_SPIN,2,0);
    gridLayout->addWidget(P_SPIN,2,1);
    gridLayout->addWidget(F_SPIN,2,2);

    gridLayout->addWidget(Delete,1,3);

    connect(A_SPIN,SIGNAL(valueChanged(int)),amplitude,SLOT(setValue(int)));
    connect(amplitude,SIGNAL(valueChanged(int)),A_SPIN,SLOT(setValue(int)));

    connect(P_SPIN,SIGNAL(valueChanged(int)),phase,SLOT(setValue(int)));
    connect(phase,SIGNAL(valueChanged(int)),P_SPIN,SLOT(setValue(int)));

    connect(F_SPIN,SIGNAL(valueChanged(int)),freq,SLOT(setValue(int)));
    connect(freq,SIGNAL(valueChanged(int)),F_SPIN,SLOT(setValue(int)));

    this->setMaximumHeight(180);
}

MyParamPlot::~MyParamPlot()
{

    delete amplitude;;
    delete phase;
    delete freq;
    delete A;
    delete P;
    delete F;
    delete A_SPIN;
    delete P_SPIN;
    delete F_SPIN;
    delete gridLayout;

}

double MyParamPlot::getA()
{
    return amplitude->value();
}

double MyParamPlot::getP()
{
    return phase->value();
}

double MyParamPlot::getF()
{
    return freq->value();
}

double MyParamPlot::getValue(double t)
{
    return amplitude->value()*cos(M_PI*2*t*freq->value()/sampling_rate + M_PI*2*phase->value()/360);
}
