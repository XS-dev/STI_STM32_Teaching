// ADC ��ͨ���ɼ�

#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[100];

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
	// ���ô���
	USART_Config();
	
	// ADC ��ʼ��
	ADCx_Init();
	
	printf("\r\n ----����һ��ADC��ͨ��DMA��ȡʵ��----\r\n");
	
	while (1)
	{
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue[29]/4096*3.3; // ��ȡת����ADֵ
	
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue[29]); 
		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 

		Delay(0xffffee);  
	}
}
/*********************************************END OF FILE**********************/

