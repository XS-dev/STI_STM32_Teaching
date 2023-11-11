#ifndef _UFFT_H
#define _UFFT_H

#include "main.h"

//#define MAX_FFT_N 16384

typedef struct
{
	float real;
	float imag;
} Complex;





void FFT_Init(void);
void FFT_DIS(void);
unsigned char XFFT(Complex *d,int m);








#endif

