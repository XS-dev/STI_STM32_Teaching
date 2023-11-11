#ifndef _AD9959_H_
#define _AD9959_H_
#include "base.h"
#include "stdint.h"

#define kHz 1000*0.9987013790118112670830499041494
//������0.9986705

//AD9959�Ĵ�����ַ����
#define CSR_ADD   0x00   //CSR ͨ��ѡ��Ĵ���
#define FR1_ADD   0x01   //FR1 ���ܼĴ���1
#define FR2_ADD   0x02   //FR2 ���ܼĴ���2
#define CFR_ADD   0x03   //CFR ͨ�����ܼĴ���
#define CFTW0_ADD 0x04   //CTW0 ͨ��Ƶ��ת���ּĴ���
#define CPOW0_ADD 0x05   //CPW0 ͨ����λת���ּĴ���
#define ACR_ADD   0x06   //ACR ���ȿ��ƼĴ���
#define LSRR_ADD  0x07   //LSR ͨ������ɨ��Ĵ���
#define RDW_ADD   0x08   //RDW ͨ����������ɨ��Ĵ���
#define FDW_ADD   0x09   //FDW ͨ����������ɨ��Ĵ���\


#define Mhz 1000000
#define step500K 500000



//AD9959�ܽź궨��
#define AD9959_PWR	PBout(12)
#define Reset		PBout(10)
#define UPDATE		PEout(14)
#define CS			PEout(12)
#define SCLK		PEout(10)
#define SDIO3		PEout(8)

#define SDIO2		PBout(13)
#define SDIO1		PBout(11)
#define SDIO0		PEout(15)
#define PS3		PEout(13)
#define PS2		PEout(11)
#define PS1		PEout(9)
#define PS0		PEout(7)
#define AD9959_Amv 1.8907
#define AD9959_Khz 1000


void delay1 (u32 length);
void IntReset(void);	  //AD9959��λ
void IO_Update(void);   //AD9959��������
void Intserve(void);		   //IO�ڳ�ʼ��
void WriteData_AD9959(u8 RegisterAddress, u8 NumberofRegisters, u8 *RegisterData,u8 temp);
void Init_AD9959(void);
void Write_frequence(u8 Channel,u32 Freq);
void Write_Amplitude(u8 Channel, u16 Ampli);
void Write_Phase(u8 Channel,u16 Phase);



#endif
