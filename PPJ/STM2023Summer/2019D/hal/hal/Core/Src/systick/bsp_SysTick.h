#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f4xx.h"

typedef uint32_t  u32;

void SysTick_Init(void);
void Delay_Us(__IO u32 nTime);
#define Delay_Ms(x) Delay_Us(100*x)	 //µ¥Î»ms

#endif /* __SYSTICK_H */
