#include "fir_f.h"

FIR_F::FIR_F(QWidget *parent):FiltrInterface{parent},
    //Coefficient
    coef{299,
         -377,
         -728,
         -302,
          549,
          933,
          306,
         -841,
        -1300,
         -308,
         1472,
         2199,
          311,
        -3958,
        -8398,
        19635,
        -8398,
        -3958,
          311,
         2199,
         1472,
         -308,
        -1300,
         -841,
          306,
          933,
          549,
         -302,
         -728,
         -377,
          299,
         0}

{
    //INIT BUFF AND COEF
    for(int i = 0;i < 32;i++)
        buff[i] = 0;


    for(int i = 0;i < 8;i++)
        coef_4[i] = _mm_set_epi32(coef[0+i*4],coef[1+i*4],coef[2+i*4],coef[3+i*4]);

    //Label
    grid = new QGridLayout(this);
    type = new QLabel("FIR");
    stopband = new QLabel("Stopband\n0-500 Hz");
    passband = new QLabel("Passband\n600-1600 Hz");

    type->setAlignment(Qt::AlignCenter);
    stopband->setAlignment(Qt::AlignCenter);
    passband->setAlignment(Qt::AlignCenter);

    grid->addWidget(type);
    grid->addWidget(passband);
    grid->addWidget(stopband);

    grid->setAlignment(Qt::AlignCenter);

}

FIR_F::~FIR_F()
{
    delete type;
    delete passband;
    delete stopband;
    delete grid;
}
//Mainloop
double FIR_F::next(double input)
{
    for(int i = 29;i >= 0;i--)
        buff[i+1] = buff[i];

    buff[0] = static_cast<int>(input*(1<<15)) >> 8;

    __m128i buff_4,
            answer;
    answer = _mm_set_epi32(0,0,0,0);
    for(int i = 0;i < 8;i++){
        buff_4 = _mm_mullo_epi32(_mm_set_epi32(buff[0+i*4],buff[1+i*4],buff[2+i*4],buff[3+i*4]),coef_4[i]);
        answer = _mm_add_epi32(answer,buff_4);
    }   
    return (double((_mm_extract_epi32(answer,0) + _mm_extract_epi32(answer,1) + _mm_extract_epi32(answer,2) + _mm_extract_epi32(answer,3)) >> 7))/(1<<15);

//Version without SIMD
/*
    int answer = 0;
    for(int i = 0; i < 31;i++)
        answer_1 += (buff[i]*coef[i])>>7;
*/
}
