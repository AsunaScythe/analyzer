#include "myfiltrgui.h"

MyFiltrGUI::MyFiltrGUI(QWidget *parent)
    : QWidget{parent} ,sampling_rate(3200) ,t(0)  ,refresh_rate(0), refresh_rate_spectrum(0),filtr_state(true) ,state_out(true), state_in(true)
{
    //INIT
    for(int i = 0;i < sampling_rate;i++){
        data.push_front(0);
        callback_in.push_back(0);
        callback_out.push_back(0);
        output.push_back(0);
    }

    //involute size
    implementation_size_slider = new QSlider();
    implementation_size_slider->setRange(20,3200);

    QObject::connect(implementation_size_slider, SIGNAL(valueChanged(int)),
              this, SLOT(set_range(int)));

    //speed
    speed = new QSlider();
    speed->setRange(750,999);

    QObject::connect(speed, SIGNAL(valueChanged(int)),
              this, SLOT(set_speed(int)));


    //plots
    input_signal = new QCustomPlot();
    input_signal->addGraph();
    spectrum_input = new QCustomPlot();
    spectrum_input->addGraph();
    output_signal = new QCustomPlot();
    output_signal->addGraph();
    spectrum_output = new QCustomPlot();
    spectrum_output->addGraph();

    spectrum_input->yAxis->setRangeUpper(100);
    spectrum_input->xAxis->setRangeUpper(sampling_rate/2);

    spectrum_output->yAxis->setRangeUpper(100);
    spectrum_output->xAxis->setRangeUpper(sampling_rate/2);

    input_signal->xAxis->setRangeUpper(implementation_size_slider->value());
    output_signal->xAxis->setRangeUpper(implementation_size_slider->value());

    input_signal->yAxis->setRange(-300,300);
    output_signal->yAxis->setRange(-300,300);


    //generator list
    function = new QScrollArea();
    test = new QWidget();
    gridFunctions = new QGridLayout(test);
    function->setWidget(test);
    function->setWidgetResizable(true);


    //add buttons
    add_signal = new QPushButton("add_signal");
    add_noise = new QPushButton("add_noise");
    switch_f = new QPushButton("switch\nFILTR");

    QObject::connect(add_signal,SIGNAL(pressed()),this,SLOT(add_graph()));
    QObject::connect(add_noise,SIGNAL(pressed()),this,SLOT(addNoise()));
    QObject::connect(switch_f,SIGNAL(pressed()),this,SLOT(switch_filtr()));

    //Threads
    worker_in = new SignalWork(&callback_in);
    worker_out = new SignalWork(&callback_out);
    thread_in = new QThread();
    thread_out = new QThread();
    worker_in->moveToThread(thread_in);
    worker_out->moveToThread(thread_out);
    thread_in->start();
    thread_out->start();

    connect(this, &MyFiltrGUI::data_refresh_in, worker_in, &SignalWork::clock);
    connect(this, &MyFiltrGUI::data_refresh_out, worker_out, &SignalWork::clock);
    connect(worker_in, &SignalWork::finished, this, &MyFiltrGUI::refresh_spectrum_plot_in);
    connect(worker_out, &SignalWork::finished, this, &MyFiltrGUI::refresh_spectrum_plot_out);


    //Clock timer
    timer = new QTimer();
    timer->start(1000-speed->value());
    connect(timer, SIGNAL(timeout()), this, SLOT(clock()));


    //Label
    input = new QLabel("INPUT");
    filtred = new QLabel("OUTPUT");


    //Filtr
    filtr = new FIR_F();

    //MainLayout
    gridLayout = new QGridLayout(this);

    gridLayout->addWidget(filtr,1,4);
    gridLayout->addWidget(input,0,3);
    gridLayout->addWidget(filtred,0,5);
    gridLayout->addWidget(add_signal,0,0);
    gridLayout->addWidget(add_noise,0,1);
    gridLayout->addWidget(function,1,0,2,2);
    gridLayout->addWidget(implementation_size_slider,1,2);
    gridLayout->addWidget(speed,2,2);
    gridLayout->addWidget(input_signal,1,3);
    gridLayout->addWidget(spectrum_input,2,3);
    gridLayout->addWidget(output_signal,1,5);
    gridLayout->addWidget(spectrum_output,2,5);
    gridLayout->addWidget(switch_f,2,4);
    gridLayout->setColumnMinimumWidth(0,150);
    gridLayout->setColumnMinimumWidth(1,150);
    gridLayout->setColumnMinimumWidth(3,500);
    gridLayout->setColumnMinimumWidth(5,500);
    gridLayout->setColumnMinimumWidth(4,120);
    gridLayout->setRowMinimumHeight(2,400);
    gridLayout->setRowMinimumHeight(1,400);


}

MyFiltrGUI::~MyFiltrGUI()
{
    thread_in->exit();
    thread_out->exit();

    delete add_signal;
    delete add_noise;
    delete switch_f;

    delete implementation_size_slider;
    delete speed;

    delete input_signal;
    delete output_signal;
    delete spectrum_input;
    delete spectrum_output;

    delete timer;

    delete input;
    delete filtred;

    while (QLayoutItem *itm = gridFunctions->itemAt(0))
        delete itm->widget();

    delete gridFunctions;
    delete test;
    delete function;

    delete filtr;
    delete gridLayout;
}
//SIMD  TEST
void MyFiltrGUI::test_t()
{
    __m128i e = _mm_set_epi32(456,456,456,456);
    for(int i  = 0;i < 2500;i++)
        e = _mm_add_epi32(e,e);


    auto y = std::clock();

    int k = 456;
    for(int i = 0;i < 10000;i++)
        k*=k;

    y = std::clock()-y;
}

void MyFiltrGUI::set_range(int value)
{

    input_signal->xAxis->setRangeUpper(double(value));
    input_signal->replot();

    output_signal->xAxis->setRangeUpper(double(value));
    output_signal->replot();

}

void MyFiltrGUI::add_graph()
{ 

    gridFunctions->addWidget(new MyParamPlot(sampling_rate));

}

void MyFiltrGUI::addNoise()
{
    gridFunctions->addWidget(new Err(sampling_rate));
}

void MyFiltrGUI::clock()
{

    double sum = 0;
    for(int i = 0;i < gridFunctions->count();i++)
        sum += static_cast<SignalInterface*>(gridFunctions->itemAt(i)->widget())->getValue(t);

    data.pop_back();
    data.push_front(sum);

    output.pop_back();
    output.push_front(filtr->next(sum));

    t = (t+1)%sampling_rate;


    int N = 0;

    refresh_rate +=  timer->interval();
    if(refresh_rate > 1){

        input_signal->graph(0)->data()->clear();
        for(auto i = data.begin();N < implementation_size_slider->value();i++)
            input_signal->graph(0)->addData(N++,*i);
        input_signal->replot();

        N = 0;
        output_signal->graph(0)->data()->clear();
        for(auto i = output.begin();N < implementation_size_slider->value();i++)
            output_signal->graph(0)->addData(N++,*i);
        output_signal->replot();
        refresh_rate %= 1;
    }

    refresh_rate_spectrum += timer->interval();
    if(refresh_rate_spectrum > 500){
    if(state_in){
        state_in = false;
        N=0;
        for(auto i : data)
            callback_in[N++] = i;
        emit data_refresh_in();
    }

    if(state_out){
        state_out = false;
        N=0;
        for(auto i : output)
            callback_out[N++] = i;
        emit data_refresh_out();
    }
        refresh_rate_spectrum %=  500;
    }


}

void MyFiltrGUI::set_speed(int value)
{
    timer->start(1000-value);
}

void MyFiltrGUI::refresh_spectrum_plot_out()
{
    spectrum_output->graph(0)->data()->clear();

    for(int i = 0;i < sampling_rate/2;i++)
        spectrum_output->graph(0)->addData(i,callback_out[i]);

    spectrum_output->replot();
    state_out = true;
}

void MyFiltrGUI::switch_filtr()
{
    auto temp = filtr;
    if(filtr_state) filtr = new IIR_F();
    else filtr = new FIR_F();
    gridLayout->addWidget(filtr,1,4);
    delete temp;
    filtr_state = !filtr_state;
}

//Callback
void MyFiltrGUI::refresh_spectrum_plot_in()
{
    spectrum_input->graph(0)->data()->clear();

    for(int i = 0;i < sampling_rate/2;i++)
        spectrum_input->graph(0)->addData(i,callback_in[i]);

    spectrum_input->replot();
    state_in = true;
}



