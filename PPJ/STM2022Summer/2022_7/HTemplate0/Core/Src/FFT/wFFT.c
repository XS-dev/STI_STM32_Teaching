#include "wFFT.h"

float AM_Gate0 	= 13700;//第一题要求中的门限；
float AM_Gate0X = 20;//第一门限修正值
float AM_fregateHIGH[10] 	= {0};//AM调制的频率值
float AM_fregateLOW[10] 	= {0};//AM调制的频率值

float AM_fre_HIGH 		= 0;
float FM_fre_HIGH 		= 0;



float AM_fre_LOW 			= 0;
float AM_fre		 			= 0;
float FM_fre		 			= 0;

float AM_order 				= 0;
float AMDMF 					= 0;//调幅度
ALIGN_32BYTES (Complex q[FFT_LENGTH])   __attribute__((section(".ARM.__at_0x24000000")) );
ALIGN_32BYTES (Complex q1[FFT_LENGTH])  __attribute__((section(".ARM.__at_0x24040000")) );
void FFT_Init(void)
{

		for(uint32_t i=0; i<FFT_LENGTH; i++)
		{
			/* *(0.54f-0.46f*cosf(6.283185307f*i/FFT_LENGTH)) */
//			q1[i].real = adc1_data[i] *(0.5-0.5*cos(6.283185307*i/FFT_LENGTH))*3.3/65536;	
			q1[i].real = adc1_data[i] *3.3/65536;		
			q1[i].imag = 0;
		}
		FFT(q1, 15);
		for(uint32_t i=0; i<FFT_LENGTH; i++)
		{
			arm_sqrt_f32((float)(q1[i].real *q1[i].real+ q1[i].imag*q1[i].imag ), &q1[i].real); 
		}
	
}




void FFT_DIS(void)
{
//		for(uint32_t i=1550; i<6750; i++)
//		for(uint32_t i = 0; i < FFT_LENGTH; i++) 
		for(uint32_t i=3000; i<4000; i++)
		{
//			printf("%f\r\n", q1[i].real);
				printf("%d:\t%f\r\n", i,  q1[i].real);			
		}

}

void FM_peak(void)
{
	float a[6] = {0};
	a[0] = 0;
	a[1] = 0;
	a[2] = 0;
	a[3] = 0;
	a[4] = 0;
	a[5] = 3480;
	for(uint32_t i=3700; i>3300; i--)
	{
		if(q1[i].real > 1000){a[5] = i;break;}
	}
	FM_fre_HIGH =  a[5];
	FM_fre = (FM_fre_HIGH - 3276)*15.25+120;
}
void FM_peak2(void)
{
	float a[6] = {0};
	a[0] = 0;
	a[1] = 0;
	a[2] = 0;
	a[3] = 0;
	a[4] = 0;
	a[5] = 3600;
	for(uint32_t i=3950; i>3580; i--)
	{
		if(q1[i].real > 1000){a[5] = i;break;}
	}
	FM_fre_HIGH =  a[5];
	FM_fre = (FM_fre_HIGH - 3276)*15.25+120;
	if((4500<FM_fre)&&(FM_fre <= 5500)){FM_fre = 5000;}
	if((5500<FM_fre)&&(FM_fre <= 6500)){FM_fre = 6000;}
	if((6500<FM_fre)&&(FM_fre <= 7500)){FM_fre = 7000;}
	if((7500<FM_fre)&&(FM_fre <= 8500)){FM_fre = 8000;}
	if((8500<FM_fre)&&(FM_fre <= 9500)){FM_fre = 9000;}
	if((9500<FM_fre)&&(FM_fre <= 10500)){FM_fre = 10000;}
}



unsigned char JUDGE(void)
{
	for(uint32_t i=4000; i<5000; i++)
	{
		if(q1[i].real >600){FM_flag = 1;break;}
	}
	if(FM_flag == 1)
	{
		printf("FM\r\n");
		return 0;
	}
	for(uint32_t i=3500; i<3960; i++)
	{
		if(q1[i].real > 420){AM_flag = 1;break;}
	}
	if(AM_flag == 1)
	{
		printf("AM\r\n");
		return 0;
	}	
	printf("None\r\n");
	None_flag = 1;
	return 0;
}


void AM_peak2(void)
{
	float a[6] = {0};
	a[0] = 0;
	a[1] = 0;
	a[2] = 0;
	a[3] = 0;
	a[4] = 0;
	a[5] = 3600;
	for(uint32_t i=3950; i>3580; i--)
	{
		if(q1[i].real > 400){a[5] = i;break;}
	}
	AM_fre_HIGH =  a[5];
	AM_fre = (AM_fre_HIGH - 3276)*15.25+2000;
	if((4500<AM_fre)&&(AM_fre <= 5500)){AM_fre = 5000;}
	if((5500<AM_fre)&&(AM_fre <= 6500)){AM_fre = 6000;}
	if((6500<AM_fre)&&(AM_fre <= 7500)){AM_fre = 7000;}
	if((7500<AM_fre)&&(AM_fre <= 8500)){AM_fre = 8000;}
	if((8500<AM_fre)&&(AM_fre <= 9500)){AM_fre = 9000;}
	if((9500<AM_fre)&&(AM_fre <= 10500)){AM_fre = 10000;}
	printf("%f\r\n", AM_fre);
}



unsigned char FFT(Complex *d,int m)
{
#ifndef __EXTERN_W__
	static Complex *w;
	static int mw = 0;
	float arg, w_real, w_imag, wr_real, wr_imag, wtemp;
#endif
	static int n = 1;
	Complex temp, tmp1, tmp2;
	Complex *di, *dip, *dj, *wp;
	int i, j, k, l, le, wi;
#ifndef __EXTERN_W__
	if(m != mw)
	{
		if(mw != 0)
			free(w);
		mw = m;
		if(m == 0)
			return 0;
		n = 1 << m;
		le = n >> 1;
		w =q;
		if(!w)
			return 0;
		arg = 4.0 * atan(1.0) / le;
		wr_real = w_real = cos(arg);
		wr_imag = w_imag = -sin(arg);
		dj = w;
		for(j = 1; j < le; j++)
		{
			dj->real = (float)wr_real;
			dj->imag = (float)wr_imag;
			dj++;
			wtemp = wr_real * w_real - wr_imag * w_imag;
			wr_imag = wr_real * w_imag + wr_imag * w_real;
			wr_real = wtemp;
		}
	}
#else
	n = 1 << m;
#endif
	le = n;
	wi = 1;
	for(l = 0; l < m; l++)
	{
		le >>= 1;
		for(i = 0; i < n; i += (le << 1))
		{
			di = d + i;
			dip = di + le;
			temp.real = (di->real + dip->real);
			temp.imag = (di->imag + dip->imag);
			dip->real = (di->real - dip->real);
			dip->imag = (di->imag - dip->imag);
			*di = temp;
		}
		wp = (Complex*)w + wi - 1;
		for(j = 1; j < le; j++)
		{
			tmp1 = *wp;
			for(i = j; i < n; i += (le << 1))
			{
				di = d + i;
				dip = di + le;
				temp.real = (di->real + dip->real);
				temp.imag = (di->imag + dip->imag);
				tmp2.real = (di->real - dip->real);
				tmp2.imag = (di->imag - dip->imag);
				dip->real = (tmp2.real * tmp1.real - tmp2.imag * tmp1.imag);
				dip->imag = (tmp2.real * tmp1.imag + tmp2.imag * tmp1.real);
				*di = temp;
			}
			wp += wi;
		}
		wi <<= 1;
	}

	for(i = 0; i < n; i++)
	{
		j = 0;
		for(k = 0; k < m; k++)
			j = (j << 1) | ((i >> k) & 1);
		if(i < j)
		{
			di = d + i;
			dj = d + j;
			temp = *dj;
			*dj = *di;
			*di = temp;
		}
	}
	return 1;
}



void AM_peak(void)
{
	float a[6] = {0};
	a[0] = 0;
	a[1] = 0;
	a[2] = 0;
	a[3] = 0;
	a[4] = 0;
	a[5] = 3480;
	for(uint32_t i=3500; i>3300; i--)
	{
		if(q1[i].real > 400){a[5] = i;break;}
	}
	AM_fre_HIGH =  a[5];
	AM_fre = (AM_fre_HIGH - 3276)*15.25+120;
}

void AM_MF0(void)
{
	uint32_t  A5[5000] ={0};
	for(uint16_t tmp = 0;tmp < 5000;tmp++)
	A5[tmp] = adc1_data[tmp+1000];

	QuickSort(A5, 0, 4999);
//	for(uint16_t tmp = 0;tmp < 5000;tmp++)
//	printf("\t%d   %d\r\n",tmp, A5[tmp]);
//	printf("%d\r\n", A5[tmp]);

	AMDMF = ((float)A5[5000-50] - (float)A5[50])/((float)AM_Gate0-(float)AM_Gate0X) - 1+0.05;
//	printf("%f\r\n",AMDMF);
}

