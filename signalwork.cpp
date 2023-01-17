#include "signalwork.h"

SignalWork::SignalWork(std::vector<double>* callback,QObject *parent)
    : QObject{parent} , callback(callback)
{
}

void SignalWork::clock()
{
    auto answer = Fourier(*callback);
    for(int i =0;i < answer.size();i++)
        (*callback)[i] = (sqrt(answer[i].first*answer[i].first + answer[i].second*answer[i].second));
    emit finished();
}

