#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

// ˫ģʽʱ��ADC1��ADC2ת�������ݶ������ADC1�����ݼĴ�����
// ADC1���ڵ�ʮ��λ��ADC2���ڸ�ʮ��λ
// ˫ADCģʽ�ĵ�һ��ADC��������ADC1
#define    ADCx_1                           ADC1
#define    ADCx_1_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADCx_1_CLK                       RCC_APB2Periph_ADC1

#define    ADCx_1_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADCx_1_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADCx_1_PORT                      GPIOC
#define    ADCx_1_PIN                       GPIO_Pin_1
#define    ADCx_1_CHANNEL                   ADC_Channel_11

// ˫ADCģʽ�ĵڶ���ADC��������ADC2
#define    ADCx_2                           ADC2
#define    ADCx_2_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADCx_2_CLK                       RCC_APB2Periph_ADC2

#define    ADCx_2_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADCx_2_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADCx_2_PORT                      GPIOC
#define    ADCx_2_PIN                       GPIO_Pin_4
#define    ADCx_2_CHANNEL                 ADC_Channel_14

#define    NOFCHANEL                        1

// ADC1 ��Ӧ DMA1ͨ��1��ADC3��ӦDMA2ͨ��5��ADC2û��DMA����
#define    ADC_DMA_CHANNEL               DMA1_Channel1


void ADCx_Init(void);


#endif /* __ADC_H */

