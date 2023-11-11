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

#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include <stdio.h>
#include "math.h"
#include "stdlib.h"	
#include <stdbool.h>

#include "ShuMaGuan.h"
#include "keyboard.h"
#include "tm1637.h"
#include "tm1637_config.h"
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
#define SSCLK_Pin GPIO_PIN_11
#define SSCLK_GPIO_Port GPIOE
#define SSDIO_Pin GPIO_PIN_14
#define SSDIO_GPIO_Port GPIOE
#define R4_Pin GPIO_PIN_15
#define R4_GPIO_Port GPIOD
#define R3_Pin GPIO_PIN_7
#define R3_GPIO_Port GPIOC
#define R2_Pin GPIO_PIN_9
#define R2_GPIO_Port GPIOC
#define R1_Pin GPIO_PIN_9
#define R1_GPIO_Port GPIOA
#define C1_Pin GPIO_PIN_11
#define C1_GPIO_Port GPIOA
#define C2_Pin GPIO_PIN_15
#define C2_GPIO_Port GPIOA
#define C3_Pin GPIO_PIN_11
#define C3_GPIO_Port GPIOC
#define C4_Pin GPIO_PIN_0
#define C4_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
