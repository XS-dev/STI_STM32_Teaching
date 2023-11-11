#include "bsp_adc.h"

__IO uint32_t ADC_ConvertedValue[NOFCHANEL] = {0};

/**
  * @brief  ADC GPIO ��ʼ��
  * @param  ��
  * @retval ��
  */
static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// ADCx_1 GPIO ��ʼ��
	ADCx_1_GPIO_APBxClock_FUN ( ADCx_1_GPIO_CLK, ENABLE );
	GPIO_InitStructure.GPIO_Pin = ADCx_1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADCx_1_PORT, &GPIO_InitStructure);

	// ADCx_2 GPIO ��ʼ��
	ADCx_1_GPIO_APBxClock_FUN ( ADCx_2_GPIO_CLK, ENABLE );
	GPIO_InitStructure.GPIO_Pin = ADCx_2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADCx_2_PORT, &GPIO_InitStructure);	
}

/**
  * @brief  ����ADC����ģʽ
  * @param  ��
  * @retval ��
  */
static void ADCx_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	// ��DMAʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	// ��ADCʱ��
	ADCx_1_APBxClock_FUN ( ADCx_1_CLK, ENABLE );
	ADCx_2_APBxClock_FUN ( ADCx_2_CLK, ENABLE );
	
  /* ------------------DMAģʽ����---------------- */	
	// ��λDMA������
	DMA_DeInit(ADC_DMA_CHANNEL);	
	// ���� DMA ��ʼ���ṹ��
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&( ADCx_1->DR ));	
	// �洢����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertedValue;	
	// ����Դ��������
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	
	// ��������С��Ӧ�õ�������Ŀ�ĵصĴ�С
	DMA_InitStructure.DMA_BufferSize = NOFCHANEL;	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// �洢����ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 	
	// �������ݴ�С
	DMA_InitStructure.DMA_PeripheralDataSize = 
	                                  DMA_PeripheralDataSize_Word;	
	// �ڴ����ݴ�С�����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;	
	// ��ֹ�洢�����洢��ģʽ����Ϊ�Ǵ����赽�洢��
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	
	// ��ʼ��DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);	
	// ʹ�� DMA ͨ��
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	/* ----------------ADCx_1 ģʽ����--------------------- */
	// ˫ADC�Ĺ���ͬ��
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;	
	// ɨ��ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 
	// ����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	// �����ⲿ����ת���������������
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	// ת������Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	// ת��ͨ������
	ADC_InitStructure.ADC_NbrOfChannel = NOFCHANEL;			
	// ��ʼ��ADC
	ADC_Init(ADCx_1, &ADC_InitStructure);	
	// ����ADCʱ�ӣΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	
	// ����ADC ͨ����ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADCx_1, ADCx_1_CHANNEL, 1, 
	                         ADC_SampleTime_239Cycles5);	
	// ʹ��ADC DMA ����
	ADC_DMACmd(ADCx_1, ENABLE);
	
	
		/* ----------------ADCx_2 ģʽ����--------------------- */
	// ˫ADC�Ĺ���ͬ��
	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;	
	// ɨ��ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 
	// ����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	// �����ⲿ����ת���������������
	ADC_InitStructure.ADC_ExternalTrigConv = 
	                           ADC_ExternalTrigConv_None;
	// ת������Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	// ת��ͨ������
	ADC_InitStructure.ADC_NbrOfChannel = NOFCHANEL;			
	// ��ʼ��ADC
	ADC_Init(ADCx_2, &ADC_InitStructure);	
	// ����ADCʱ��ΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	
	// ����ADC ͨ����ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADCx_2, ADCx_2_CHANNEL, 1, 
	                         ADC_SampleTime_239Cycles5);
	/* ʹ��ADCx_2���ⲿ����ת�� */
  ADC_ExternalTrigConvCmd(ADC2, ENABLE);
	
	/* ----------------ADCx_1 У׼--------------------- */
	// ����ADC ������ʼת��
	ADC_Cmd(ADCx_1, ENABLE);	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADCx_1);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADCx_1));	
	// ADC��ʼУ׼
	ADC_StartCalibration(ADCx_1);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADCx_1));
	
  /* ----------------ADCx_2 У׼--------------------- */
		// ����ADC ������ʼת��
	ADC_Cmd(ADCx_2, ENABLE);	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADCx_2);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADCx_2));	
	// ADC��ʼУ׼
	ADC_StartCalibration(ADCx_2);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADCx_2));

	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	ADC_SoftwareStartConvCmd(ADCx_1, ENABLE);
}

/**
  * @brief  ADC��ʼ��
  * @param  ��
  * @retval ��
  */
void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
}
/*********************************************END OF FILE**********************/
