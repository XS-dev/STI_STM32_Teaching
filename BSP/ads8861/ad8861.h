/**************************************************

CONVST = A4
DOUT = 	A5
SCLK =	A6
DIN	 = 	A7



**************************************************/

#ifndef _AD8861_H
#define _AD8861_H


#include "main.h"




//IO²Ù×÷º¯Êý	 
#define CONVST    PAout(4) 
#define SCLK    	PAout(6)  
#define DIN 			PAout(7)

#define READ_DOUT	PAin(5)

void AD_GPIO_INIT(void);
void AD_Init(void);
void AD_START(void);
void AD_STOP(void);
u16 AD_Read(void);
u16 AD_RESULT(void);


#endif

