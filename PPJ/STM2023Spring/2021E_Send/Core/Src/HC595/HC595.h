#ifndef __HC595_H
#define __HC595_H

#include "main.h"

#define HC595_SCLK_Pin GPIO_PIN_3
#define HC595_SCLK_GPIO_Port GPIOA
#define HC595_RCLK_Pin GPIO_PIN_7
#define HC595_RCLK_GPIO_Port GPIOA
#define HC595_DIO_Pin GPIO_PIN_1
#define HC595_DIO_GPIO_Port GPIOB

#define HC595_DIO_H     HAL_GPIO_WritePin(HC595_DIO_GPIO_Port,	HC595_DIO_Pin,	GPIO_PIN_SET);		//串行数据输入
#define HC595_RCLK_H    HAL_GPIO_WritePin(HC595_RCLK_GPIO_Port,	HC595_RCLK_Pin,	GPIO_PIN_SET);	   //存储寄存器 锁存控制信号(上升沿有效)
#define HC595_SCLK_H    HAL_GPIO_WritePin(HC595_SCLK_GPIO_Port,	HC595_SCLK_Pin,	GPIO_PIN_SET); 	   //移位寄存器 时钟脉冲信号(上升沿有效)


#define HC595_DIO_L     HAL_GPIO_WritePin(HC595_DIO_GPIO_Port,	HC595_DIO_Pin,	GPIO_PIN_RESET);		//串行数据输入
#define HC595_RCLK_L    HAL_GPIO_WritePin(HC595_RCLK_GPIO_Port,	HC595_RCLK_Pin,	GPIO_PIN_RESET);	   //存储寄存器 锁存控制信号(上升沿有效)
#define HC595_SCLK_L    HAL_GPIO_WritePin(HC595_SCLK_GPIO_Port,	HC595_SCLK_Pin,	GPIO_PIN_RESET); 	   //移位寄存器 时钟脉冲信号(上升沿有效)



extern uint16_t LED_table[18];
extern uint16_t wei_table[8] ;

void HC595_Init(void);

void LED8_Display(uint16_t x,uint16_t y);

void LED_OUT(uint16_t outdata);

#endif