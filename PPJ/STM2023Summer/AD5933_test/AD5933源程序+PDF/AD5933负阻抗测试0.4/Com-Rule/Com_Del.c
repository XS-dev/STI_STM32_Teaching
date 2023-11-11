#include "Com_Del.h"
#include "AD9834.h" 
#include "AD9851.h" 
#include "AD9854.h" 
#include "AD9954.h" 

u8 (*DDS_deal)(void);

u8 DDS_model=0;
u8 DDS_mod;
extern u8 *Com_dat;
extern u8 Command;
extern u8	Get_Msg_mark;

enum DDS_mode
{
	AD9834=1,
	AD9851,
	AD9854,
	AD9954,
	FRE,
	sine,
	Square,
	Triangle,
	FSK,
	BPSK,
	OSK,
	AM,
	FM,
	RFSK,
	Sweep,
	parrel,
	serial,
	ASK,
	AD9833,
};

double Fre_decoding(void)
{
	double re;
	u8 kk;
	kk=Com_dat[5];
	kk=Com_dat[4];
	kk=Com_dat[3];
	kk=Com_dat[2];
	kk=Com_dat[1];
	kk=Com_dat[0];
	
//	re = Com_dat[0]*256*256*256+Com_dat[1]*256*256+Com_dat[2]*256+Com_dat[3]+(double)(Com_dat[4]*256+Com_dat[5])/100;
	re = Com_dat[5]*256*256*256+Com_dat[4]*256*256+Com_dat[3]*256+Com_dat[2]+(double)(Com_dat[1]*256+Com_dat[0])/100;
	Com_dat+=6;
	return re;
}
u8 Fre_mode(void)
{
	u8 re;
	re = *Com_dat;
	Com_dat++;
	return re;
}
u16 Phase_decoding(void)
{
	u16 re;
	re = Com_dat[0]*256+Com_dat[1];
	Com_dat+=2;
	return re;
}
u16 AMP_decoding(void)
{
	u16 re;
	re = Com_dat[0]*256+Com_dat[1];
	Com_dat+=2;
	return re;
}
u8 AD9834_deal(void)
{
	switch(Command)
	{
		case FRE:AD9834_Set_Freq(FREQ_0,Fre_decoding());break;
		case sine:AD9834_Select_Wave(0x2008);AD9834_Set_Freq(FREQ_0,Fre_decoding());break;
		case Square:AD9834_Select_Wave(0x2028);AD9834_Set_Freq(FREQ_0,Fre_decoding());break;
		case Triangle:AD9834_Select_Wave(0x2002);AD9834_Set_Freq(FREQ_0,Fre_decoding());break;
		default:return ERROR;
	}
	return SUCCESS;
}
u8 AD9851_deal(void)
{
	switch(Command)
	{
		case FRE:AD9851_Setfq(Fre_decoding());break;
////		case sine:break;
////		case Square:break;
////		case Triangle:break;
//		case FSK:break;
//		case BPSK:break;
//		case OSK:break;
//		case AM:break;
//		case FM:break;
//		case RFSK:break;
//		case Sweep:break;
		case parrel:AD9851_Init(ad9851_parallel,*Com_dat);break;
		case serial:AD9851_Init(ad9851_serial,*Com_dat);break;
		default:return ERROR;
	}
	return SUCCESS;
}
u8 AD9854_deal(void)
{
	switch(Command)
	{
		case FRE:break;
		case sine:	if(DDS_mod!=sine)AD9854_Init();				DDS_mod=sine;		AD9854_SetSine_double(Fre_decoding(),*Com_dat);break;
		case Square:break;
		case Triangle:break;
		case FSK:		if(DDS_mod!=FSK)	AD9854_InitFSK();		DDS_mod=FSK;		AD9854_SetFSK(Fre_decoding(),Fre_decoding());break;
		case BPSK:	if(DDS_mod!=BPSK)	AD9854_InitBPSK();	DDS_mod=BPSK;		AD9854_SetBPSK(Phase_decoding(),Phase_decoding());break;
		case OSK:		if(DDS_mod!=OSK)	AD9854_InitOSK();		DDS_mod=OSK;		AD9854_SetOSK(*Com_dat);break;
		case AM:		if(DDS_mod!=AM)		AD9854_InitAM();		DDS_mod=AM;			AD9854_SetAM(AMP_decoding());break;
		case FM:		if(DDS_mod!=FM)		break;
		case RFSK:	if(DDS_mod!=RFSK)	AD9854_InitRFSK();	DDS_mod=RFSK;		AD9854_SetRFSK(Fre_decoding(),Fre_decoding(),Fre_decoding(),Fre_decoding());break;
		case Sweep:	if(DDS_mod!=Sweep)break;
		case parrel:break;
		case serial:break;
		default:return ERROR;
	}
	return SUCCESS;
}
u8 AD9954_deal(void)
{
	switch(Command)
	{
		case FRE:break;
		case sine:	if(DDS_mod!=sine)AD9954_Init();				DDS_mod=sine;		AD9954_SETFRE(Fre_decoding());break;
		case Square:break;
		case Triangle:break;
		case FSK:		if(DDS_mod!=FSK)		AD9854_InitFSK();		DDS_mod=FSK;		DirectSwitchFSK(Fre_decoding(),Fre_decoding(),Fre_decoding(),Fre_decoding());break;
//		case BPSK:	if(DDS_mod!=BPSK)	AD9854_InitBPSK();	DDS_mod=BPSK;		AD9854_SetBPSK(Phase_decoding(),Phase_decoding());break;
//		case OSK:		if(DDS_mod!=OSK)	AD9854_InitOSK();		DDS_mod=OSK;		AD9854_SetOSK(*Com_dat);break;
		case AM:		if(DDS_mod!=AM)			AM_Init();		DDS_mod=AM;			Write_ASF(AMP_decoding());break;
		case FM:		if(DDS_mod!=FM)			break;
//		case RFSK:	if(DDS_mod!=RFSK)	AD9854_InitRFSK();	DDS_mod=RFSK;		AD9854_SetRFSK(Fre_decoding(),Fre_decoding(),Fre_decoding(),Fre_decoding());break;
		case Sweep:	if(DDS_mod!=Sweep)											DDS_mod=Sweep;			Linear_Sweep(Fre_decoding(),Fre_decoding(),Fre_decoding(),Fre_mode(),Fre_decoding(),Fre_mode(),Fre_mode());break;
		case parrel:break;
		case serial:break;
		default:return ERROR;
	}
	return SUCCESS;
}

void Chose_DDS_function(u8 DDS)
{
	switch(DDS)
	{
		case AD9834:AD9834_Init();break;
		case AD9851:AD9851_Init(ad9851_parallel,1);break;
		case AD9854:AD9854_Init();break;
		case AD9954:AD9954_Init();break;
		default:break;
	}	
}

u8 DDS_Chose(u8 DDS)
{
		switch(DDS)
		{
			case AD9834:DDS_deal=AD9834_deal;break;
			case AD9851:DDS_deal=AD9851_deal;break;
			case AD9854:DDS_deal=AD9854_deal;break;
			case AD9954:DDS_deal=AD9954_deal;break;
			default:return ERROR;
		}
		Chose_DDS_function(DDS);
		return SUCCESS;
}

void sys_begin(void)
{
	while(1)
	{
//		Get_Msg_mark=AD9834;
		if(Get_Msg_mark)
		{
			Get_Msg_mark=0;
//			Chose_DDS_function(Command);
			if(DDS_Chose(DDS_model)==SUCCESS)
			{
				DDS_deal();
				return;
			}
		}
	}
}


