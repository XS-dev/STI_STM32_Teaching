
#ifndef _MAIN_H_
#define _MAIN_H_
/*****************************
      官方头文件
*****************************/
#include  <math.h>
#include <arm_math.h>
#include "u_dma.h"
#include "measure.h"
#include "stdio.h"

#include "driverlib.h"
/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
/******************************
    数据类型定义
******************************/
typedef signed long s32;
typedef signed short s16;
typedef signed char s8;
typedef signed long const sc32; /* Read Only */
typedef signed short const sc16; /* Read Only */
typedef signed char const sc8; /* Read Only */
typedef volatile signed long vs32;
typedef volatile signed short vs16;
typedef volatile signed char vs8;
typedef volatile signed long const vsc32; /* Read Only */
typedef volatile signed short const vsc16; /* Read Only */
typedef volatile signed char const vsc8; /* Read Only */
typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned long const uc32; /* Read Only */
typedef unsigned short const uc16; /* Read Only */
typedef unsigned char const uc8; /* Read Only */
typedef volatile unsigned long vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char vu8;
typedef volatile unsigned long const vuc32; /* Read Only */
typedef volatile unsigned short const vuc16; /* Read Only */
typedef volatile unsigned char const vuc8; /* Read Only */


void clk_init(void);
void start_DMA(void);

extern arm_rfft_fast_instance_f32  _1024_fft;

extern u8 gears;

extern float voltage_real[1024];
extern float voltage_fft[1024];
extern uint16_t data_array1[1024];
extern float Hanning[1024];
extern float voltage_before_fft[1024];	
/****************************
      Basic内部外设头文件
*****************************/
#include "delay.h"
#include "systeminit.h"
#include "usart.h"
#include "adc.h"

/***************************
      Hardware外设头文件
*****************************/
#include "led.h"
#include "oled.h"
#include "key.h"



#endif


