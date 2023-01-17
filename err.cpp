#include "err.h"

Err::Err(int sampling_rate,QWidget *parent): SignalInterface{sampling_rate,parent}
{
    grid = new QGridLayout(this);
    range = new ctkRangeSlider(Qt::Horizontal);
    range->setMaximum(sampling_rate/2);

    max = new QSpinBox();
    min = new QSpinBox();
    max->setReadOnly(true);
    min->setReadOnly(true);
    max->setMaximum(sampling_rate/2);
    max->setMinimum(0);
    min->setMinimum(0);
    min->setMaximum(sampling_rate/2);



    connect(max,SIGNAL(valueChanged(int)),range,SLOT(setMaximumValue(int)));
    connect(min,SIGNAL(valueChanged(int)),range,SLOT(setMinimumValue(int)));

    connect(range,SIGNAL(minimumValueChanged(int)),min,SLOT(setValue(int)));
    connect(range,SIGNAL(maximumValueChanged(int)),max,SLOT(setValue(int)));

    connect(range,SIGNAL(sliderReleased()),this,SLOT(resample()));


    amplitude = new QSlider(Qt::Horizontal);
    amplitude->setMaximum(100);

    ampl = new QSpinBox();
    ampl->setMaximum(100);

    connect(amplitude,SIGNAL(valueChanged(int)),ampl,SLOT(setValue(int)));
    connect(ampl,SIGNAL(valueChanged(int)),amplitude,SLOT(setValue(int)));

    A = new QLabel("Amplitude");
    D = new QLabel("Range");

    grid->addWidget(D,0,1);
    grid->addWidget(range,1,1);
    grid->addWidget(min,1,0);
    grid->addWidget(max,1,2);
    grid->addWidget(Delete,2,2);
    grid->addWidget(A,2,1);
    grid->addWidget(amplitude,3,1);
    grid->addWidget(ampl,3,2);

    for(int i = 0;i < sampling_rate;i++)
        sample.push_back(0);

    this->setMaximumHeight(150);

}

Err::~Err()
{
    delete range;
    delete amplitude;
    delete ampl;
    delete max;
    delete min;
    delete D;
    delete A;
    delete grid;
}

double Err::getValue(double t)
{
    return sample[t]*amplitude->value();
}

void Err::resample()
{
std::vector<std::pair<double,double>> spectrum(sampling_rate/2,{0,0});
    for(int i = min->value(); i < max->value();i++){
        spectrum[i].first = static_cast<double>(QRandomGenerator::global()->bounded(-100, 100))/1000;
        spectrum[i].second = static_cast<double>(QRandomGenerator::global()->bounded(-100, 100))/1000;
    }
    sample = reFourier(spectrum);
}


