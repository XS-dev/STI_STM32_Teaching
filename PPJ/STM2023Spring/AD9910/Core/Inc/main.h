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
#include "stdint.h"
#include "stdio.h"
#include "math.h"

#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "AD9910.h"
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
#define CSB_Pin GPIO_PIN_6
#define CSB_GPIO_Port GPIOA
#define DRH_Pin GPIO_PIN_7
#define DRH_GPIO_Port GPIOA
#define SCK_Pin GPIO_PIN_4
#define SCK_GPIO_Port GPIOC
#define UPDATE_Pin GPIO_PIN_5
#define UPDATE_GPIO_Port GPIOC
#define SDIO_Pin GPIO_PIN_0
#define SDIO_GPIO_Port GPIOB
#define DRC_Pin GPIO_PIN_2
#define DRC_GPIO_Port GPIOB
#define PF0_Pin GPIO_PIN_10
#define PF0_GPIO_Port GPIOE
#define PF1_Pin GPIO_PIN_11
#define PF1_GPIO_Port GPIOE
#define PF2_Pin GPIO_PIN_12
#define PF2_GPIO_Port GPIOE
#define RSO_Pin GPIO_PIN_13
#define RSO_GPIO_Port GPIOE
#define PLL_Pin GPIO_PIN_14
#define PLL_GPIO_Port GPIOE
#define RST_Pin GPIO_PIN_10
#define RST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
