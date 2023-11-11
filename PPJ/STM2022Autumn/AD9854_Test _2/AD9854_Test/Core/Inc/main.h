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
#include "AD9854.h" 
#include "tim.h"
#include "gpio.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
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
#define DA5_Pin GPIO_PIN_9
#define DA5_GPIO_Port GPIOD
#define DA4_Pin GPIO_PIN_11
#define DA4_GPIO_Port GPIOD
#define DA3_Pin GPIO_PIN_13
#define DA3_GPIO_Port GPIOD
#define DA2_Pin GPIO_PIN_15
#define DA2_GPIO_Port GPIOD
#define DA1_Pin GPIO_PIN_7
#define DA1_GPIO_Port GPIOC
#define DA0_Pin GPIO_PIN_9
#define DA0_GPIO_Port GPIOC
#define UDCLK_Pin GPIO_PIN_9
#define UDCLK_GPIO_Port GPIOA
#define WD_Pin GPIO_PIN_11
#define WD_GPIO_Port GPIOA
#define DDRST_Pin GPIO_PIN_15
#define DDRST_GPIO_Port GPIOA
#define FSK_Pin GPIO_PIN_11
#define FSK_GPIO_Port GPIOC
#define OSK_Pin GPIO_PIN_0
#define OSK_GPIO_Port GPIOD
#define DD7_Pin GPIO_PIN_2
#define DD7_GPIO_Port GPIOD
#define DD6_Pin GPIO_PIN_4
#define DD6_GPIO_Port GPIOD
#define DD5_Pin GPIO_PIN_6
#define DD5_GPIO_Port GPIOD
#define DD4_Pin GPIO_PIN_3
#define DD4_GPIO_Port GPIOB
#define DD3_Pin GPIO_PIN_5
#define DD3_GPIO_Port GPIOB
#define DD2_Pin GPIO_PIN_7
#define DD2_GPIO_Port GPIOB
#define DD1_Pin GPIO_PIN_9
#define DD1_GPIO_Port GPIOB
#define DD0_Pin GPIO_PIN_1
#define DD0_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
