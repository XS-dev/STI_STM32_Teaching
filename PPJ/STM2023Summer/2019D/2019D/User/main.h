#ifndef _MAIN_H
#define	_MAIN_H



#include "stm32f10x.h"
#include <stdio.h>
#include "math.h"
#include "stdlib.h"
#include "sys.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "bsp_SysTick.h"
#include "core_cm3.h"
#include "misc.h"
//#include "esp8266.h"

#include "bsp_adc.h"

#include "bsp_led.h"
#include "bsp_usart.h"
//#include "bsp_GeneralTim.h"  
#include "./key/bsp_key.h"  
#include "bsp_led.h" 
#include "lcd.h"
#include "stm32f10x_it.h"
#include "9833.h"
//#include "bsp_AdvanceTim.h" 
//#include "./beep/bsp_beep.h"   
#include "JDqi.h"
#include "count.h"
#include "measure.h"

extern float ADC_ConvertedValueLocal[1024];
extern float wave_show[1024];
extern float Input[480] ;
extern float Output[480];

#endif

