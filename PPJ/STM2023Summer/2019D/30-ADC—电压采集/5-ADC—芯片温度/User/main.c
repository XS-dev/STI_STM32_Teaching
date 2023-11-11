/**
  ******************************************************************************
  * @file    оƬ�¶�
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   оƬ�¶�����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32  ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */


// ͨ��ADC1ͨ��16��ȡоƬ�ڲ��¶ȣ���ͨ�����ڴ�ӡ�����Դ��ڵ���������ʾ

#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./temp/bsp_tempad.h"

/* ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����sram*/
extern __IO u16 ADC_ConvertedValue;


/*�������¶�ֵ*/
 u16 Current_Temp;	 

 
/* �����ʱ	*/
void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
} 


//��*��ע�����
//��ʵ���������оƬ�¶ȣ�һ�������Ҫ��

/*
 * ��������main
 * ����  ��������
 * ����  : ��
 * ���  ����
 */
int main(void)
{		 
	USART_Config();

	Temp_ADC1_Init();

	printf("\r\n ����һ���ڲ��¶ȴ�����ʵ�� \r\n");
	printf( "\r\n Print current Temperature  \r\n");	

  while (1)
  { 

	Delay(0xffffee);      // ��ʱ 
	
	//���㷽���ο���STM32�����ֲᡷ
	//���㷽��1            	                 									  
 	 //Current_Temp= (1.43- ADC_ConvertedValue*3.3/4096)*1000 / 4.3+ 25 ;
	
	//���㷽��2
	Current_Temp=(V25-ADC_ConvertedValue)/AVG_SLOPE+25;	

	//10������ʾ
	printf("\r\n The IC current tem= %3d ��\r\n", Current_Temp);	      
 	 
	//16������ʾ 						 
 	// printf("\r\n The current temperature= %04x \r\n", Current_Temp);		 
  }
}

