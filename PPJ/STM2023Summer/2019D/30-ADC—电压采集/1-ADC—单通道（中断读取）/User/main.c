
// ADC ��ͨ���ɼ�����ʹ��DMA��һ��ֻ��ADC2������ʹ�ã���ΪADC2����ʹ��DMA

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
	// ���ô���
	USART_Config();
	
	// ADC ��ʼ��
	ADCx_Init();
	
	printf("\r\n ----����һ��ADC��ͨ���ж϶�ȡʵ��----\r\n");
	
	while (1)
	{
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; 
	
		printf("\r\n The current AD value = 0x%04X \r\n", 
		       ADC_ConvertedValue); 
		printf("\r\n The current AD value = %f V \r\n",
		       ADC_ConvertedValueLocal); 
		printf("\r\n\r\n");

		Delay(0xffffee);  
	}
}
/*********************************************END OF FILE**********************/
