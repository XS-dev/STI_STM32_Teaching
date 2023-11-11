#include "main.h"

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[1024] = {0};
float wave_show[1024] = {0};
float Input[480] = {0};
float Output[480] = {0};

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	float test = 0;

	USART_Config();
	JD_GPIO_Init();
	SysTick_Delay_Ms(5);
	ADCx_GPIO_Config();
	SysTick_Init();
	AD9833_Init();
	Key_GPIO_Config();
	//printf("\r\n START \r\n");
	show_delta();
	LED_GPIO_Config();
	AD9833_SetWaveData(1000,0);
	clean_wave();

//	for(int maga = 0; maga < 1; maga++)
//	{

//		oneKgain();
//		test=singlesaopin(ADC_CHANNEL2,0x07,1000);
//		printf("%f\r\n",test);
//	}

	for(int temp = 0;temp <10;temp++)
	{
		outputResistor();
	}





}
/*********************************************END OF FILE**********************/
