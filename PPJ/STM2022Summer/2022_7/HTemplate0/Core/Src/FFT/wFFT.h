#ifndef	_wFFT_H
#define _wFFT_H


#include "main.h"

typedef struct
{
	float real;
	float imag;
} Complex;

extern float AM_fre;
extern float FM_fre;

extern float AMDMF;
extern float AM_order;
extern float AM_fregateHIGH[10] ;	
extern float AM_fregateLOW[10] 	;
extern float AM_Gate0X;
extern float FM_fre_HIGH;
unsigned char FFT(Complex *x,int m);

void FFT_Init(void);
void FFT_DIS(void);
void AM_peak(void);
void AM_MF0(void);
unsigned char JUDGE(void);
void AM_peak2(void);
void FM_peak(void);
void FM_peak2(void);

#endif

