/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-�Ե� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"


extern __IO uint16_t ADC_ConvertedValue;

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal;        

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	printf("��ӭʹ�ñ���STM32������\n\n\n\n");
	
	ADCx_Init();
	
  while(1)
	{	
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; 
	
		printf("\r\n The current AD value = 0x%04X \r\n",ADC_ConvertedValue); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 
		printf("\r\n\r\n");

		Delay(0xffffee); 
	}	
}

// ��ҵ

// 1-�ѳ���ĳ� ADC1/3
// 2-����������ͨ����һ��











/*********************************************END OF FILE**********************/
