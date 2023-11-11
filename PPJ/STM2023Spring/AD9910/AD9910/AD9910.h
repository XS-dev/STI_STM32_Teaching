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
void Freq_convert(ulong Freq);										//写频率

//void Write_Amplitude(bit Channel,unsigned int Amplitude);	//写幅度

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
void Write_Amplitude(uint Amp); //写幅度，输入范围：1-650 mV

//扫频波下限频率，上限频率，频率步进（单位：Hz），步进时间间隔（单位：ns，范围：4*(1~65536)ns）
void SweepFre(ulong SweepMinFre, ulong SweepMaxFre, ulong SweepStepFre, ulong SweepTime);

void Square_wave(uint Sample_interval);//方波，采样时间间隔输入范围：4*(1~65536)ns


void txd_32bit(uint32_t dat);

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_DRG_Fre_Init(void)
//函数功能:AD9910的数字斜坡模式DRG初始化------------------频率
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_DRG_Fre_Init(void);

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_DRG_Freq_set(uint32_t upper_limit , uint32_t lower_limit ,uint32_t dec_step , uint32_t inc_step , uint16_t neg_rate ,uint16_t pos_rate)
//函数功能:AD9910的DRG设置------------------频率
//入口参数:		upper_limit										上限频率							1Hz---450M
//						lower_limit										下限频率							1Hz---450M       (上限频率要大于下限频率)
//						dec_step											频率加步进						1Hz---450M					
//						inc_step											频率减步进						1Hz---450M
//						neg_rate											频率加的速率(时间)	0x0000----0xffff			  
//						pos_rate											频率减的速率(时间)	0x0000----0xffff
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_DRG_Freq_set(uint32_t upper_limit , uint32_t lower_limit ,uint32_t dec_step , uint32_t inc_step , uint16_t neg_rate ,uint16_t pos_rate);
//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_Init(void)
//函数功能:将CFR1和CFR2恢复默认值
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_Init(void);

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_ZB_Fre_Init(void)
//函数功能:设置RAM模式中的载波的频率的初始化
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_ZB_Fre_Init(void);


//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_ZB_Fre_Set(uint32_t Freq)
//函数功能:设置RAM模式中的载波的频率
//入口参数:Freq--------------------载波频率
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_ZB_Fre_Set(uint32_t Freq);


void FSK_RAM_Write(void);


void FM_RAM_Write(uint32_t modin,uint32_t deepth, uint32_t carrer);

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_ramdata_W(void)
//函数功能:将数据写入1024*32的RAM中---------------------------频率
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_ramdata_W(void);


//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_AMP_W(void)
//函数功能:将数据写入1024*32的RAM中-------------------------幅度
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_AMP_W(void);

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_WAVE_RAM_AMP_W(int mode)
//函数功能:将数据写入1024*32的RAM中-------------------------幅度
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_WAVE_RAM_AMP_W(int mode);

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_DIR_Fre_R(void)
//函数功能:直接转换模式的回放-------------------------频率
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_DIR_Fre_R(void);


//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_DIR_AMP_R(void)
//函数功能:直接转换模式的回放-------------------------幅度
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_DIR_AMP_R(void);


//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_RAMP_UP_ONE_Fre_R(void)
//函数功能:上斜坡模式的回放-------------------------频率
//														ONE 代表由外部引脚PRO2~PRO0控制
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_ONE_Fre_R(void);

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_RAMP_UP_ONE_AMP_R(void)
//函数功能:上斜坡模式的回放-------------------------幅度
//														ONE 代表由外部引脚PRO2~PRO0控制
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_ONE_AMP_R(void);


//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_RAMP_UP_TWO_Fre_R(void)
//函数功能:上斜坡模式的回放-------------------------频率
//														TWO 代表由内部控制							控制位为（CFR1[20:17]） 参考数据手册
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_TWO_Fre_R(void);


//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_RAMP_UP_TWO_AMP_R(void)
//函数功能:上斜坡模式的回放-------------------------幅度
//														TWO 代表由内部控制							控制位为（CFR1[20:17]） 参考数据手册
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_TWO_AMP_R(void);

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_CON_RECIR_Fre_R(void)
//函数功能:连续循环模式的回放-------------------------频率
//														
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_CON_RECIR_Fre_R(void);


//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_CON_RECIR_AMP_R(void)
//函数功能:连续循环模式的回放-------------------------幅度
//														
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_CON_RECIR_AMP_R(void);


//------------------------------------------------------------------------------------
//函数名称:void Freq_convert(uint32_t Freq)	
//函数功能:AD9910写初始频率
//入口参数:Freq      写频率   频率小于450M														
//出口参数:无
//------------------------------------------------------------------------------------
void Freq_convert2(uint32_t Freq);


//------------------------------------------------------------------------------------
//函数名称:void Amp_convert(uint32_t Amp)	
//函数功能:AD9910写初始幅度
//入口参数:Amp      写幅度  														
//出口参数:无
//------------------------------------------------------------------------------------
void Amp_convert2(uint32_t Amp);

//------------------------------------------------------------------------------------
//函数名称:void AD9910_Init_Sin(void)
//函数功能:AD9910时钟的设置和辅助DAC设置 以及AD9910并行正弦初始化
//入口参数:无
//出口参数:无
//------------------------------------------------------------------------------------
void AD9910_Init_Sin(int gain);

























































#endif


