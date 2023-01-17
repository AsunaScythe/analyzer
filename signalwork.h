#ifndef SIGNALWORK_H
#define SIGNALWORK_H

#include <QObject>
#include <vector>
#include <queue>
#include "qcustomplot.h"
#include "signal.h"

class SignalWork : public QObject
{
    Q_OBJECT
    std::vector<double>* callback;

public:
    explicit SignalWork(std::vector<double>*,QObject *parent = nullptr);

public slots:
    void clock();
signals:
    void finished();

};

#endif // SIGNALWORK_H
