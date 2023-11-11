 /*-----------------------------------------------
  名称：AD9854并口驱动
  编写：Liu
  日期：2014.3
  修改：无
  内容：
------------------------------------------------*/
#ifndef __AD9910_H__
#define __AD9910_H__

#include "main.h"

#define uchar unsigned char
#define uint  unsigned int	
#define ulong  unsigned long int

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


#define AD9910_PWR PCout(13)//0
#define	AD9910_PWR_H 	HAL_GPIO_WritePin(D10_PWR_GPIO_Port, D10_PWR_Pin, GPIO_PIN_SET);
#define	AD9910_PWR_L 	HAL_GPIO_WritePin(D10_PWR_GPIO_Port, D10_PWR_Pin, GPIO_PIN_RESET);

//原始IO
#define	AD9910_SDIO_H 	HAL_GPIO_WritePin(D10_SDIO_GPIO_Port, D10_SDIO_Pin	, GPIO_PIN_SET);
#define	AD9910_DRH_H 		HAL_GPIO_WritePin(D10_SDIO_GPIO_Port, D10_SDIO_Pin	, GPIO_PIN_SET);
#define	AD9910_DRO_H 		HAL_GPIO_WritePin(D10_SDIO_GPIO_Port, D10_SDIO_Pin	, GPIO_PIN_SET);
#define	AD9910_UP_H 		HAL_GPIO_WritePin(D10_DPH_GPIO_Port	, D10_DPH_Pin		, GPIO_PIN_SET);
#define	AD9910_PF1_H 		HAL_GPIO_WritePin(D10_DRO_GPIO_Port	, D10_DRO_Pin		, GPIO_PIN_SET);
#define	AD9910_RST_H 		HAL_GPIO_WritePin(D10_IOUP_GPIO_Port, D10_PF1_Pin		, GPIO_PIN_SET);
#define	AD9910_SCLK_H 	HAL_GPIO_WritePin(D10_SCK_GPIO_Port	, D10_SCK_Pin		, GPIO_PIN_SET);
#define	AD9910_DRC_H 		HAL_GPIO_WritePin(D10_DRC_GPIO_Port	, D10_DRC_Pin		, GPIO_PIN_SET);
#define	AD9910_OSK_H 		HAL_GPIO_WritePin(D10_OSK_GPIO_Port	, D10_OSK_Pin		, GPIO_PIN_SET);
#define	AD9910_PF0_H 		HAL_GPIO_WritePin(D10_PF0_GPIO_Port	, D10_PF0_Pin		, GPIO_PIN_SET);
#define	AD9910_PF2_H 		HAL_GPIO_WritePin(D10_PF2_GPIO_Port	, D10_PF2_Pin		, GPIO_PIN_SET);
#define	AD9910_CS_H 		HAL_GPIO_WritePin(D10_CSB_GPIO_Port	, D10_CSB_Pin		, GPIO_PIN_SET);

#define	AD9910_SDIO_L 	HAL_GPIO_WritePin(D10_SDIO_GPIO_Port, D10_SDIO_Pin	, GPIO_PIN_RESET);
#define	AD9910_DRH_L 		HAL_GPIO_WritePin(D10_SDIO_GPIO_Port, D10_SDIO_Pin	, GPIO_PIN_RESET);
#define	AD9910_DRO_L 		HAL_GPIO_WritePin(D10_SDIO_GPIO_Port, D10_SDIO_Pin	, GPIO_PIN_RESET);
#define	AD9910_UP_L 		HAL_GPIO_WritePin(D10_DPH_GPIO_Port	, D10_DPH_Pin		, GPIO_PIN_RESET);
#define	AD9910_PF1_L 		HAL_GPIO_WritePin(D10_DRO_GPIO_Port	, D10_DRO_Pin		, GPIO_PIN_RESET);
#define	AD9910_RST_L 		HAL_GPIO_WritePin(D10_IOUP_GPIO_Port, D10_PF1_Pin		, GPIO_PIN_RESET);
#define	AD9910_SCLK_L 	HAL_GPIO_WritePin(D10_SCK_GPIO_Port	, D10_SCK_Pin		, GPIO_PIN_RESET);
#define	AD9910_DRC_L 		HAL_GPIO_WritePin(D10_DRC_GPIO_Port	, D10_DRC_Pin		, GPIO_PIN_RESET);
#define	AD9910_OSK_L 		HAL_GPIO_WritePin(D10_OSK_GPIO_Port	, D10_OSK_Pin		, GPIO_PIN_RESET);
#define	AD9910_PF0_L 		HAL_GPIO_WritePin(D10_PF0_GPIO_Port	, D10_PF0_Pin		, GPIO_PIN_RESET);
#define	AD9910_PF2_L 		HAL_GPIO_WritePin(D10_PF2_GPIO_Port	, D10_PF2_Pin		, GPIO_PIN_RESET);
#define	AD9910_CS_L 		HAL_GPIO_WritePin(D10_CSB_GPIO_Port	, D10_CSB_Pin		, GPIO_PIN_RESET);
//#define AD9910_SDIO PAout(5)
//#define DRHOLD PCout(1)
//#define DROVER PCout(2)
//#define UP_DAT PCout(3)
//#define PROFILE1 PCout(10)
//#define MAS_REST PAout(6)
//#define SCLK PAout(2)
//#define DRCTL  PAout(4)
//#define OSK PCout(8)
//#define PROFILE0 PCout(4)
//#define PROFILE2 PCout(5)
//#define CS  PBout(10)

void AD9110_IOInit(void);
void Init_ad9910(void);
void Freq_convert(ulong Freq);										//写频率
void AD9910_AmpWrite(uint16_t Amp);

#endif


