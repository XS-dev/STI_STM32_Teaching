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
#include "keyboard.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern uint16_t key_flag; 
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
#define led_Pin GPIO_PIN_1
#define led_GPIO_Port GPIOA
#define R4_Pin GPIO_PIN_9
#define R4_GPIO_Port GPIOD
#define R4_EXTI_IRQn EXTI9_5_IRQn
#define R3_Pin GPIO_PIN_11
#define R3_GPIO_Port GPIOD
#define R3_EXTI_IRQn EXTI15_10_IRQn
#define R2_Pin GPIO_PIN_13
#define R2_GPIO_Port GPIOD
#define R2_EXTI_IRQn EXTI15_10_IRQn
#define R1_Pin GPIO_PIN_15
#define R1_GPIO_Port GPIOD
#define R1_EXTI_IRQn EXTI15_10_IRQn
#define C1_Pin GPIO_PIN_7
#define C1_GPIO_Port GPIOC
#define C2_Pin GPIO_PIN_9
#define C2_GPIO_Port GPIOC
#define C3_Pin GPIO_PIN_9
#define C3_GPIO_Port GPIOA
#define C4_Pin GPIO_PIN_11
#define C4_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
