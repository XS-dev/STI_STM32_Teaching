#include "xadc.h"

////���ڲ���֪ԭ����Ҫ��д��main������
//ALIGN_32BYTES (uint16_t adc1_data[FFT_LENGTH]) 	__attribute__((section(".ARM.__at_0x30000000")));
//__IO uint8_t AdcConvEnd = 0;//��ʾadc�ɼ����


//void adc_init(void)
//{
//	HAL_ADC_DeInit(&hadc1);
//    MX_ADC1_Init();	//��ʼ�����÷�����, ȷ����MX_DMA_Init()��ʼ������    
//    HAL_Delay(100);	//�еط�˵������Եȵȵ�ѹ�ȶ�����У׼

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
