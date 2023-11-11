/*************************************************************************************
 Title	:   Analog Devices AD9833 DDS Wave Generator Library for STM32 Using HAL Libraries
 Author:    Bardia Alikhan Afshar <bardia.a.afshar@gmail.com>  
 Software:  IAR Embedded Workbench for ARM
 Hardware:  Any STM32 device
 
 SDATA 	= 	A4
 SCLK  	= 	A5
 SYNC 	= 	A6
 
 
*************************************************************************************/
#ifndef _AD_9833_H
#define _AD_9833_H
#include <main.h>

// ------------------------- Defines -------------------------
#define FMCLK 25000000        // Master Clock On AD9833


#define SDATA(a) 			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,a)	
#define	DCLK(a) 			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,a)
#define	SYNC(a) 			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,a)



enum WaveType{SIN, SQR, TRI}; // Wave Selection Enum

// ------------------ Functions  ---------------------
void AD9833_SetWave(uint16_t Wave);                      // Sets Output Wave Type
void AD9833_SetWaveData(float Frequency,float Phase);    // Sets Wave Frequency & Phase
void AD9833_Init(void);   // Initializing AD9833


#endif

