 /*-----------------------------------------------
  名称：AD9854并口驱动
  编写：Liu
  日期：2014.3
  修改：无
  内容：
------------------------------------------------*/
#ifndef __AD9910_H__
#define __AD9910_H__

#include "stm32f10x.h"

#define uchar unsigned char
#define uint  unsigned int	
#define ulong  unsigned long int

#define AD9910_PWR PCout(13)//0
//原始IO
#define AD9910_SDIO PAout(5)
#define DRHOLD PCout(1)
#define DROVER PCout(2)
#define UP_DAT PCout(3)
#define PROFILE1 PCout(10)
#define MAS_REST PAout(6)
#define SCLK PAout(2)
#define DRCTL  PAout(4)
#define OSK PCout(8)
#define PROFILE0 PCout(4)
#define PROFILE2 PCout(5)
#define CS  PBout(10)

void AD9110_IOInit(void);
void Init_ad9910(void);
void Freq_convert(ulong Freq);										//写频率
void AD9910_AmpWrite(uint16_t Amp);

#endif


