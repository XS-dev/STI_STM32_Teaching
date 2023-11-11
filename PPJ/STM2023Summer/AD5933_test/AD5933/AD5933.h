#ifndef __AD5933_H
#define __AD5933_H
#include "main.h"
#define uint unsigned int


#define AD5933_MCLK 16.776 //=536870912/MCLK;

#define AD5933_Correction 100604823.421598073


///////////////////////////////////////////
//IO配置相关
///////////////////////////////////////////
#define AD5933_SCK_Pin GPIO_PIN_2
#define AD5933_SCK_GPIO_Port GPIOE
#define AD5933_SDA_Pin GPIO_PIN_3
#define AD5933_SDA_GPIO_Port GPIOE

#define AD5933_SCK_H HAL_GPIO_WritePin(AD5933_SCK_GPIO_Port,	AD5933_SCK_Pin,	GPIO_PIN_SET);	
#define AD5933_SDA_H HAL_GPIO_WritePin(AD5933_SDA_GPIO_Port,	AD5933_SDA_Pin,	GPIO_PIN_SET);	

#define AD5933_SCK_L HAL_GPIO_WritePin(AD5933_SCK_GPIO_Port,	AD5933_SCK_Pin,	GPIO_PIN_RESET);	
#define AD5933_SDA_L HAL_GPIO_WritePin(AD5933_SDA_GPIO_Port,	AD5933_SDA_Pin,	GPIO_PIN_RESET);	

#define READ_SDA  		HAL_GPIO_ReadPin(AD5933_SDA_GPIO_Port,AD5933_SDA_Pin)

///////////////////////////////////////////
//配置相关常数
///////////////////////////////////////////
#define AD5933_CTRL_NOP					(0)<<12
#define AD5933_SYS_Init					(1)<<12
#define AD5933_Begin_Fre_Scan		(2)<<12
#define AD5933_Fre_UP						(3)<<12
#define AD5933_Fre_Rep					(4)<<12
#define AD5933_Get_Temp					(9)<<12
#define AD5933_Sleep						(10)<<12
#define AD5933_Standby					(11)<<12

#define AD5933_OUTPUT_2V				(0)<<9
#define AD5933_OUTPUT_1V				(3)<<9
#define AD5933_OUTPUT_400mV			(2)<<9
#define AD5933_OUTPUT_200mV			(1)<<9

#define AD5933_Gain_1						(1)<<8
#define AD5933_Gain_5						(0)<<8

#define AD5933_IN_MCLK					(0)<<3
#define AD5933_OUT_MCLK					(1)<<3

#define AD5933_Reset						(1)<<4
#define AD5933_NReset				    (0)<<4


void I2C_EE_ByteWrite( uint8_t WriteAddr, uint8_t dat );
void Init_AD5933(void);
void Fre_To_Hex(float fre, uint8_t *buf);
void AD5933_Set_Freq_Start( unsigned int freq );
void AD5933_Set_Freq_Add( unsigned int afreq );
void AD5933_Set_Freq_Num( unsigned int num );
void AD5933_Set_Mode( unsigned int ctrl, unsigned int out, unsigned int gain, unsigned int clk, unsigned int rst );
void AD5933_Set_Mode_Rst(void);
void AD5933_Set_Mode_Standby(void);
void AD5933_Set_Mode_SysInit(void);
void AD5933_Set_Mode_Freq_Start(void);
void AD5933_Set_Mode_Freq_UP(void);
void AD5933_Set_Mode_Freq_Repeat(void);
void AD5933_Set_Mode_Freq_Temp(void);
unsigned char  AD5933_Get_DFT_ST(void);
unsigned int AD5933_Get_Real(void);
unsigned int AD5933_Get_Img(void);





void SDA_IN(void);
void SDA_OUT(void);

void Ini_I2c(void);
//void SDA_1(void);
//void SDA_0 (void);
//void SCL_1(void);
//void SCL_0 (void);

void GetACK(void);
void SendNACK(void);
void START(void);
void STOP(void);

void SendByte(uint8_t txd);	// 发送一个字节数据子函数
uint8_t ReadByte(void);  //读一个字节数据
void Write_Byte(char nAddr,uint nValue);

void SetPointer(char nAddr);
int Rece_Byte(char nAddr);

uint16_t AD5933_Tempter(void);


float Get_resistance(uint16_t num);
float AD5933_Sweep (float Fre_Begin,float Fre_UP,uint16_t UP_Num,uint16_t OUTPUT_Vatage,uint16_t Gain,uint16_t SWeep_Rep);
float DA5933_Get_Rs(void);
float DA5933_Get_Cap(float Fre);
float DA5933_Get_L(float Fre);



#endif
