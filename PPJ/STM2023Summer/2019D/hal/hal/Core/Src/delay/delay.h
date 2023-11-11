#ifndef __DELAY_H
#define __DELAY_H                
 
#include "main.h"
extern TIM_HandleTypeDef htim2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_TIM2_Init(void); 
void SysTick_Delay_Ms(uint16_t nms);
void SysTick_Delay_Us(uint32_t nus);
#endif

