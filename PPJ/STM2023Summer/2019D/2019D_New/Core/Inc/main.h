/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//extern uint32_t FFT_LENGTH; 
#define FFT_LENGTH 100
#define ADC_BUFFER_SIZE FFT_LENGTH//ADC1用了4通道, 存32组, 方便做平均
extern int Chande_flag;
extern ALIGN_32BYTES (uint16_t adc1_data[10000]) 	__attribute__((section(".ARM.__at_0x30020000")));
extern ALIGN_32BYTES (uint16_t adc3_data[2000]) 	__attribute__((section(".ARM.__at_0x30000000")));

extern float InputRes;
extern float InputAC ;
extern float InputAC_kailu ;

extern float OutputAC ;
extern float OutputResAC ;
extern float OutputRes ;
extern float Upper_K;
extern float Gain;

extern float scan_data[480];
extern uint16_t comp[2000];
extern uint32_t frequency;
extern char screen_message[30];

extern float Check_OutputRes ;

extern float Check_InputRes ;

extern float Check_Gain ;

extern float Check_DC ;

extern float OutputDC;

extern uint16_t Error_flag;

extern uint16_t Check_flag;

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

#include <stdio.h>
#include "math.h"
#include "stdlib.h"	
#include <stdbool.h>

#include "arm_math.h"
#include "arm_const_structs.h"

#include "adc.h"
//#include "dac.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "AD9910.h"
//#include "AD9834.h"
//#include "xadc.h"
//#include "xFFT.h"

#include "Measure.h"
#include "display.h"
#include "error_detect.h"


typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;  

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  
typedef __I int16_t vsc16; 
typedef __I int8_t vsc8;   

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8; 

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8;  
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
void adc_saopin(void);
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Key3_Pin GPIO_PIN_3
#define Key3_GPIO_Port GPIOE
#define Key3_EXTI_IRQn EXTI3_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
