
/**********************************************************
                       康威科技
											 
//硬件连接: PC7~-PC0    ——Data;	  
//          PC13~PC8   ——Adr;    
//          RESET ——PA6;     
//          UDCLK ——PA4;   
//          WR    ——PA5;	  
//          RD    ——PA8;    
//          FDATA ——PB10;     
//          OSK   ——PA2;  
//          VDD--逻辑电源(3.3V)
//          VSS--GND(0V)  

更多电子需求，请到淘宝店，康威电子竭诚为您服务 ^_^
https://kvdz.taobao.com/
**********************************************************/

#include "stm32_config.h"
#include "stdio.h"
#include "led.h"
#include "lcd.h"
#include "AD9854.h" 
#include "key.h"
#include "task_manage.h"
#include "timer.h"

char str[30];	//显示缓存
extern u8 _return;
int main(void)
{
	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2);	//设置中断分组
	delay_init(72);	//初始化延时函数
	LED_Init();	//初始化LED接口
	key_init();
	initial_lcd();
	LCD_Clear();
	delay_ms(300);
	LCD_Refresh_Gram();
	
	Timerx_Init(99,71);//定时器
	LCD_Clear();


	AD9854_Init();
	AD9854_SetSine_double(1000000,4095);//写频率1M Hz,0X0000~4095对应峰峰值0mv~550mv(左右)
	
	
	//1、
	//后续代码涉及界面及按键交互功能，频率或幅度或其他参数可能被重写，可能导致上面更改参数无效
	//上述情况，取消下面注释即可，可直接更改频率及幅度，
////	AD9854_SetSine_double(1000000,4095);//写频率1M Hz,0X0000~4095对应峰峰值0mv~550mv(左右)
////	while(1);
	
	//2、	
//	关于扫频的说明
//	该程序的扫频功能利用定时器中断，不断写入自加的频率实现，
//	在timer.C的TIM4_IRQHandler中将自加后的频率写入

	while(1)
	{
		KeyRead();
		Set_PointFre(Keycode, 0);
		if(_return){_return=0;LCD_Refresh_Gram();}
		KEY_EXIT();
	}	
}

