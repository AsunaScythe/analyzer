#ifndef MYFILTRGUI_H
#define MYFILTRGUI_H

#include <QWidget>
#include <QGridLayout>
#include <QTimer>
#include <list>
#include <time.h>
#include "signalwork.h"
#include "qcustomplot.h"
#include "signal.h"
#include  "myparamplot.h"
#include "iir_f.h"
#include "fir_f.h"
#include "err.h"


//MainWidget
class MyFiltrGUI : public QWidget
{
    Q_OBJECT
    //WINDOW out and in signals
    std::list<double> data,output;

    //Callback buffer
    std::vector<double> callback_in, callback_out;

    //Sample_rate
    int sampling_rate,

    //Widget refresh
    t,refresh_rate, refresh_rate_spectrum;

    //ThreadWorkers
    SignalWork * worker_in, * worker_out;   
    QThread* thread_in,*thread_out;
    bool state_in,state_out,filtr_state;


    //Generator widget
    QWidget * test;
    QGridLayout* gridLayout,
                *gridFunctions;
    QScrollArea * function;

    //Buttons
    QPushButton * add_signal,
                * add_noise,
                * switch_f;

    //Settings
    QSlider * implementation_size_slider,
            * speed;

    //Plots
    QCustomPlot * input_signal,
                * spectrum_input,
                * output_signal,
                * spectrum_output;
    //Clock timer
    QTimer * timer;

    //Label
    QLabel * input, *filtred;

    //Filtr
    FiltrInterface *filtr;

public:
    explicit MyFiltrGUI(QWidget *parent = nullptr);
    ~MyFiltrGUI();
    void test_t();
signals:
    void data_refresh_in();
    void data_refresh_out();

public slots:
    void set_range(int);
    void add_graph();
    void addNoise();
    void clock();
    void set_speed(int);
    void refresh_spectrum_plot_in();
    void refresh_spectrum_plot_out();
    void switch_filtr();
};

#endif // MYFILTRGUI_H
