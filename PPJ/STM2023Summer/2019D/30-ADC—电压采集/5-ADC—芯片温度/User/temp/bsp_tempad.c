/**
  ******************************************************************************
  * @file    bsp_tempad.c
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ��ȡоƬ�¶�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

//�¶ȴ��������ڲ���ADC1_IN16����ͨ�������ӣ�
#include "./temp/bsp_tempad.h"

//ADC1_BASE��ַ��0x4000 0000+0x2400 ��ADC1�Ļ���ַ�������Ĺ������ݼĴ�����ƫ�Ƶ�ַ�ǣ�0x4c
#define ADC1_DR_Address    ((u32)ADC1_BASE+0x4c)

__IO u16 ADC_ConvertedValue;
//__IO u16 ADC_ConvertedValueLocal;


/*
 * ��������ADC1_GPIO_Config
 * ����  ��ʹ��ADC1��DMA1��ʱ��
 * ����  :��
 * ���  ����
 * ����  ���ڲ�����
 */
static void ADC1_GPIO_Config(void)		       
{

	/* Enable DMA clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	/* Enable ADC1 and GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

 }


/* ��������ADC1_Mode_Config
 * ����  ������ADC1�Ĺ���ģʽΪMDAģʽ
 * ����  : ��
 * ���  ����
 * ����  ���ڲ�����
 */
static void ADC1_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	/* DMA channel1 configuration */
		   
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;		        // �������ַ
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;	        // ADת��ֵ����ŵ��ڴ����ַ	�����Ǹ�����ַ��
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                        // ������Ϊ���ݴ������Դ	
  DMA_InitStructure.DMA_BufferSize = 1;                                     // ����ָ��DMAͨ�� DMA����Ĵ�С
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;          // �����ַ�Ĵ�������
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;			        // �ڴ��ַ�Ĵ�������
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // ���ݿ��Ϊ16λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         // HalfWord
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		                    //������ѭ��ģʽ��
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;	                    //�����ȼ�
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;		                        //û������Ϊ�ڴ浽�ڴ�Ĵ���
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);											//ENABLE��

  /* ADC1 configuration */
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                        //��������ģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;			                    //��ͨ��
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;			            //����ת��
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;       //�������������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					//Right
  ADC_InitStructure.ADC_NbrOfChannel = 1;				                    //��һ��ͨ��ת��
  ADC_Init(ADC1, &ADC_InitStructure);
	
  	/*����ADCʱ�ӣ�ΪPCLK2��8��Ƶ����9Hz*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 

  /* ADC1 regular channel16 configuration */ 
  //���ò���ͨ��IN16, ���ò���ʱ��
  ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);	

  //ʹ���¶ȴ��������ڲ��ο���ѹ   
  ADC_TempSensorVrefintCmd(ENABLE);                                    

   /* Enable ADC1 DMA */	  
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibaration register */   
  ADC_ResetCalibration(ADC1);			                              
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));                         

  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);				                        
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));	  
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}												

/*
 * ��������Temp_ADC1_Init
 * ����  ����
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void Temp_ADC1_Init(void)
{
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
}
