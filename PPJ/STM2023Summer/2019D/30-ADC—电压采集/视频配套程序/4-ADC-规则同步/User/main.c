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


extern __IO uint32_t ADC_ConvertedValue[NOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal[NOFCHANEL*2]={0,0};        

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
  uint16_t temp0=0 ,temp1=0;
	/*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	printf("��ӭʹ�ñ���STM32������\n\n\n\n");
	
	ADCx_Init();
	while (1)
	{	
    // ȡ��ADC1���ݼĴ����ĸ�16λ�������ADC2��ת������
		temp0 = (ADC_ConvertedValue[0]&0XFFFF0000) >> 16;
		// ȡ��ADC1���ݼĴ����ĵ�16λ�������ADC1��ת������
		temp1 = (ADC_ConvertedValue[0]&0XFFFF);	
		
		ADC_ConvertedValueLocal[0] =(float) temp0/4096*3.3;
		ADC_ConvertedValueLocal[1] =(float) temp1/4096*3.3;
		
		printf("\r\n ADCx_1 value = %f V \r\n",ADC_ConvertedValueLocal[1]);
		printf("\r\n ADCx_2 value = %f V \r\n",ADC_ConvertedValueLocal[0]);
		
		printf("\r\n\r\n");
		Delay(0xffffee); 
		 
	}

}

// ��ҵ

// �ѳ���ĳ�˫ģʽ�Ķ�ͨ��



/*********************************************END OF FILE**********************/
