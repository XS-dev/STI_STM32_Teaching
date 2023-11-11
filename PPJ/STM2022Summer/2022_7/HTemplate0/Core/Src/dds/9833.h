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

#define DSDATA_HIGH 			HAL_GPIO_WritePin(GPIOE, DDS_SDATA_Pin	, GPIO_PIN_SET);	
#define DCLK_HIGH				HAL_GPIO_WritePin(GPIOE, DDS_SCLK_Pin		, GPIO_PIN_SET);
#define DSYNC_HIGH				HAL_GPIO_WritePin(GPIOE, DDS_CS_Pin			, GPIO_PIN_SET);

#define DSDATA_LOW 			HAL_GPIO_WritePin(GPIOE, DDS_SDATA_Pin, GPIO_PIN_RESET);
#define DCLK_LOW					HAL_GPIO_WritePin(GPIOE, DDS_SCLK_Pin	, GPIO_PIN_RESET);
#define DSYNC_LOW				HAL_GPIO_WritePin(GPIOE, DDS_CS_Pin		, GPIO_PIN_RESET);





enum WaveType{SIN, SQR, TRI}; // Wave Selection Enum

// ------------------ Functions  ---------------------
void AD9833_SetWave(uint16_t Wave);                      // Sets Output Wave Type
void AD9833_SetWaveData(float Frequency,float Phase);    // Sets Wave Frequency & Phase
void AD9833_Init(void);   // Initializing AD9833


#endif

