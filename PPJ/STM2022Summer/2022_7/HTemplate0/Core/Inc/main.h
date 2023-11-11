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
#include <stdio.h>
#include "math.h"
#include "stdlib.h"	
#include <stdbool.h>


#include "9833.h"
#include "AD9854.h"    
#include "lcd.h"
#include "esp8266.h"
//#include "bdma.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"
#include "UFFT.h"
#include "fre_cal.h"
#include "AM.h"
#include "FM.h"
#include "wFFT.h"
#include "arm_math.h"
#include "arm_const_structs.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
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
#define FFT_LENGTH 32768
#define ADC1_BUFFER_SIZE MAX_FFT_N*1	//ADC1用了4通道, 存32组, 方便做平均
//#define ADC3_BUFFER_SIZE FFT_LENGTH*1	//ADC3用了8通道, 存32组, 方便做平均
#define MAX_FFT_N	8192
extern ALIGN_32BYTES (uint16_t adc1_data[FFT_LENGTH]) __attribute__((section(".ARM.__at_0x30020000")));


extern float			count_flag;

extern u16 None_flag;//进入第三题
extern u16 AM_flag 	;//进入AM题
extern u16 FM_flag 	;//进入FM题
extern uint32_t fm_value[10];
//extern struct compx s[MAX_FFT_N]; 
extern uint32_t 	cnt 						 ;
extern uint32_t 	cnt_value[201] 	 ;
extern uint32_t 	capture_Buf[3] 	 ;
extern uint8_t 	capture_Cnt 			 ;
extern uint32_t 	high_time 				 ;
extern u16 			fm_temp 					 ;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DDS_SDATA_Pin GPIO_PIN_10
#define DDS_SDATA_GPIO_Port GPIOE
#define DDS_SCLK_Pin GPIO_PIN_12
#define DDS_SCLK_GPIO_Port GPIOE
#define DDS_CS_Pin GPIO_PIN_14
#define DDS_CS_GPIO_Port GPIOE
#define DDRST_Pin GPIO_PIN_8
#define DDRST_GPIO_Port GPIOD
#define DA5_Pin GPIO_PIN_9
#define DA5_GPIO_Port GPIOD
#define DD7_Pin GPIO_PIN_10
#define DD7_GPIO_Port GPIOD
#define DA4_Pin GPIO_PIN_11
#define DA4_GPIO_Port GPIOD
#define DD6_Pin GPIO_PIN_12
#define DD6_GPIO_Port GPIOD
#define DA3_Pin GPIO_PIN_13
#define DA3_GPIO_Port GPIOD
#define DD5_Pin GPIO_PIN_14
#define DD5_GPIO_Port GPIOD
#define DA2_Pin GPIO_PIN_15
#define DA2_GPIO_Port GPIOD
#define DD4_Pin GPIO_PIN_6
#define DD4_GPIO_Port GPIOC
#define DA1_Pin GPIO_PIN_7
#define DA1_GPIO_Port GPIOC
#define DD3_Pin GPIO_PIN_8
#define DD3_GPIO_Port GPIOC
#define DA0_Pin GPIO_PIN_9
#define DA0_GPIO_Port GPIOC
#define DD2_Pin GPIO_PIN_8
#define DD2_GPIO_Port GPIOA
#define UCLK_Pin GPIO_PIN_9
#define UCLK_GPIO_Port GPIOA
#define DD1_Pin GPIO_PIN_10
#define DD1_GPIO_Port GPIOA
#define WD_Pin GPIO_PIN_11
#define WD_GPIO_Port GPIOA
#define DD0_Pin GPIO_PIN_12
#define DD0_GPIO_Port GPIOA
#define RD_Pin GPIO_PIN_15
#define RD_GPIO_Port GPIOA
#define OSK_Pin GPIO_PIN_11
#define OSK_GPIO_Port GPIOC
#define FSK_Pin GPIO_PIN_0
#define FSK_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
