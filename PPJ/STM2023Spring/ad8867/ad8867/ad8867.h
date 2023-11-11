/**************************************************

CONVST = A4
DOUT = 	A5
SCLK =	A6
DIN	 = 	A7



**************************************************/

#ifndef _AD8867_H
#define _AD8867_H


#include "main.h"

//#define ADSTART_Pin GPIO_PIN_3
//#define ADSTART_GPIO_Port GPIOC
//#define ADOUT_Pin GPIO_PIN_3
//#define ADOUT_GPIO_Port GPIOA
//#define ADSCLK_Pin GPIO_PIN_7
//#define ADSCLK_GPIO_Port GPIOA
//#define ADCS_Pin GPIO_PIN_1
//#define ADCS_GPIO_Port GPIOB



#define DIN_H			HAL_GPIO_WritePin(ADCS_GPIO_Port,			ADCS_Pin,			GPIO_PIN_SET);	
#define CONVST_H	HAL_GPIO_WritePin(ADSTART_GPIO_Port,	ADSTART_Pin,	GPIO_PIN_SET);	
#define SCLK_H		HAL_GPIO_WritePin(ADSCLK_GPIO_Port,		ADSCLK_Pin,		GPIO_PIN_SET);	

#define DIN_L			HAL_GPIO_WritePin(ADCS_GPIO_Port,			ADCS_Pin,			GPIO_PIN_RESET);	
#define CONVST_L	HAL_GPIO_WritePin(ADSTART_GPIO_Port,	ADSTART_Pin,	GPIO_PIN_RESET);	
#define SCLK_L		HAL_GPIO_WritePin(ADSCLK_GPIO_Port,		ADSCLK_Pin,		GPIO_PIN_RESET);	

#define READ_DOUT	HAL_GPIO_ReadPin(ADOUT_GPIO_Port,		ADOUT_Pin)

void AD_GPIO_INIT(void);
void AD_Init(void);
void AD_START(void);
void AD_STOP(void);
uint16_t AD_Read(void);
uint16_t AD_RESULT(void);


#endif

