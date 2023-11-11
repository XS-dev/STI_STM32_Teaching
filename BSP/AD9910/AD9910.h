#ifndef __AD9910_H__
#define __AD9910_H__
#include "main.h"

#define uchar 	uint32_t
#define uint  	uint32_t	
#define ulong  	uint32_t		


//#define CSB_Pin GPIO_PIN_6
//#define CSB_GPIO_Port GPIOA
//#define DRH_Pin GPIO_PIN_7
//#define DRH_GPIO_Port GPIOA
//#define SCK_Pin GPIO_PIN_4
//#define SCK_GPIO_Port GPIOC
//#define UPDATE_Pin GPIO_PIN_5
//#define UPDATE_GPIO_Port GPIOC
//#define SDIO_Pin GPIO_PIN_0
//#define SDIO_GPIO_Port GPIOB
//#define DRC_Pin GPIO_PIN_2
//#define DRC_GPIO_Port GPIOB
//#define PF0_Pin GPIO_PIN_10
//#define PF0_GPIO_Port GPIOE
//#define PF1_Pin GPIO_PIN_11
//#define PF1_GPIO_Port GPIOE
//#define PF2_Pin GPIO_PIN_12
//#define PF2_GPIO_Port GPIOE
//#define RSO_Pin GPIO_PIN_13
//#define RSO_GPIO_Port GPIOE
//#define PLL_Pin GPIO_PIN_14
//#define PLL_GPIO_Port GPIOE
//#define RST_Pin GPIO_PIN_10
//#define RST_GPIO_Port GPIOB

#define AD9910_SDIO_H	HAL_GPIO_WritePin(SDIO_GPIO_Port,	SDIO_Pin,	GPIO_PIN_SET);	
#define DRHOLD_H 		HAL_GPIO_WritePin(DRH_GPIO_Port,	DRH_Pin,	GPIO_PIN_SET);		  		  
#define UP_DAT_H 		HAL_GPIO_WritePin(UPDATE_GPIO_Port,	UPDATE_Pin,	GPIO_PIN_SET);	   
#define PROFILE1_H		HAL_GPIO_WritePin(PF1_GPIO_Port,	PF1_Pin,	GPIO_PIN_SET);  	 
#define MAS_REST_H 		HAL_GPIO_WritePin(RST_GPIO_Port,	RST_Pin,	GPIO_PIN_SET);	 
#define SCLK_H 			HAL_GPIO_WritePin(SCK_GPIO_Port,	SCK_Pin,	GPIO_PIN_SET);
#define DRCTL_H  		HAL_GPIO_WritePin(DRC_GPIO_Port,	DRC_Pin,	GPIO_PIN_SET);		  
#define PROFILE0_H		HAL_GPIO_WritePin(PF0_GPIO_Port,	PF0_Pin,	GPIO_PIN_SET);  	 
#define PROFILE2_H 		HAL_GPIO_WritePin(PF2_GPIO_Port,	PF2_Pin,	GPIO_PIN_SET);	 
#define CS_H			HAL_GPIO_WritePin(CSB_GPIO_Port,	CSB_Pin,	GPIO_PIN_SET);	

#define AD9910_SDIO_L	HAL_GPIO_WritePin(SDIO_GPIO_Port,	SDIO_Pin,	GPIO_PIN_RESET);	
#define DRHOLD_L 		HAL_GPIO_WritePin(DRH_GPIO_Port,	DRH_Pin,	GPIO_PIN_RESET);		  		  
#define UP_DAT_L 		HAL_GPIO_WritePin(UPDATE_GPIO_Port,	UPDATE_Pin,	GPIO_PIN_RESET);	   
#define PROFILE1_L		HAL_GPIO_WritePin(PF1_GPIO_Port,	PF1_Pin,	GPIO_PIN_RESET);  	 
#define MAS_REST_L 		HAL_GPIO_WritePin(RST_GPIO_Port,	RST_Pin,	GPIO_PIN_RESET);	 
#define SCLK_L 			HAL_GPIO_WritePin(SCK_GPIO_Port,	SCK_Pin,	GPIO_PIN_RESET);
#define DRCTL_L  		HAL_GPIO_WritePin(DRC_GPIO_Port,	DRC_Pin,	GPIO_PIN_RESET);		  
#define PROFILE0_L		HAL_GPIO_WritePin(PF0_GPIO_Port,	PF0_Pin,	GPIO_PIN_RESET);  	 
#define PROFILE2_L 		HAL_GPIO_WritePin(PF2_GPIO_Port,	PF2_Pin,	GPIO_PIN_RESET);	 
#define CS_L 			HAL_GPIO_WritePin(CSB_GPIO_Port,	CSB_Pin,	GPIO_PIN_RESET);		 			     

#define PI 3.1415926         


void Init_ad9910(void);
void Freq_convert(ulong Freq);										//дƵ��

//void Write_Amplitude(bit Channel,unsigned int Amplitude);	//д����

void txd_8bit(uchar txdat);
void TxCFR(void);
void Txprofile(void);

void Freq_convert_profile0(ulong Freq);
void Freq_convert_profile1(ulong Freq);
void Freq_convert_profile2(ulong Freq);
void Freq_convert_profile3(ulong Freq);
void Freq_convert_profile4(ulong Freq);
void Freq_convert_profile5(ulong Freq);
void Freq_convert_profile6(ulong Freq);
void Freq_convert_profile7(ulong Freq);

void scan8channel(void);
void Write_Amplitude(uint Amp); //д���ȣ����뷶Χ��1-650 mV

//ɨƵ������Ƶ�ʣ�����Ƶ�ʣ�Ƶ�ʲ�������λ��Hz��������ʱ��������λ��ns����Χ��4*(1~65536)ns��
void SweepFre(ulong SweepMinFre, ulong SweepMaxFre, ulong SweepStepFre, ulong SweepTime);

void Square_wave(uint Sample_interval);//����������ʱ�������뷶Χ��4*(1~65536)ns


void txd_32bit(uint32_t dat);

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_DRG_Fre_Init(void)
//��������:AD9910������б��ģʽDRG��ʼ��------------------Ƶ��
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_DRG_Fre_Init(void);

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_DRG_Freq_set(uint32_t upper_limit , uint32_t lower_limit ,uint32_t dec_step , uint32_t inc_step , uint16_t neg_rate ,uint16_t pos_rate)
//��������:AD9910��DRG����------------------Ƶ��
//��ڲ���:		upper_limit										����Ƶ��							1Hz---450M
//						lower_limit										����Ƶ��							1Hz---450M       (����Ƶ��Ҫ��������Ƶ��)
//						dec_step											Ƶ�ʼӲ���						1Hz---450M					
//						inc_step											Ƶ�ʼ�����						1Hz---450M
//						neg_rate											Ƶ�ʼӵ�����(ʱ��)	0x0000----0xffff			  
//						pos_rate											Ƶ�ʼ�������(ʱ��)	0x0000----0xffff
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_DRG_Freq_set(uint32_t upper_limit , uint32_t lower_limit ,uint32_t dec_step , uint32_t inc_step , uint16_t neg_rate ,uint16_t pos_rate);
//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_Init(void)
//��������:��CFR1��CFR2�ָ�Ĭ��ֵ
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_Init(void);

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_ZB_Fre_Init(void)
//��������:����RAMģʽ�е��ز���Ƶ�ʵĳ�ʼ��
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_ZB_Fre_Init(void);


//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_ZB_Fre_Set(uint32_t Freq)
//��������:����RAMģʽ�е��ز���Ƶ��
//��ڲ���:Freq--------------------�ز�Ƶ��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_ZB_Fre_Set(uint32_t Freq);


void FSK_RAM_Write(void);


void FM_RAM_Write(uint32_t modin,uint32_t deepth, uint32_t carrer);

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_ramdata_W(void)
//��������:������д��1024*32��RAM��---------------------------Ƶ��
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_ramdata_W(void);


//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_AMP_W(void)
//��������:������д��1024*32��RAM��-------------------------����
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_AMP_W(void);

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_WAVE_RAM_AMP_W(int mode)
//��������:������д��1024*32��RAM��-------------------------����
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_WAVE_RAM_AMP_W(int mode);

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_DIR_Fre_R(void)
//��������:ֱ��ת��ģʽ�Ļط�-------------------------Ƶ��
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_DIR_Fre_R(void);


//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_DIR_AMP_R(void)
//��������:ֱ��ת��ģʽ�Ļط�-------------------------����
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_DIR_AMP_R(void);


//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_RAMP_UP_ONE_Fre_R(void)
//��������:��б��ģʽ�Ļط�-------------------------Ƶ��
//														ONE �������ⲿ����PRO2~PRO0����
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_ONE_Fre_R(void);

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_RAMP_UP_ONE_AMP_R(void)
//��������:��б��ģʽ�Ļط�-------------------------����
//														ONE �������ⲿ����PRO2~PRO0����
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_ONE_AMP_R(void);


//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_RAMP_UP_TWO_Fre_R(void)
//��������:��б��ģʽ�Ļط�-------------------------Ƶ��
//														TWO �������ڲ�����							����λΪ��CFR1[20:17]�� �ο������ֲ�
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_TWO_Fre_R(void);


//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_RAMP_UP_TWO_AMP_R(void)
//��������:��б��ģʽ�Ļط�-------------------------����
//														TWO �������ڲ�����							����λΪ��CFR1[20:17]�� �ο������ֲ�
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_TWO_AMP_R(void);

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_CON_RECIR_Fre_R(void)
//��������:����ѭ��ģʽ�Ļط�-------------------------Ƶ��
//														
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_CON_RECIR_Fre_R(void);


//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_CON_RECIR_AMP_R(void)
//��������:����ѭ��ģʽ�Ļط�-------------------------����
//														
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_CON_RECIR_AMP_R(void);


//------------------------------------------------------------------------------------
//��������:void Freq_convert(uint32_t Freq)	
//��������:AD9910д��ʼƵ��
//��ڲ���:Freq      дƵ��   Ƶ��С��450M														
//���ڲ���:��
//------------------------------------------------------------------------------------
void Freq_convert2(uint32_t Freq);


//------------------------------------------------------------------------------------
//��������:void Amp_convert(uint32_t Amp)	
//��������:AD9910д��ʼ����
//��ڲ���:Amp      д����  														
//���ڲ���:��
//------------------------------------------------------------------------------------
void Amp_convert2(uint32_t Amp);

//------------------------------------------------------------------------------------
//��������:void AD9910_Init_Sin(void)
//��������:AD9910ʱ�ӵ����ú͸���DAC���� �Լ�AD9910�������ҳ�ʼ��
//��ڲ���:��
//���ڲ���:��
//------------------------------------------------------------------------------------
void AD9910_Init_Sin(int gain);

























































#endif


