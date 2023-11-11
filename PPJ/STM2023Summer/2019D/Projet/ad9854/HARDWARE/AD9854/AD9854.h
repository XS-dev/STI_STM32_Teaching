#ifndef __AD9854_H
#define __AD9854_H	 
#include "sys.h"


#define AD9854_RST    PAout(6)   //AD9854复位端口
#define AD9854_UDCLK  PAout(4)   //AD9854更新时钟
#define AD9854_WR     PAout(5)  //AD9854写使能，低有效
#define AD9854_RD     PAout(8)   //AD9854读使能，低有效
#define AD9854_OSK    PAout(2)   //AD9854 OSK控制端
#define AD9854_FDATA  PBout(10)   //AD9854 FSK,PSK控制

#define AD9854_DataBus GPIOC->BSRR	//PC7 ~PC0 
#define AD9854_AdrBus  GPIOC->BSRR	//PC13~PC8

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

