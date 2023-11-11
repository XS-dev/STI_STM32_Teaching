#include "task_manage.h"
#include "I2C.h"
#include "delay.h"
#include "key.h"

#define OUT_KEY  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//读取按键0


u8 Firt_In = 1;
u8 Task_Index = 0;
u8 _return=0;
extern char str[30];

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
	u16 Wel_time0 = 10,Wel_time1 = 50;
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
void LCD_Show_ModeCEInfo(u16 x0, u8 start_info, u8 current_deal_info)
{
	u8 ystart = 0;
	u8 show_mode = 1;
	switch(start_info)
	{
		case 0: if(ystart/2 == (current_deal_info - start_info)) show_mode = 0;
						else show_mode = 1;
						LCD_Show_ModeCEStr(x0,ystart, "1,电阻",show_mode);
						ystart += 2; 
						if(ystart == 6) break;
		case 1: if(ystart/2 == (current_deal_info - start_info)) show_mode = 0;
						else show_mode = 1;
						LCD_Show_ModeCEStr(x0,ystart, "2,电容",show_mode); 
						ystart += 2; 
						if(ystart == 6) break;
		case 2: if(ystart/2 == (current_deal_info - start_info)) show_mode = 0;
						else show_mode = 1;
						LCD_Show_ModeCEStr(x0,ystart, "3,电感",show_mode); 
						ystart += 2; 
						if(ystart == 6) break;
	}
}
void Main_Menu(u32 Key_Value, u8* Task_ID)
{
	u8 show_line_first = 0;
	if(Firt_In)
	{
		Firt_In = 0;
		Task_Index = 0;
		LCD_Clear();
		LCD_Show_ModeCEStr(10,0, "1,电阻",0);
		LCD_Show_ModeCEStr(10,2, "2,电容",1);
		LCD_Show_ModeCEStr(10,4, "3,电感",1);
	
		LCD_Show_CEStr(0,6,"↓    确认    ↑");
		_return=1;
	}
	switch(Key_Value)
	{
		case K_1_S: Task_Index++; break;
		case K_1_L: Task_Index++; break;
		case K_3_S: Task_Index++; break;
		case K_3_L: Task_Index++; break;
//		case K_2_L: *Task_ID = Task_Index; Firt_In = 1; break;
		case K_2_S:  *Task_ID = Task_Index; Firt_In = 1; break;
		case K_4_S: Task_Index--; break;
		case K_4_L: Task_Index--; break;
		case K_5_S: Task_Index--; break;
		case K_5_L: Task_Index--; break;
	}
	if(Task_Index == 255)
		Task_Index = 0;
	if(Task_Index >= (Max_Task-1))
		Task_Index = Max_Task-1;
	if(Key_Value != K_NO)
	{
		show_line_first = Task_Index - 2;
		if(show_line_first > 200)
			show_line_first = 0;
		LCD_Show_ModeCEInfo(10, show_line_first, Task_Index);
	}
}
void Copybuf2dis(u8 *source, u8 dis[10], u8  dispoint)
{
	dis[0] = *source + '0';
	dis[1] = *(source+1) + '0';
	dis[2] = *(source+2) + '0';
	dis[3] = *(source+3) + '0';
	dis[4] = '.';
	dis[5] = *(source+4) + '0';
	dis[6] = 'M';
	dis[7] = 0;
//	if(dispoint < 4) dis[dispoint] += 128;
//	else if(dispoint == 4) dis[dispoint+1] += 128;
}

void Get_Rs(u32 Key_Value, u8* Task_ID)
{
	float Rs;
	if(Firt_In) 
	{
		LCD_Clear();
		LCD_Show_CEStr(0,0,"    电阻测量    ");
		LCD_Show_CEStr(0,6,"     返回       ");
		Firt_In = 0;		
		_return=1;		
	}
	Rs=DA5933_Get_Rs();
	if(Rs>15000000)
	{
		sprintf(str,"   0LΩ  ",Rs/1000000);
	}else if(Rs>1000000)
	{
		sprintf(str,"%03.03fMΩ  ",Rs/1000000);
	}else	if(Rs>1000)
	{
		sprintf(str,"%03.03fKΩ  ",Rs/1000);
	}else if(Rs<1000)
	{
		sprintf(str,"%03.03fΩ  ",Rs);
	}
	LCD_Show_CEStr(20,2,str);
	_return=1;
	switch(Key_Value)
	{
		case K_2_L: *Task_ID = Max_Task; Task_Index = 0; Firt_In = 1;break;
		case K_2_S: *Task_ID = Max_Task; Task_Index = 0; Firt_In = 1;break;
	}
}
void Get_Cap(u32 Key_Value, u8* Task_ID)
{
	float Cap;
	if(Firt_In) 
	{
		LCD_Clear();
		LCD_Show_CEStr(0,0,"    电容测量    ");
		LCD_Show_CEStr(0,6,"     返回       ");
		Firt_In = 0;		
		_return=1;		
	}
	Cap=DA5933_Get_Cap(10000);
	if(Cap>1000000)
	{
		sprintf(str,"%03.03fuF  ",Cap/1000000);
	}else	if(Cap>1000)
	{
		sprintf(str,"%03.03fnF  ",Cap/1000);
	}else if(Cap<1000)
	{
		sprintf(str,"%03.03fpF  ",Cap);
	}
	LCD_Show_CEStr(20,2,str);
	_return=1;
	switch(Key_Value)
	{
		case K_2_L: *Task_ID = Max_Task; Task_Index = 0; Firt_In = 1;break;
		case K_2_S: *Task_ID = Max_Task; Task_Index = 0; Firt_In = 1;break;
	}
}
void Get_L(u32 Key_Value, u8* Task_ID)
{
	float L;
	if(Firt_In) 
	{
		LCD_Clear();
		LCD_Show_CEStr(0,0,"    电感测量    ");
		LCD_Show_CEStr(0,6,"     返回       ");
		Firt_In = 0;		
		_return=1;		
	}
	L=DA5933_Get_L(100000);
	if(L>1000000)
	{
		sprintf(str,"%03.03fmH  ",L/1000000);
	}else	if(L>1000)
	{
		sprintf(str,"%03.03fuH  ",L/1000);
	}else if(L<1000)
	{
		sprintf(str,"%03.03fnH  ",L);
	}
	LCD_Show_CEStr(20,2,str);
	_return=1;
	switch(Key_Value)
	{
		case K_2_L: *Task_ID = Max_Task; Task_Index = 0; Firt_In = 1;break;
		case K_2_S: *Task_ID = Max_Task; Task_Index = 0; Firt_In = 1;break;
	}
}
