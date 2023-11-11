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
#include "gpio.h"




#include <stdio.h>
#include "math.h"
#include "stdlib.h"	
#include <stdbool.h>
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
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define D10_CSB_Pin GPIO_PIN_9
#define D10_CSB_GPIO_Port GPIOE
#define D10_PF2_Pin GPIO_PIN_10
#define D10_PF2_GPIO_Port GPIOE
#define D10_PF0_Pin GPIO_PIN_11
#define D10_PF0_GPIO_Port GPIOE
#define D10_OSK_Pin GPIO_PIN_12
#define D10_OSK_GPIO_Port GPIOE
#define D10_DRC_Pin GPIO_PIN_13
#define D10_DRC_GPIO_Port GPIOE
#define D10_SCK_Pin GPIO_PIN_14
#define D10_SCK_GPIO_Port GPIOE
#define D10_RST_Pin GPIO_PIN_15
#define D10_RST_GPIO_Port GPIOE
#define D10_PF1_Pin GPIO_PIN_10
#define D10_PF1_GPIO_Port GPIOB
#define D10_IOUP_Pin GPIO_PIN_11
#define D10_IOUP_GPIO_Port GPIOB
#define D10_DRO_Pin GPIO_PIN_12
#define D10_DRO_GPIO_Port GPIOB
#define D10_DPH_Pin GPIO_PIN_13
#define D10_DPH_GPIO_Port GPIOB
#define D10_SDIO_Pin GPIO_PIN_14
#define D10_SDIO_GPIO_Port GPIOB
#define D10_PWR_Pin GPIO_PIN_15
#define D10_PWR_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
