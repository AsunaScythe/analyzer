#ifndef FILTRINTERFACE_H
#define FILTRINTERFACE_H

#include <QWidget>

//Interface for filtr
class FiltrInterface : public QWidget
{
    Q_OBJECT
public:
    explicit FiltrInterface(QWidget *parent = nullptr);

    virtual double next(double) = 0;

    virtual ~FiltrInterface() = default;

signals:

};

#endif // FILTRINTERFACE_H
