#include "xadc.h"

////由于不可知原因，需要在写在main函数中
//ALIGN_32BYTES (uint16_t adc1_data[FFT_LENGTH]) 	__attribute__((section(".ARM.__at_0x30000000")));
//__IO uint8_t AdcConvEnd = 0;//表示adc采集完成


//void adc_init(void)
//{
//	HAL_ADC_DeInit(&hadc1);
//    MX_ADC1_Init();	//初始化调用放这里, 确保在MX_DMA_Init()初始化后面    
//    HAL_Delay(100);	//有地方说这里可以等等电压稳定后再校准

//    if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
//    {
//        printf("hadc1 error with HAL_ADCEx_Calibration_Start\r\n");
//        Error_Handler();
//    }

//    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc1_data, ADC1_BUFFER_SIZE) != HAL_OK)
//    {
//        printf("hadc1 error with HAL_ADC_Start_DMA\r\n");
//        Error_Handler();
//    }

//		HAL_TIM_Base_Start(&htim15);
//		while (!AdcConvEnd);
//		AdcConvEnd = 0;
//}
