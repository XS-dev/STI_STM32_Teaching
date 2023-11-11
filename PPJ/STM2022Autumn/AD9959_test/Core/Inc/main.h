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
#include "AD9959.h"
#include "tim.h"
#include "gpio.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AD9959_P0_Pin GPIO_PIN_0
#define AD9959_P0_GPIO_Port GPIOD
#define AD9959_P1_Pin GPIO_PIN_1
#define AD9959_P1_GPIO_Port GPIOD
#define AD9959_P2_Pin GPIO_PIN_2
#define AD9959_P2_GPIO_Port GPIOD
#define AD9959_P3_Pin GPIO_PIN_3
#define AD9959_P3_GPIO_Port GPIOD
#define AD9959_SD0_Pin GPIO_PIN_4
#define AD9959_SD0_GPIO_Port GPIOD
#define AD9959_SD1_Pin GPIO_PIN_5
#define AD9959_SD1_GPIO_Port GPIOD
#define AD9959_SD2_Pin GPIO_PIN_6
#define AD9959_SD2_GPIO_Port GPIOD
#define AD9959_SD3_Pin GPIO_PIN_7
#define AD9959_SD3_GPIO_Port GPIOD
#define AD9959_SCK_Pin GPIO_PIN_3
#define AD9959_SCK_GPIO_Port GPIOB
#define AD9959_CS_Pin GPIO_PIN_4
#define AD9959_CS_GPIO_Port GPIOB
#define AD9959_UP_Pin GPIO_PIN_5
#define AD9959_UP_GPIO_Port GPIOB
#define AD9959_RST_Pin GPIO_PIN_6
#define AD9959_RST_GPIO_Port GPIOB
#define AD9959_PWR_Pin GPIO_PIN_7
#define AD9959_PWR_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
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
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
