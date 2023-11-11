#include "bsp_adc.h"

uint16_t ADC_ConvertedValue[RHEOSTAT_NOFCHANEL]={0};
DMA_HandleTypeDef DMA_Init_Handle;
ADC_HandleTypeDef ADC_Handle;
ADC_ChannelConfTypeDef ADC_Config;

void Rheostat_ADC_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /*=====================ͨ��1======================*/
    // ʹ�� GPIO ʱ��
    RHEOSTAT_ADC_GPIO_CLK1_ENABLE();    
    // ���� IO
    GPIO_InitStructure.Pin = RHEOSTAT_ADC_GPIO_PIN1;
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;	    
    GPIO_InitStructure.Pull = GPIO_NOPULL ; //������������
    HAL_GPIO_Init(RHEOSTAT_ADC_GPIO_PORT1, &GPIO_InitStructure);
    
    /*=====================ͨ��2======================*/
    // ʹ�� GPIO ʱ��
    RHEOSTAT_ADC_GPIO_CLK2_ENABLE();    
    // ���� IO
    GPIO_InitStructure.Pin = RHEOSTAT_ADC_GPIO_PIN2;
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;	    
    GPIO_InitStructure.Pull = GPIO_NOPULL ; //������������
    HAL_GPIO_Init(RHEOSTAT_ADC_GPIO_PORT2, &GPIO_InitStructure);
     
}

void ADCx_Mode_Config(uint8_t channel,uint8_t fre,int maga)
{

    // ------------------DMA Init �ṹ����� ��ʼ��--------------------------
    // ADC1ʹ��DMA2��������0��ͨ��0��������ֲ�̶�����
    // ����DMAʱ��
    RHEOSTAT_ADC_DMA_CLK_ENABLE();
    // ���ݴ���ͨ��
    DMA_Init_Handle.Instance = RHEOSTAT_ADC_DMA_STREAM;
    // ���ݴ��䷽��Ϊ���赽�洢��	
    DMA_Init_Handle.Init.Direction = DMA_PERIPH_TO_MEMORY;	
    // ����Ĵ���ֻ��һ������ַ���õ���
    DMA_Init_Handle.Init.PeriphInc = DMA_PINC_DISABLE;
    // �洢����ַ�̶�
    DMA_Init_Handle.Init.MemInc = DMA_MINC_ENABLE; 
    // // �������ݴ�СΪ���֣��������ֽ� 
    DMA_Init_Handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD; 
    //	�洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
    DMA_Init_Handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;	
    // ѭ������ģʽ
    DMA_Init_Handle.Init.Mode = DMA_NORMAL;
    // DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
    DMA_Init_Handle.Init.Priority = DMA_PRIORITY_HIGH;
    // ��ֹDMA FIFO	��ʹ��ֱ��ģʽ
    DMA_Init_Handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;  
//    // FIFO ��С��FIFOģʽ��ֹʱ�������������	
//    DMA_Init_Handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
//    DMA_Init_Handle.Init.MemBurst = DMA_MBURST_SINGLE;
//    DMA_Init_Handle.Init.PeriphBurst = DMA_PBURST_SINGLE;  
    // ѡ�� DMA ͨ����ͨ������������
    DMA_Init_Handle.Init.Channel = RHEOSTAT_ADC_DMA_CHANNEL; 
    //��ʼ��DMA�������൱��һ����Ĺܵ����ܵ������кܶ�ͨ��
    HAL_DMA_Init(&DMA_Init_Handle); 

    HAL_DMA_Start (&DMA_Init_Handle,RHEOSTAT_ADC_DR_ADDR,(uint32_t)&ADC_ConvertedValue,maga);

    // ����ADCʱ��
    RHEOSTAT_ADC_CLK_ENABLE();
    // -------------------ADC Init �ṹ�� ���� ��ʼ��------------------------
    // ADC1
    ADC_Handle.Instance = RHEOSTAT_ADC;
    // ʱ��Ϊfpclk 4��Ƶ	
    ADC_Handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
    // ADC �ֱ���
    ADC_Handle.Init.Resolution = ADC_RESOLUTION_12B;
    // ɨ��ģʽ����ͨ���ɼ�����Ҫ	
    ADC_Handle.Init.ScanConvMode = DISABLE; 
    // ����ת��	
    ADC_Handle.Init.ContinuousConvMode = ENABLE;
    // ������ת��	
    ADC_Handle.Init.DiscontinuousConvMode = DISABLE;
    // ������ת������
    ADC_Handle.Init.NbrOfDiscConversion   = 0;
    //��ֹ�ⲿ���ش���    
    ADC_Handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    //ʹ���������
    ADC_Handle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
    //�����Ҷ���	
    ADC_Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    //ת��ͨ������
    ADC_Handle.Init.NbrOfConversion = 1;
    //ʹ������ת������
    ADC_Handle.Init.DMAContinuousRequests = ENABLE;
    //ת����ɱ�־
    ADC_Handle.Init.EOCSelection          = DISABLE;    
    // ��ʼ��ADC	                          
    HAL_ADC_Init(&ADC_Handle);
    //---------------------------------------------------------------------------
    // ���� ADC ͨ��1ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ3��ʱ������
		
    ADC_Config.Channel      = channel;
    ADC_Config.Rank         = 1;    
    ADC_Config.SamplingTime = fre;// ����ʱ����	
    ADC_Config.Offset       = 0;
    HAL_ADC_ConfigChannel(&ADC_Handle, &ADC_Config);
    HAL_ADC_Start(&ADC_Handle);
//    // ���� ADC ͨ��2ת��˳��Ϊ2���ڶ���ת��������ʱ��Ϊ3��ʱ������
//    ADC_Config.Channel      = RHEOSTAT_ADC_CHANNEL2;
//    ADC_Config.Rank         = 2;

//    HAL_ADC_ConfigChannel(&ADC_Handle, &ADC_Config);
    HAL_ADC_Start_DMA(&ADC_Handle, (uint32_t*)&ADC_ConvertedValue,maga);
}



void	ADCx_Init(uint8_t channel,uint8_t fre,int maga)
{

	ADCx_Mode_Config(channel,fre,maga);
}



