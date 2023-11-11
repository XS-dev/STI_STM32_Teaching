#ifndef _AD7883_H
#define _AD7883_H


#include "main.h"



#define AD78_SCLK			PCout(9)
#define AD78_SDO			PCout(6)
#define AD78_CS 			PCout(11)

#define AD78_SDO_READ			PCin(6)


void 	AD78_init(void);
u16 	AD78_Read(void);
#endif

