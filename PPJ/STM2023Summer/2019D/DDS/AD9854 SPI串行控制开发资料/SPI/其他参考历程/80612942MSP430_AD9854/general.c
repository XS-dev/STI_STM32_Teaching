#include "general.h"
//函数
//MCLK的频率为8000KHz的条件下延时ms个毫秒


void DelayMs (unsigned int ms)
{
	unsigned int iq0,iq1 ;
	for ( iq0 = ms ; iq0 > 0 ;iq0 --)
	for ( iq1 = LOOPCNT  ; iq1 > 0 ;iq1 --) ;
}
 
 
