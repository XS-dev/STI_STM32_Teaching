#ifndef __ADC_H
#define	__ADC_H


#include "main.h"

// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
/********************ADC1输入通道（引脚）配置**************************/
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC_PORT                      GPIOC

// 注意
// 1-PC0 在指南者里面接的是蜂鸣器，默认被拉低
// 2-PC0 在指南者里面接的是SPI FLASH的 片选，默认被拉高
// 所以 PC0 做 ADC 转换通道的时候，结果可能会有误差

// 转换通道个数
#define    NOFCHANEL										 1024

#define    ADC_PIN1                      GPIO_Pin_1
#define    ADC_CHANNEL1                  ADC_Channel_11

#define    ADC_PIN2                      GPIO_Pin_2
#define    ADC_CHANNEL2                  ADC_Channel_12//输入信号


// ADC1 对应 DMA1通道1，ADC3对应DMA2通道5，ADC2没有DMA功能
#define    ADC_x                         ADC1
#define    ADC_DMA_CHANNEL               DMA1_Channel1
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA1

// ADC1转换的电压值通过MDA方式传到SRAM
extern uint16_t ADC_ConvertedValue[1024];

/**************************函数声明********************************/
void ADCx_GPIO_Config(void);
void ADCx_Init(uint8_t channel,uint8_t fre,int maga);
void DMA_START(void);

#endif /* __ADC_H */

