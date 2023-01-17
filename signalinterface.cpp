#include "signalinterface.h"

SignalInterface::SignalInterface(int sampling_rate,QWidget *parent)
    : QWidget{parent} , sampling_rate{sampling_rate}
{
    Delete = new QPushButton("delete");
    connect(Delete,SIGNAL(clicked()),this,SLOT(deleteLater()));
}

SignalInterface::~SignalInterface()
{
     delete Delete;
}






