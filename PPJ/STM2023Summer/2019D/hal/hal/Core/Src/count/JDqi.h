#ifndef _JDqi_H
#define _JDqi_H

#include "main.h"


#define JD1(a)	 	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_7,a)

#define JD4(a)	 	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,a)

#define JD3(a)	 	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,a)

#define JD2(a) 		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,a)

#endif

