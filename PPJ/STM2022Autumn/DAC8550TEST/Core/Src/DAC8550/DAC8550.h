#ifndef _DAC8550_h_
#define _DAC8550_h_

#include "main.h"


//#define DAC_SCLK_Pin GPIO_PIN_2
//#define DAC_SCLK_GPIO_Port GPIOE
//#define DAC_SYNC_Pin GPIO_PIN_3
//#define DAC_SYNC_GPIO_Port GPIOE
//#define DAC_DATA_Pin GPIO_PIN_4
//#define DAC_DATA_GPIO_Port GPIOE
extern float pi;
extern const int32_t sinbox[200];
#define DIN1 				HAL_GPIO_WritePin(DAC_DATA_GPIO_Port, DAC_DATA_Pin, GPIO_PIN_SET);
#define SCLK1 			HAL_GPIO_WritePin(DAC_SCLK_GPIO_Port, DAC_SCLK_Pin, GPIO_PIN_SET);
#define SYNC1  		HAL_GPIO_WritePin(DAC_SYNC_GPIO_Port, DAC_SYNC_Pin, GPIO_PIN_SET);


#define DIN0 				HAL_GPIO_WritePin(DAC_DATA_GPIO_Port, DAC_DATA_Pin, GPIO_PIN_RESET);
#define SCLK0 			HAL_GPIO_WritePin(DAC_SCLK_GPIO_Port, DAC_SCLK_Pin, GPIO_PIN_RESET);
#define SYNC0  		HAL_GPIO_WritePin(DAC_SYNC_GPIO_Port, DAC_SYNC_Pin, GPIO_PIN_RESET);

int32_t cal_dac(uint16_t frequency,uint16_t fre_i);
void 		DAC8550_init(void);
void 		write_8550(uint32_t data);
void 		voltage_output(int32_t data);

#endif
