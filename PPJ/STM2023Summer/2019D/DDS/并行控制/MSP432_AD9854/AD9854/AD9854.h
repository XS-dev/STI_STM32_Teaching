#ifndef __AD9854_H
#define __AD9854_H
//#include "msp.h"
#include "ti/devices/msp432p4xx/inc/msp.h"
#include <stdint.h>


#define uint  uint16_t
#define uchar uint8_t
#define ulong uint32_t

extern void AD9854_WR_Byte(ulong addr,ulong dat);
extern void AD9854_Init(void);
extern void AD9854_PortTest(void);
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
extern void AD9854_IO_Init(void);
extern void delay_us(uint32_t i);

#endif

