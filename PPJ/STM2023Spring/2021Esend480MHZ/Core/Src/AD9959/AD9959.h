#ifndef __AD9959_H__
#define __AD9959_H__

#include "main.h"


extern uint8_t 	FR1_DATA[3] ;
extern uint8_t 	LSRR_DATA[2];
extern uint8_t 	RDW_DATA[4] ; 						
extern uint8_t 	FDW_DATA[4] ;


#define SCK_Pin GPIO_PIN_6
#define SCK_GPIO_Port GPIOA
#define SD1_Pin GPIO_PIN_7
#define SD1_GPIO_Port GPIOA
#define CS_Pin GPIO_PIN_4
#define CS_GPIO_Port GPIOC
#define SD0_Pin GPIO_PIN_5
#define SD0_GPIO_Port GPIOC
#define UPDATE_Pin GPIO_PIN_0
#define UPDATE_GPIO_Port GPIOB
#define P0_Pin GPIO_PIN_1
#define P0_GPIO_Port GPIOB
#define RST_Pin GPIO_PIN_2
#define RST_GPIO_Port GPIOB
#define PDC_Pin GPIO_PIN_9
#define PDC_GPIO_Port GPIOE






//AD9959寄存器地址定义
#define CSR_ADD   0x00   //CSR 通道选择寄存器
#define FR1_ADD   0x01   //FR1 功能寄存器1
#define FR2_ADD   0x02   //FR2 功能寄存器2
#define CFR_ADD   0x03   //CFR 通道功能寄存器
#define CFTW0_ADD 0x04   //CTW0 通道频率转换字寄存器
#define CPOW0_ADD 0x05   //CPW0 通道相位转换字寄存器
#define ACR_ADD   0x06   //ACR 幅度控制寄存器
#define LSRR_ADD  0x07   //LSR 通道线性扫描寄存器
#define RDW_ADD   0x08   //RDW 通道线性向上扫描寄存器
#define FDW_ADD   0x09   //FDW 通道线性向下扫描寄存器


//AD9959管脚宏定义
#define CS_H			HAL_GPIO_WritePin(CS_GPIO_Port, 	CS_Pin, 	GPIO_PIN_SET);			
#define SCLK_H			HAL_GPIO_WritePin(SCK_GPIO_Port, 	SCK_Pin, 	GPIO_PIN_SET);					
#define UPDATE_H		HAL_GPIO_WritePin(UPDATE_GPIO_Port,	UPDATE_Pin,	GPIO_PIN_SET);					
#define PS0_H			HAL_GPIO_WritePin(P0_GPIO_Port,		P0_Pin, 	GPIO_PIN_SET);			
//#define PS1_H			HAL_GPIO_WritePin(P1_GPIO_Port,		P1_Pin, 	GPIO_PIN_SET);			
//#define PS2_H			HAL_GPIO_WritePin(P2_GPIO_Port,		P2_Pin, 	GPIO_PIN_SET);			
//#define PS3_H			HAL_GPIO_WritePin(P3_GPIO_Port,		P3_Pin, 	GPIO_PIN_SET);			
#define SDIO0_H			HAL_GPIO_WritePin(SD0_GPIO_Port,	SD0_Pin,	GPIO_PIN_SET);	
#define SDIO1_H			HAL_GPIO_WritePin(SD1_GPIO_Port,	SD1_Pin,	GPIO_PIN_SET);	
//#define SDIO2_H			HAL_GPIO_WritePin(SD2_GPIO_Port,	SD2_Pin,	GPIO_PIN_SET);	
//#define SDIO3_H			HAL_GPIO_WritePin(SD3_GPIO_Port,	SD3_Pin,	GPIO_PIN_SET);	
#define AD9959_PWR_H	HAL_GPIO_WritePin(PDC_GPIO_Port,	PDC_Pin,	GPIO_PIN_SET);		
#define Reset_H			HAL_GPIO_WritePin(RST_GPIO_Port,	RST_Pin,	GPIO_PIN_SET);	



#define CS_L			HAL_GPIO_WritePin(CS_GPIO_Port, 	CS_Pin, 	GPIO_PIN_RESET);			
#define SCLK_L			HAL_GPIO_WritePin(SCK_GPIO_Port, 	SCK_Pin, 	GPIO_PIN_RESET);					
#define UPDATE_L		HAL_GPIO_WritePin(UPDATE_GPIO_Port,	UPDATE_Pin,	GPIO_PIN_RESET);					
#define PS0_L			HAL_GPIO_WritePin(P0_GPIO_Port,		P0_Pin, 	GPIO_PIN_RESET);			
//#define PS1_L			HAL_GPIO_WritePin(P1_GPIO_Port,		P1_Pin, 	GPIO_PIN_RESET);			
//#define PS2_L			HAL_GPIO_WritePin(P2_GPIO_Port,		P2_Pin, 	GPIO_PIN_RESET);			
//#define PS3_L			HAL_GPIO_WritePin(P3_GPIO_Port,		P3_Pin, 	GPIO_PIN_RESET);			
#define SDIO0_L			HAL_GPIO_WritePin(SD0_GPIO_Port,	SD0_Pin,	GPIO_PIN_RESET);	
#define SDIO1_L			HAL_GPIO_WritePin(SD1_GPIO_Port,	SD1_Pin,	GPIO_PIN_RESET);	
//#define SDIO2_L			HAL_GPIO_WritePin(SD2_GPIO_Port,	SD2_Pin,	GPIO_PIN_RESET);	
//#define SDIO3_L			HAL_GPIO_WritePin(SD3_GPIO_Port,	SD3_Pin,	GPIO_PIN_RESET);	
#define AD9959_PWR_L	HAL_GPIO_WritePin(PDC_GPIO_Port,	PDC_Pin,	GPIO_PIN_RESET);		
#define Reset_L			HAL_GPIO_WritePin(RST_GPIO_Port,	RST_Pin,	GPIO_PIN_RESET);	



void AD9959_GPIO_Init(void);
void delay1 (uint32_t length);
void IntReset(void);	  //AD9959复位
void IO_Update(void);   //AD9959更新数据
void Intserve(void);		   //IO口初始化
void WriteData_AD9959(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData,uint8_t temp);
void Init_AD9959(void);
void Write_frequence(uint8_t Channel,uint32_t Freq);
void Write_Amplitude(uint8_t Channel, uint16_t Ampli);
void Write_Phase(uint8_t Channel,uint16_t Phase);


#endif
