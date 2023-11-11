#ifndef __timer_H
#define __timer_H
#include "stm32f10x.h"
#include "lcd.h"
#include "key.h"

extern u32 SweepMinFre;
extern u32 SweepMaxFre;
extern u32 SweepStepFre;
extern u16 SweepTime;//ms
extern u8 SweepFlag;

void Timerx_Init(u16 arr,u16 psc);


#endif
