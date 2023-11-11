#ifndef __AD9854_H
#define __AD9854_H	

#include "main.h"

//#define RST_Pin GPIO_PIN_12
//#define RST_GPIO_Port GPIOB
//#define A5_Pin GPIO_PIN_13
//#define A5_GPIO_Port GPIOB
//#define D7_Pin GPIO_PIN_14
//#define D7_GPIO_Port GPIOB
//#define A4_Pin GPIO_PIN_15
//#define A4_GPIO_Port GPIOB
//#define D6_Pin GPIO_PIN_8
//#define D6_GPIO_Port GPIOD
//#define A3_Pin GPIO_PIN_9
//#define A3_GPIO_Port GPIOD
//#define D5_Pin GPIO_PIN_10
//#define D5_GPIO_Port GPIOD
//#define A2_Pin GPIO_PIN_11
//#define A2_GPIO_Port GPIOD
//#define D4_Pin GPIO_PIN_12
//#define D4_GPIO_Port GPIOD
//#define A1_Pin GPIO_PIN_13
//#define A1_GPIO_Port GPIOD
//#define D3_Pin GPIO_PIN_14
//#define D3_GPIO_Port GPIOD
//#define A0_Pin GPIO_PIN_15
//#define A0_GPIO_Port GPIOD
//#define D2_Pin GPIO_PIN_2
//#define D2_GPIO_Port GPIOG
//#define UDCLK_Pin GPIO_PIN_3
//#define UDCLK_GPIO_Port GPIOG
//#define D1_Pin GPIO_PIN_4
//#define D1_GPIO_Port GPIOG
//#define WD_Pin GPIO_PIN_5
//#define WD_GPIO_Port GPIOG
//#define D0_Pin GPIO_PIN_6
//#define D0_GPIO_Port GPIOG
//#define RD_Pin GPIO_PIN_7
//#define RD_GPIO_Port GPIOG
//#define OSK_Pin GPIO_PIN_6
//#define OSK_GPIO_Port GPIOC
//#define FSK_Pin GPIO_PIN_8
//#define FSK_GPIO_Port GPIOC

//#define AD9854_RST    PBout(12)   //AD9854复位端口
//#define AD9854_UDCLK  PGout(3)   //AD9854更新时钟
//#define AD9854_WR     PGout(5)  //AD9854写使能，低有效
//#define AD9854_RD     PGout(7)   //AD9854读使能，低有效
//#define AD9854_OSK    PCout(6)   //AD9854 OSK控制端
//#define AD9854_FDATA  PCout(8)   //AD9854 FSK,PSK控制

#define AD9854_RST_H  	HAL_GPIO_WritePin(DDRST_GPIO_Port, DDRST_Pin, GPIO_PIN_SET);
#define AD9854_UDCLK_H	HAL_GPIO_WritePin(UCLK_GPIO_Port, UCLK_Pin, GPIO_PIN_SET);
#define AD9854_WR_H			HAL_GPIO_WritePin(WD_GPIO_Port, WD_Pin, GPIO_PIN_SET);
#define AD9854_RD_H  		HAL_GPIO_WritePin(RD_GPIO_Port, RD_Pin, GPIO_PIN_SET); 
#define AD9854_OSK_H  	HAL_GPIO_WritePin(OSK_GPIO_Port, OSK_Pin, GPIO_PIN_SET);
#define AD9854_FDATA_H	HAL_GPIO_WritePin(FSK_GPIO_Port, FSK_Pin, GPIO_PIN_SET);

#define AD9854_RST_L  	HAL_GPIO_WritePin(DDRST_GPIO_Port, DDRST_Pin, GPIO_PIN_RESET);
#define AD9854_UDCLK_L  HAL_GPIO_WritePin(UCLK_GPIO_Port, UCLK_Pin, 	GPIO_PIN_RESET);
#define AD9854_WR_L     HAL_GPIO_WritePin(WD_GPIO_Port, WD_Pin, 			GPIO_PIN_RESET);
#define AD9854_RD_L     HAL_GPIO_WritePin(RD_GPIO_Port, RD_Pin, 			GPIO_PIN_RESET); 
#define AD9854_OSK_L    HAL_GPIO_WritePin(OSK_GPIO_Port, OSK_Pin, 		GPIO_PIN_RESET);
#define AD9854_FDATA_L  HAL_GPIO_WritePin(FSK_GPIO_Port, FSK_Pin, 		GPIO_PIN_RESET);


////#define AD9854_DataBus GPIOC->BSRR	//PC7 ~PC0 
////#define AD9854_AdrBus  GPIOC->BSRR	//PC13~PC8

//#define  DDS_D0 PGout(6)		
//#define  DDS_D1 PGout(4)
//#define  DDS_D2 PGout(2)
//#define  DDS_D3 PDout(14)
//#define  DDS_D4 PDout(12)
//#define  DDS_D5 PDout(10)
//#define  DDS_D6 PDout(8)
//#define  DDS_D7 PBout(14)

#define  DDS_D0_H 	HAL_GPIO_WritePin(DD0_GPIO_Port, DD0_Pin, GPIO_PIN_SET);
#define  DDS_D1_H 	HAL_GPIO_WritePin(DD1_GPIO_Port, DD1_Pin, GPIO_PIN_SET);
#define  DDS_D2_H 	HAL_GPIO_WritePin(DD2_GPIO_Port, DD2_Pin, GPIO_PIN_SET);
#define  DDS_D3_H 	HAL_GPIO_WritePin(DD3_GPIO_Port, DD3_Pin, GPIO_PIN_SET); 
#define  DDS_D4_H 	HAL_GPIO_WritePin(DD4_GPIO_Port, DD4_Pin, GPIO_PIN_SET);
#define  DDS_D5_H 	HAL_GPIO_WritePin(DD5_GPIO_Port, DD5_Pin, GPIO_PIN_SET);
#define  DDS_D6_H 	HAL_GPIO_WritePin(DD6_GPIO_Port, DD6_Pin, GPIO_PIN_SET);
#define  DDS_D7_H 	HAL_GPIO_WritePin(DD7_GPIO_Port, DD7_Pin, GPIO_PIN_SET);

#define  DDS_D0_L	 HAL_GPIO_WritePin(DD0_GPIO_Port, DD0_Pin, GPIO_PIN_RESET);
#define  DDS_D1_L	 HAL_GPIO_WritePin(DD1_GPIO_Port, DD1_Pin, GPIO_PIN_RESET);
#define  DDS_D2_L	 HAL_GPIO_WritePin(DD2_GPIO_Port, DD2_Pin, GPIO_PIN_RESET);
#define  DDS_D3_L	 HAL_GPIO_WritePin(DD3_GPIO_Port, DD3_Pin, GPIO_PIN_RESET); 
#define  DDS_D4_L	 HAL_GPIO_WritePin(DD4_GPIO_Port, DD4_Pin, GPIO_PIN_RESET);
#define  DDS_D5_L	 HAL_GPIO_WritePin(DD5_GPIO_Port, DD5_Pin, GPIO_PIN_RESET);
#define  DDS_D6_L	 HAL_GPIO_WritePin(DD6_GPIO_Port, DD6_Pin, GPIO_PIN_RESET);
#define  DDS_D7_L	 HAL_GPIO_WritePin(DD7_GPIO_Port, DD7_Pin, GPIO_PIN_RESET);



#define  DDS_A5_H  HAL_GPIO_WritePin(DA5_GPIO_Port, DA5_Pin, GPIO_PIN_SET);
#define  DDS_A4_H  HAL_GPIO_WritePin(DA4_GPIO_Port, DA4_Pin, GPIO_PIN_SET);
#define  DDS_A3_H  HAL_GPIO_WritePin(DA3_GPIO_Port, DA3_Pin, GPIO_PIN_SET);
#define  DDS_A2_H  HAL_GPIO_WritePin(DA2_GPIO_Port, DA2_Pin, GPIO_PIN_SET);
#define  DDS_A1_H  HAL_GPIO_WritePin(DA1_GPIO_Port, DA1_Pin, GPIO_PIN_SET);
#define  DDS_A0_H  HAL_GPIO_WritePin(DA0_GPIO_Port, DA0_Pin, GPIO_PIN_SET);

#define  DDS_A5_L  HAL_GPIO_WritePin(DA5_GPIO_Port, DA5_Pin, GPIO_PIN_RESET);
#define  DDS_A4_L  HAL_GPIO_WritePin(DA4_GPIO_Port, DA4_Pin, GPIO_PIN_RESET);
#define  DDS_A3_L  HAL_GPIO_WritePin(DA3_GPIO_Port, DA3_Pin, GPIO_PIN_RESET);
#define  DDS_A2_L  HAL_GPIO_WritePin(DA2_GPIO_Port, DA2_Pin, GPIO_PIN_RESET);
#define  DDS_A1_L  HAL_GPIO_WritePin(DA1_GPIO_Port, DA1_Pin, GPIO_PIN_RESET);
#define  DDS_A0_L  HAL_GPIO_WritePin(DA0_GPIO_Port, DA0_Pin, GPIO_PIN_RESET);




//#define  DDS_A5  PBout(13)
//#define  DDS_A4  PBout(15)
//#define  DDS_A3  PDout(9)
//#define  DDS_A2  PDout(11)
//#define  DDS_A1  PDout(13)
//#define  DDS_A0  PDout(15)


#define uint  unsigned int
#define uchar unsigned char
#define ulong unsigned long

extern void AD9854_Init(void);						  
static void Freq_convert(long Freq);	         	  
extern void AD9854_SetSine(ulong Freq,uint Shape);	  
static void Freq_double_convert(double Freq);		  
extern void AD9854_SetSine_double(double Freq,uint Shape);
extern void AD9854_InitFSK(void);				
extern void AD9854_SetFSK(ulong Freq1,ulong Freq2);					  
extern void AD9854_InitBPSK(void);					  
extern void AD9854_SetBPSK(uint Phase1,uint Phase2);					
extern void AD9854_InitOSK(void);					 
extern void AD9854_SetOSK(uchar RateShape);					  
extern void AD9854_InitAM(void);					 
extern void AD9854_SetAM(uint Shape);					
extern void AD9854_InitRFSK(void);					 
extern void AD9854_SetRFSK(ulong Freq_Low,ulong Freq_High,ulong Freq_Up_Down,ulong FreRate);		

#endif

