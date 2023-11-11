#ifndef	_xFFT_H
#define _xFFT_H

#include "main.h"

typedef struct
{
	float real;
	float imag;
} Complex;

void FFT_Init(void);

unsigned char FFT(Complex *x,int m);


void FFT_DIS(void);






#endif
