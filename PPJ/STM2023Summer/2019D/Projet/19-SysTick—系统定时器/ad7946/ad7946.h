#ifndef		_AD7946_H
#define		_AD7946_H

#include "main.h"


#define CS 			PCout(9)
#define ADCLK		PCout(10)
#define SDO			PCout(11)

#define SDO_READ	PCin(11)


void AD79_Init(void);
u16 AD79_Read(void);
#endif


