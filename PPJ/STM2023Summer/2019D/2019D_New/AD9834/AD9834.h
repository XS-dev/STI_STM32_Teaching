#ifndef __AD9834_H__
#define __AD9834_H__
#include "main.h"

#define uchar 	uint32_t
#define uint  	uint32_t	
#define ulong  	uint32_t		

#define SCLK_Pin GPIO_PIN_2
#define SCLK_GPIO_Port GPIOD
#define AD9834_RST_Pin GPIO_PIN_6
#define AD9834_RST_GPIO_Port GPIOD
#define SDATA_Pin GPIO_PIN_5
#define SDATA_GPIO_Port GPIOB
#define FSYNC_Pin GPIO_PIN_9
#define FSYNC_GPIO_Port GPIOB

#define AD9834_SDATA_H      HAL_GPIO_WritePin(SDATA_GPIO_Port,  SDATA_Pin,      	GPIO_PIN_SET)
#define AD9834_SCLK_H       HAL_GPIO_WritePin(SCLK_GPIO_Port,   SCLK_Pin, 				GPIO_PIN_SET)
#define AD9834_RESET_H      HAL_GPIO_WritePin(AD9834_RST_GPIO_Port,    AD9834_RST_Pin,  				GPIO_PIN_SET)
#define AD9834_FSYNC_H      HAL_GPIO_WritePin(FSYNC_GPIO_Port,  FSYNC_Pin,				GPIO_PIN_SET)

#define AD9834_SDATA_L      HAL_GPIO_WritePin(SDATA_GPIO_Port,  SDATA_Pin,      	GPIO_PIN_RESET)
#define AD9834_SCLK_L       HAL_GPIO_WritePin(SCLK_GPIO_Port,   SCLK_Pin, 				GPIO_PIN_RESET)
#define AD9834_RESET_L      HAL_GPIO_WritePin(AD9834_RST_GPIO_Port,    AD9834_RST_Pin,  				GPIO_PIN_RESET)
#define AD9834_FSYNC_L      HAL_GPIO_WritePin(FSYNC_GPIO_Port,  FSYNC_Pin,				GPIO_PIN_RESET)

void AD9834_Init(void);

void AD9834_Gpio_Init(void);

void AD9834_Select_Wave(uint16_t initdata);

void AD9834_Set_Freq(uint8_t freq_number, uint32_t freq) ;

void AD9834_Write_16Bits(uint16_t data) ;



#endif


