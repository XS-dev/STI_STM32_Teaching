/**********************************************************
                       康威电子
										 
功能：stm32f103rct6控制
			显示：12864
接口：
AD9910模块							STM32单片机接口
AD9910_PWR							PCout(13)
AD9910_SDIO							PAout(5)
DRHOLD									PCout(1)
DROVER									PCout(2)
UP_DAT									PCout(3)
PROFILE1								PCout(10)
MAS_REST								PAout(6)
SCLK										PAout(2)
DRCTL 									PAout(4)
OSK											PCout(8)
PROFILE0								PCout(4)
PROFILE2								PCout(5)
CS 											PBout(10)
GND											GND

时间：2015/11/3
版本：1.0
作者：康威电子
其他：

更多电子需求，请到淘宝店，康威电子竭诚为您服务 ^_^
https://shop110336474.taobao.com/?spm=a230r.7195193.1997079397.2.Ic3MRJ

**********************************************************/

#include "stm32_config.h"
#include "stdio.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "AD9910.h"
#include "task_manage.h"
#include "timer.h"

char str[30];	//显示缓存
extern u8 _return;
int main(void)
{
	u16 i=0;

	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2);	//设置中断分组
	delay_init(72);	//初始化延时函数
	LED_Init();	//初始化LED接口
	key_init();//按键初始化
	initial_lcd();//液晶初始化
	LCD_Clear();
	delay_ms(300);
	LCD_Refresh_Gram();
	
	Timerx_Init(99,71);
	
	LCD_Clear();
	LCD_Show_CEStr(0,0,"5");//橙色 orange
	
	Init_ad9910();//9910初始化
	Freq_convert(1000000);//写频率1MHz
	AD9910_AmpWrite(16383);//0X0000~16383对应峰峰值0mv~800mv(左右)
	
	//1、
	//后续代码涉及界面及按键交互功能，频率或幅度或其他参数可能被重写，可能导致上面更改参数无效
	//上述情况，取消下面注释即可，可直接更改频率及幅度，
//	Freq_convert(10000);	//写频率10kHz
//	AD9910_AmpWrite(16383);//0X0000~16383对应峰峰值0mv~800mv(左右)
//	while(1);

	//2、
//	关于扫频的说明
//	该程序的扫频功能利用定时器中断，不断写入自加的频率实现，
//	在timer.C的TIM4_IRQHandler中将自加后的频率写入
	while(1)
	{
		KeyRead();//读取按键值 （内部备注不详，不用管） 
		Set_PointFre(Keycode, 0);//按键处理
		if(_return){_return=0;LCD_Refresh_Gram();}//更新显示
		KEY_EXIT();
	}	
}

