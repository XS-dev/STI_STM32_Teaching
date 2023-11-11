/**********************************************************
                       ��������
										 
���ܣ�stm32f103rct6���ƣ�20MHzʱ�ӣ� AD9954���Ҳ���Ƶ�������Χ0-130M(�ɱ༭0-200M)��
			ɨƵĬ�����Ҳ� ��
			��ʾ��12864cog
�ӿڣ����ƽӿ������AD9954.h  �����ӿ������key.h
ʱ�䣺2015/11/10
�汾��1.0
���ߣ���������

������������뵽�Ա��꣬�������ӽ߳�Ϊ������ ^_^
https://shop110336474.taobao.com/?spm=a230r.7195193.1997079397.2.Ic3MRJ

**********************************************************/

#include "task_manage.h"
#include "delay.h"
#include "key.h"
#include "AD9854.h" 
#include <stdio.h>
#include <ctype.h>
#include <cstring>

#define OUT_KEY  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//��ȡ����0
#define FLASH_SAVE_ADDR  0x0801F000  				//����FLASH �����ַ(����Ϊż��)

u8 Task_Index = 0;//�����л�
u8 Param_Mode = 0;//���������л�
u8 fre_buf[StrMax]; //����ת���ַ�����
u8 display[StrMax]; //������ʾ����
u8 P_Index = 0; //�༭λ��
u8 Task_First=1;//��һ�ν�����
u8 _return=0;
//ɨƵ����
u32 SweepMinFre = 1000;
u32 SweepMaxFre = 10000;
u32 SweepStepFre = 100;
u32 SweepTime = 1;//ms
u8 SweepFlag = 0;

//�����ݷŵ���һ�����棬��ʾ��FloatNumС����λ����CursorEn���ʹ��
void Copybuf2dis(u8 *source, u8 dis[StrMax], u8 dispoint, u8 FloatNum, u8 CursorEn)
{
	int i, len;
	
	len = strlen(source);
	i = len - FloatNum;//��������
	if(FloatNum>0)dis[i] = '.';
	for (i = 0; i < len; i++)
	{
		if(i < (len-FloatNum)) dis[i] = source[i];
		else 
		{ dis[i+1] = source[i]; }
	}
	
	if(CursorEn)
	{
		if(dispoint < (len-FloatNum)) dis[dispoint] += 128;
		else dis[dispoint+1] += 128;	
	}
}
//
void Set_PointFre(u32 Key_Value, u8* Task_ID)
{
	//�����ж�
	switch(Key_Value)
	{
		case K_4_S: fre_buf[P_Index]++;break;
		case K_4_L: fre_buf[P_Index]++;break;
		case K_5_L: P_Index++;break;
		case K_5_S: P_Index++;break;
		case K_1_L: P_Index--;break;
		case K_1_S: P_Index--;break;
		case K_3_S: fre_buf[P_Index]--;break;
		case K_3_L: fre_buf[P_Index]--;break;
		case K_2_S: Param_Mode++;break;
	}
	if(fre_buf[P_Index] == '/') fre_buf[P_Index] = '9';//<'0'
	if(fre_buf[P_Index] == ':') fre_buf[P_Index] = '0';//>'9'
	if(P_Index == 255) P_Index=0;
	//�����л�
	if(Key_Value == K_2_L) 
	{	
		Task_Index++;
		LCD_Clear();
	}
	if(Key_Value == K_2_L || Key_Value == K_2_S) Task_First=1;//���µ�һ�ν���
	if(Task_Index >= Interface) Task_Index=0;
	switch(Task_Index)
	{
		case 0: 
			Task0_PointFre(Key_Value);
			break;
		case 1: 
			Task3_SweepFre(Key_Value);
			break;
	}
	//��������
//	if(Task_Index != 1) SweepFlag=0;//
//	else SweepFlag=1;
	//�̶���ʾ
	LCD_Show_CEStr(0,0,"9854");
}
//����

void Task0_PointFre(u32 Key_Value)//���Ҳ� (10M) 0-100 000 000
{
	static u32 SinFre = 50000000;
	u8 showstr[StrMax]={0};
	
	if(Task_First)
	{
		AD9854_Init();//��ʼ����Ƶ
		Task_First = 0;
		Key_Value = K_2_S;
		sprintf(fre_buf, "%9d", SinFre);//��һ�� ����
		LCD_Show_CEStr(64-8*3,0,"���Ҳ�");
		_return=1;
	}
	if(Key_Value != K_NO)
	{
		//�ж�
		P_Index = P_Index%9;//����λ��
		SinFre = atol(fre_buf);//�ַ�ת�����֣��ж�������
		if(SinFre>200000000) SinFre=200000000;//��������
		if(SinFre<0) SinFre=0;
		sprintf(fre_buf, "%9d", SinFre);//�ַ�ת��
		//��ʾ
		sprintf(showstr, "%9d", SinFre);//�ַ�ת��
		fre_buf_change(showstr);//fre_buf���� �� '->'0'
		Copybuf2dis(showstr, display, P_Index, 0, 1);
		OLED_ShowString(64-4*11, 3, display);
		LCD_Show_CEStr(64-4*11+9*8,3,"Hz");
		//���ݴ���д��
		AD9854_SetSine_double(SinFre,4095);
		
		_return=1;
	}
}

void Task1_Square(u32 Key_Value)
{}
void Task2_Triangular(u32 Key_Value)
{}

void Task3_SweepFre(u32 Key_Value)//ɨƵ
{
	u8 showstr[StrMax]={0};
	
	if(Task_First)
	{
		AD9854_InitRFSK();//��ʼ��FSKɨƵ
		Task_First = 0;//�����һ�ν�����
		Key_Value = K_2_S;
		Param_Mode %= 4;//�������ģʽ���Ա�װ���ʼֵ
		if(Param_Mode == 0) sprintf(fre_buf, "%9d", SweepMinFre);
		if(Param_Mode == 1) sprintf(fre_buf, "%9d", SweepMaxFre);
		if(Param_Mode == 2) sprintf(fre_buf, "%4d", SweepStepFre);
		if(Param_Mode == 3) sprintf(fre_buf, "%3d", SweepTime);
		LCD_Show_CEStr(64-8*3,0," ɨƵ ");//ģʽ����
		_return=1;//������ʾ��־ 
	}
	if(Key_Value != K_NO)
	{
		if(Param_Mode == 0)//��СƵ������
		{
			P_Index %= 9;//����λ��
			SweepMinFre = atol(fre_buf);//�ַ�ת��
			if(SweepMinFre>SweepMaxFre) SweepMinFre=SweepMaxFre;//��������
			if(SweepMinFre<0) SweepMinFre=0;
			sprintf(fre_buf, "%9d", SweepMinFre);//��������д��
		}
		//��ʾ
		sprintf(showstr, "%9d", SweepMinFre);//�������뻺����ʾ
		fre_buf_change(showstr);//fre_buf���� �� '->'0'
		if(Param_Mode == 0) Copybuf2dis(showstr, display, P_Index, 0, 1);
		else Copybuf2dis(showstr, display, P_Index, 0, 0);
		OLED_ShowString(64-4*11+16, 2, display);
		LCD_Show_CEStr(64-4*11+9*8+16,2,"Hz");
		LCD_Show_CEStr(0,2,"Min:");
		
		if(Param_Mode == 1)//���Ƶ������
		{
			P_Index %= 9;//����λ��
			SweepMaxFre = atol(fre_buf);//�ַ�ת��
			if(SweepMaxFre>200000000) SweepMaxFre=200000000;//��������
			if(SweepMaxFre<0) SweepMaxFre=0;
			sprintf(fre_buf, "%9d", SweepMaxFre);//��������д��
		}
		//��ʾ
		sprintf(showstr, "%9d", SweepMaxFre);//�������뻺����ʾ
		fre_buf_change(showstr);//fre_buf���� �� '->'0'
		if(Param_Mode == 1) Copybuf2dis(showstr, display, P_Index, 0, 1);
		else Copybuf2dis(showstr, display, P_Index, 0, 0);
		OLED_ShowString(64-4*11+16, 4, display);
		LCD_Show_CEStr(64-4*11+9*8+16,4,"Hz");
		LCD_Show_CEStr(0,4,"Max:");
		
		if(Param_Mode == 2)//Ƶ�ʲ�������
		{
			P_Index %= 5;//����λ��
			SweepStepFre = atol(fre_buf);//�ַ�ת��
			if(SweepStepFre>100000) SweepStepFre=100000-1;//��������
			if(SweepStepFre<0) SweepStepFre=0;
			sprintf(fre_buf, "%5d", SweepStepFre);//��������д��
		}
		//��ʾ
		sprintf(showstr, "%5d", SweepStepFre);//�������뻺����ʾ
		fre_buf_change(showstr);//fre_buf���� �� '->'0'
		if(Param_Mode == 2) Copybuf2dis(showstr, display, P_Index, 0, 1);
		else Copybuf2dis(showstr, display, P_Index, 0, 0);
		display[5]=0;//ֻ��ʾ4λ
		OLED_ShowString(0, 6, display);
		LCD_Show_CEStr(8*5,6,"Hz");
		
		if(Param_Mode == 3)//����ʱ������
		{
			P_Index %= 7;//����λ��
			SweepTime = atol(fre_buf);//�ַ�ת��
			if(SweepTime>1048575) SweepTime=1048575;//��������
			if(SweepTime<0) SweepTime=0;
			sprintf(fre_buf, "%7d", SweepTime);//��������д��
		}
		//��ʾ
		sprintf(showstr, "%7d", SweepTime);//�������뻺����ʾ
		fre_buf_change(showstr);//fre_buf���� �� '->'0'
		if(Param_Mode == 3) Copybuf2dis(showstr, display, P_Index, 0, 1);
		else Copybuf2dis(showstr, display, P_Index, 0, 0);
		display[7]=0;//ֻ��ʾ3λ
		OLED_ShowString(64, 6, display);
//		LCD_Show_CEStr(64+3*8,6,"Ms");
		//���ݴ���д��
		AD9854_SetRFSK(SweepMinFre, SweepMaxFre, SweepStepFre, SweepTime);
		
		_return=1;
	}
}

//
void fre_buf_change(u8 *strbuf)
{
	int i;
	for (i = 0 ; i < strlen(strbuf); i++)
	 if(strbuf[i]==0x20) strbuf[i] = '0';
	for (i = 0 ; i < strlen(fre_buf); i++)
	 if(fre_buf[i]==0x20) fre_buf[i] = '0';
}
