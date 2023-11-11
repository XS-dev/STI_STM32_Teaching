/**********************************************************
                       康威电子
										 
功能：stm32f103rct6控制
			显示：12864
接口：按键接口请参照key.h
时间：2015/11/3
版本：1.0
作者：康威电子
其他：

更多电子需求，请到淘宝店，康威电子竭诚为您服务 ^_^
https://shop110336474.taobao.com/?spm=a230r.7195193.1997079397.2.Ic3MRJ

**********************************************************/


#include "task_manage.h"
#include "delay.h"
#include "key.h"
#include "AD9910.h"
#include <stdio.h>
#include <ctype.h>
#include <cstring>

#define OUT_KEY  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//读取按键0
#define FLASH_SAVE_ADDR  0x0801F000  				//设置FLASH 保存地址(必须为偶数)


u8 Task_Index = 0;//界面切换
u8 Param_Mode = 0;//参数类型切换
u8 fre_buf[StrMax]; //参数转换字符缓存
u8 display[StrMax]; //参数显示缓存
u8 P_Index = 0; //编辑位置
u8 Task_First=1;//第一次进入标记
u8 _return=0;
//扫频参数
u32 SweepMinFre = 1000;
u32 SweepMaxFre = 10000;
u32 SweepStepFre = 100;
u16 SweepTime = 1;//ms
u8 SweepFlag = 0;

u8 Task_Delay(u32 delay_time, u8* delay_ID)
{
	static u8 Time_Get = 0;
	static u32 Time_Triger;
    if(Time_Get == 0)
    {
      Time_Triger = SysTimer + delay_time;
      Time_Get = 1;
    }
    if(SysTimer >= Time_Triger)
    { 
      Time_Get = 0;
			*delay_ID = 1;		//	后续代码已被执行一遍
			return 1;
    }
		return 0;
}

//u8 TaskOneToIdel(void)
//{
//	static u8 delay_ID0 = 0;
//	static u8 delay_ID1 = 0;
//	static u8 delay_ID2 = 0;
//	static u8 delay_ID3 = 0;
//	u8 delay_arrive0 = 0;
//	u8 delay_arrive1 = 0;
//	u8 delay_arrive2 = 0;
//	u8 delay_arrive3 = 0;
//	
//	delay_arrive0 = Task_Delay(100, &delay_ID0);
//	delay_arrive1 = Task_Delay(100, &delay_ID1);
//	delay_arrive2 = Task_Delay(100, &delay_ID2);
//	delay_arrive3 = Task_Delay(100, &delay_ID3);
//	if((delay_arrive0 == 0) && (delay_ID0 == 0))
//		return 0;
//	else if((delay_arrive0) && (delay_ID0))
//	{
//			//执行本延时后代码
//	}
//		
//	
//	
//	if(delay_ID0&&delay_ID1&&delay_ID2&&delay_ID3)
//	{
//		delay_ID0 = 0;
//		delay_ID1 = 0;
//		delay_ID2 = 0;
//		delay_ID3 = 0;
//	}
//}

u8 TaskCycleDelay(u32 delay_time, u8* Last_delay_ID, u8* Self_delay_ID)
{
	static u8 Time_Get = 0;
	static u32 Time_Triger;
	
	if(!(*Last_delay_ID))
		return 0;
	if(Time_Get == 0)
	{
		Time_Triger = SysTimer + delay_time;
		Time_Get = 1;
	}
	if(SysTimer >= Time_Triger)
	{ 
		Time_Get = 0;
		*Last_delay_ID = 0;
		*Self_delay_ID = 1;		//	后续代码已被执行一遍
		return 1;
	}
	return 0;
}
void welcome_KW(void)
{
	u8 delay_ID[11] = {0,0,0,0,0,0,0,0,0,0};
	u8 delay_ID_Welcome[3] = {0,0,0};
	u16 Wel_time0 = 50,Wel_time1 = 100;
	delay_ID[10] = 1;
	delay_ID_Welcome[2] = 1;
	LCD_Show_CEStr(0,6,"ADF4351");
	LCD_Show_CEStr(56,6,"初始化");
	while(1)
	{
	if(TaskCycleDelay(Wel_time0, &delay_ID[10], &delay_ID[0]))
		LCD_Show_CEStr(32,0,"康");
	if(TaskCycleDelay(Wel_time0, &delay_ID[0], &delay_ID[1]))
		LCD_Show_CEStr(48,0,"威");
	if(TaskCycleDelay(Wel_time0, &delay_ID[1], &delay_ID[2]))
		LCD_Show_CEStr(64,0,"电");
	if(TaskCycleDelay(Wel_time0, &delay_ID[2], &delay_ID[3]))
		LCD_Show_CEStr(80,0,"子");
	if(TaskCycleDelay(Wel_time0, &delay_ID[3], &delay_ID[4]))
		LCD_Show_CEStr(16,2,"竭");
	if(TaskCycleDelay(Wel_time0, &delay_ID[4], &delay_ID[5]))
		LCD_Show_CEStr(32,2,"诚");
	if(TaskCycleDelay(Wel_time0, &delay_ID[5], &delay_ID[6]))
		LCD_Show_CEStr(48,2,"为");
	if(TaskCycleDelay(Wel_time0, &delay_ID[6], &delay_ID[7]))
		LCD_Show_CEStr(64,2,"您");
	if(TaskCycleDelay(Wel_time0, &delay_ID[7], &delay_ID[8]))
		LCD_Show_CEStr(80,2,"服");
	if(TaskCycleDelay(Wel_time0, &delay_ID[8], &delay_ID[9]))
		LCD_Show_CEStr(96,2,"务");
	if(TaskCycleDelay(Wel_time0, &delay_ID[9], &delay_ID[0]))
		break;
	if(TaskCycleDelay(Wel_time1, &delay_ID_Welcome[2], &delay_ID_Welcome[0]))
		LCD_Show_CEStr(104,6,".  ");
	if(TaskCycleDelay(Wel_time1, &delay_ID_Welcome[0], &delay_ID_Welcome[1]))
		LCD_Show_CEStr(112,6,".");
	if(TaskCycleDelay(Wel_time1, &delay_ID_Welcome[1], &delay_ID_Welcome[2]))
		LCD_Show_CEStr(120,6,".");
		LCD_Refresh_Gram();
	}
}
//把数据放到另一个缓存，显示，FloatNum小数点位数，CursorEn光标使能
void Copybuf2dis(u8 *source, u8 dis[StrMax], u8 dispoint, u8 FloatNum, u8 CursorEn)
{
	int i, len;
	
	len = strlen(source);
	i = len - FloatNum;//整数个数
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
	//按键判断
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
	//界面切换
	if(Key_Value == K_2_L) 
	{	
		Task_Index++;
		LCD_Clear();
	}
	if(Key_Value == K_2_L || Key_Value == K_2_S) Task_First=1;//更新第一次进入
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
	//其他处理
	if(Task_Index != 1) SweepFlag=0;//
	else SweepFlag=1;
	//固定显示
	LCD_Show_CEStr(0,0,"9910");
}
//任务

void Task0_PointFre(u32 Key_Value)//正弦波 (10M) 0-100 000 000
{
	static u32 SinFre = 400000000;
	u8 showstr[StrMax]={0};
	
	if(Task_First)
	{
		Task_First = 0;
		Key_Value = K_2_S;
		sprintf(fre_buf, "%9d", SinFre);//第一次 进入
		LCD_Show_CEStr(64-8*3,0,"正弦波");
		_return=1;
	}
	if(Key_Value != K_NO)
	{
		//判断
		P_Index = P_Index%9;//数据位数
		SinFre = atol(fre_buf);//字符转换数字，判断上下限
		if(SinFre>1000000000) SinFre=1000000000;//数据限制
		if(SinFre<0) SinFre=0;
		sprintf(fre_buf, "%9d", SinFre);//字符转换
		//显示
		sprintf(showstr, "%9d", SinFre);//字符转换
		fre_buf_change(showstr);//fre_buf当中 ‘ '->'0'
		Copybuf2dis(showstr, display, P_Index, 0, 1);
		OLED_ShowString(64-4*11, 3, display);
		LCD_Show_CEStr(64-4*11+9*8,3,"Hz");
		//数据处理写入
		Freq_convert(SinFre);
		
		_return=1;
	}
}

void Task1_Square(u32 Key_Value)//方波 300k
{}
void Task2_Triangular(u32 Key_Value)//三角波 1M
{}

void Task3_SweepFre(u32 Key_Value)//扫频
{
	u8 showstr[StrMax]={0};
	
	if(Task_First)
	{
		Task_First = 0;//清除第一次进入标记
		Key_Value = K_2_S;
		Param_Mode %= 4;//计算参数模式，以便装入初始值
		if(Param_Mode == 0) sprintf(fre_buf, "%9d", SweepMinFre);
		if(Param_Mode == 1) sprintf(fre_buf, "%9d", SweepMaxFre);
		if(Param_Mode == 2) sprintf(fre_buf, "%4d", SweepStepFre);
		if(Param_Mode == 3) sprintf(fre_buf, "%3d", SweepTime);
		LCD_Show_CEStr(64-8*3,0," 扫频 ");//模式名称
		_return=1;//更新显示标志 
	}
	if(Key_Value != K_NO)
	{
		if(Param_Mode == 0)//最小频率设置
		{
			P_Index %= 9;//参数位数
			SweepMinFre = atol(fre_buf);//字符转换
			if(SweepMinFre>SweepMaxFre) SweepMinFre=SweepMaxFre;//数据限制
			if(SweepMinFre<0) SweepMinFre=0;
			sprintf(fre_buf, "%9d", SweepMinFre);//数据重新写入
		}
		//显示
		sprintf(showstr, "%9d", SweepMinFre);//重新申请缓存显示
		fre_buf_change(showstr);//fre_buf当中 ‘ '->'0'
		if(Param_Mode == 0) Copybuf2dis(showstr, display, P_Index, 0, 1);
		else Copybuf2dis(showstr, display, P_Index, 0, 0);
		OLED_ShowString(64-4*11+16, 2, display);
		LCD_Show_CEStr(64-4*11+9*8+16,2,"Hz");
		LCD_Show_CEStr(0,2,"Min:");
		
		if(Param_Mode == 1)//最大频率设置
		{
			P_Index %= 9;//参数位数
			SweepMaxFre = atol(fre_buf);//字符转换
			if(SweepMaxFre>100000000) SweepMaxFre=100000000;//数据限制
			if(SweepMaxFre<0) SweepMaxFre=0;
			sprintf(fre_buf, "%9d", SweepMaxFre);//数据重新写入
		}
		//显示
		sprintf(showstr, "%9d", SweepMaxFre);//重新申请缓存显示
		fre_buf_change(showstr);//fre_buf当中 ‘ '->'0'
		if(Param_Mode == 1) Copybuf2dis(showstr, display, P_Index, 0, 1);
		else Copybuf2dis(showstr, display, P_Index, 0, 0);
		OLED_ShowString(64-4*11+16, 4, display);
		LCD_Show_CEStr(64-4*11+9*8+16,4,"Hz");
		LCD_Show_CEStr(0,4,"Max:");
		
		if(Param_Mode == 2)//频率步进设置
		{
			P_Index %= 5;//参数位数
			SweepStepFre = atol(fre_buf);//字符转换
			if(SweepStepFre>10000) SweepStepFre=10000-1;//数据限制
			if(SweepStepFre<0) SweepStepFre=0;
			sprintf(fre_buf, "%5d", SweepStepFre);//数据重新写入
		}
		//显示
		sprintf(showstr, "%5d", SweepStepFre);//重新申请缓存显示
		fre_buf_change(showstr);//fre_buf当中 ‘ '->'0'
		if(Param_Mode == 2) Copybuf2dis(showstr, display, P_Index, 0, 1);
		else Copybuf2dis(showstr, display, P_Index, 0, 0);
		display[5]=0;//只显示4位
		OLED_ShowString(0, 6, display);
		LCD_Show_CEStr(8*5,6,"Hz");
		
		if(Param_Mode == 3)//步进时间设置
		{
			P_Index %= 3;//参数位数
			SweepTime = atol(fre_buf);//字符转换
			if(SweepTime>1000) SweepTime=1000-1;//数据限制
			if(SweepTime<0) SweepTime=0;
			sprintf(fre_buf, "%3d", SweepTime);//数据重新写入
		}
		//显示
		sprintf(showstr, "%3d", SweepTime);//重新申请缓存显示
		fre_buf_change(showstr);//fre_buf当中 ‘ '->'0'
		if(Param_Mode == 3) Copybuf2dis(showstr, display, P_Index, 0, 1);
		else Copybuf2dis(showstr, display, P_Index, 0, 0);
		display[3]=0;//只显示3位
		OLED_ShowString(64, 6, display);
		LCD_Show_CEStr(64+3*8,6,"Ms");
		//数据处理写入
		
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

