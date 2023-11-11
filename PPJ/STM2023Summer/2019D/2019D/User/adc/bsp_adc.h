#ifndef __ADC_H
#define	__ADC_H


#include "main.h"

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC_PORT                      GPIOC

// ע��
// 1-PC0 ��ָ��������ӵ��Ƿ�������Ĭ�ϱ�����
// 2-PC0 ��ָ��������ӵ���SPI FLASH�� Ƭѡ��Ĭ�ϱ�����
// ���� PC0 �� ADC ת��ͨ����ʱ�򣬽�����ܻ������

// ת��ͨ������
#define    NOFCHANEL										 1024

#define    ADC_PIN1                      GPIO_Pin_1
#define    ADC_CHANNEL1                  ADC_Channel_11

#define    ADC_PIN2                      GPIO_Pin_2
#define    ADC_CHANNEL2                  ADC_Channel_12//�����ź�


// ADC1 ��Ӧ DMA1ͨ��1��ADC3��ӦDMA2ͨ��5��ADC2û��DMA����
#define    ADC_x                         ADC1
#define    ADC_DMA_CHANNEL               DMA1_Channel1
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA1

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern uint16_t ADC_ConvertedValue[1024];

/**************************��������********************************/
void ADCx_GPIO_Config(void);
void ADCx_Init(uint8_t channel,uint8_t fre,int maga);
void DMA_START(void);

#endif /* __ADC_H */

