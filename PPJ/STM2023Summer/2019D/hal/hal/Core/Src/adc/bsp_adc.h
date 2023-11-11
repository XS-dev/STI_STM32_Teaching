#ifndef __BSP_ADC_H
#define	__BSP_ADC_H

#include "stm32f4xx.h"

#define RHEOSTAT_NOFCHANEL      1024

/*=====================ͨ��1 IO======================*/
// PC3 ͨ����ñ�ӵ�λ��
// ADC IO�궨��
#define RHEOSTAT_ADC_GPIO_PORT1             GPIOC
#define RHEOSTAT_ADC_GPIO_PIN1              GPIO_PIN_0
#define RHEOSTAT_ADC_GPIO_CLK1_ENABLE()     __GPIOB_CLK_ENABLE()
#define RHEOSTAT_ADC_CHANNEL1               ADC_CHANNEL_10
#define	ADC_CHANNEL1		ADC_CHANNEL_10
/*=====================ͨ��2 IO ======================*/
// PA4 ͨ����ñ�ӹ�������
// ADC IO�궨��
#define RHEOSTAT_ADC_GPIO_PORT2             GPIOC
#define RHEOSTAT_ADC_GPIO_PIN2              GPIO_PIN_2
#define RHEOSTAT_ADC_GPIO_CLK2_ENABLE()     __GPIOB_CLK_ENABLE()
#define RHEOSTAT_ADC_CHANNEL2               ADC_CHANNEL_12
#define	ADC_CHANNEL2		ADC_CHANNEL_12
   
// ADC ��ź궨��
#define RHEOSTAT_ADC                        ADC1
#define RHEOSTAT_ADC_CLK_ENABLE()           __ADC1_CLK_ENABLE()

// ADC DR�Ĵ����궨�壬ADCת���������ֵ����������
#define RHEOSTAT_ADC_DR_ADDR                ((uint32_t)ADC1+0x4c)

// ADC DMA ͨ���궨�壬��������ʹ��DMA����
#define RHEOSTAT_ADC_DMA_CLK_ENABLE()       __DMA2_CLK_ENABLE()
#define RHEOSTAT_ADC_DMA_CHANNEL            DMA_CHANNEL_0
#define RHEOSTAT_ADC_DMA_STREAM             DMA2_Stream0

extern uint16_t ADC_ConvertedValue[RHEOSTAT_NOFCHANEL];

//ADC_SAMPLETIME_3CYCLES  
//ADC_SAMPLETIME_15CYCLES 
//ADC_SAMPLETIME_28CYCLES 
//ADC_SAMPLETIME_56CYCLES 
//ADC_SAMPLETIME_84CYCLES 
//ADC_SAMPLETIME_112CYCLES
//ADC_SAMPLETIME_144CYCLES
//ADC_SAMPLETIME_480CYCLES
void Rheostat_ADC_GPIO_Config(void);
void ADCx_Init(uint8_t channel,uint8_t fre,int maga);

#endif /* __BSP_ADC_H */



