#include "general.h"
//����
//MCLK��Ƶ��Ϊ8000KHz����������ʱms������


void DelayMs (unsigned int ms)
{
	unsigned int iq0,iq1 ;
	for ( iq0 = ms ; iq0 > 0 ;iq0 --)
	for ( iq1 = LOOPCNT  ; iq1 > 0 ;iq1 --) ;
}
 
 
