#ifndef __HC595_H
#define __HC595_H

#include "main.h"

#define HC595_SCLK_Pin GPIO_PIN_3
#define HC595_SCLK_GPIO_Port GPIOA
#define HC595_RCLK_Pin GPIO_PIN_7
#define HC595_RCLK_GPIO_Port GPIOA
#define HC595_DIO_Pin GPIO_PIN_1
#define HC595_DIO_GPIO_Port GPIOB

#define HC595_DIO_H     HAL_GPIO_WritePin(HC595_DIO_GPIO_Port,	HC595_DIO_Pin,	GPIO_PIN_SET);		//������������
#define HC595_RCLK_H    HAL_GPIO_WritePin(HC595_RCLK_GPIO_Port,	HC595_RCLK_Pin,	GPIO_PIN_SET);	   //�洢�Ĵ��� ��������ź�(��������Ч)
#define HC595_SCLK_H    HAL_GPIO_WritePin(HC595_SCLK_GPIO_Port,	HC595_SCLK_Pin,	GPIO_PIN_SET); 	   //��λ�Ĵ��� ʱ�������ź�(��������Ч)


#define HC595_DIO_L     HAL_GPIO_WritePin(HC595_DIO_GPIO_Port,	HC595_DIO_Pin,	GPIO_PIN_RESET);		//������������
#define HC595_RCLK_L    HAL_GPIO_WritePin(HC595_RCLK_GPIO_Port,	HC595_RCLK_Pin,	GPIO_PIN_RESET);	   //�洢�Ĵ��� ��������ź�(��������Ч)
#define HC595_SCLK_L    HAL_GPIO_WritePin(HC595_SCLK_GPIO_Port,	HC595_SCLK_Pin,	GPIO_PIN_RESET); 	   //��λ�Ĵ��� ʱ�������ź�(��������Ч)



extern uint16_t LED_table[18];
extern uint16_t wei_table[8] ;

void HC595_Init(void);

void LED8_Display(uint16_t x,uint16_t y);

void LED_OUT(uint16_t outdata);

#endif