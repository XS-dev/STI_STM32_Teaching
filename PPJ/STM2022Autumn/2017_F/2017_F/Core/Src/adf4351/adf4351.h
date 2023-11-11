#ifndef _ADF4351_H_
#define _ADF4351_H_

#include "main.h"

//#define 
#define ADF4351_CE_Pin GPIO_PIN_2
#define ADF4351_CE_GPIO_Port GPIOE
#define ADF4351_LE_Pin GPIO_PIN_3
#define ADF4351_LE_GPIO_Port GPIOE
#define ADF4351_DAT_Pin GPIO_PIN_4
#define ADF4351_DAT_GPIO_Port GPIOE
#define ADF4351_CLK_Pin GPIO_PIN_5
#define ADF4351_CLK_GPIO_Port GPIOE


#define ADF4351_R0			((uint32_t)0X2C8018)
#define ADF4351_R1			((uint32_t)0X8029)
#define ADF4351_R2			((uint32_t)0X10E42)
#define ADF4351_R3			((uint32_t)0X4B3)
#define ADF4351_R4			((uint32_t)0XEC803C)
#define ADF4351_R5			((uint32_t)0X580005)

#define ADF4351_R1_Base	((uint32_t)0X8001)
#define ADF4351_R4_Base	((uint32_t)0X8C803C)
#define ADF4351_R4_ON	  ((uint32_t)0X8C803C)
#define ADF4351_R4_OFF	((uint32_t)0X8C883C)

#define ADF4351_RF_OFF	((uint32_t)0XEC801C)

#define ADF4351_PD_ON		((uint32_t)0X10E42)
#define ADF4351_PD_OFF	((uint32_t)0X10E02)

void ADF4351Init(void);
void ReadToADF4351(uint8_t count, uint8_t *buf);
void WriteToADF4351(uint8_t count, uint8_t *buf);
void WriteOneRegToADF4351(uint32_t Regster);
void ADF4351_Init_some(void);
void ADF4351WriteFreq(float Fre);		//	(xx.x) M Hz

#endif

