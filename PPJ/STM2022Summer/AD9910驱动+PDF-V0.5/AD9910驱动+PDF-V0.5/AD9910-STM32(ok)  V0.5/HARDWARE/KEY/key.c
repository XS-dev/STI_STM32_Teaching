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


#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "key.h"
#include "stdio.h"
//////////////////////
u32 KEY_Sys_Timer;
u32 Keycode;
//////////////////////
u32 SystemTime;
u32 KEY_Time;
u32 key_Trgtime;
u32 KEY_Trg;
u32 KEY_Cont=0;
u32 Trg_state = NO;
void key_init(void)
{
	GPIO_InitTypeDef GPIOStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	GPIOStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIOStructure.GPIO_Pin =GPIO_Pin_11 + GPIO_Pin_12 + GPIO_Pin_13 + GPIO_Pin_14 + GPIO_Pin_15;
	GPIOStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIOStructure);

	TIM_DeInit(TIM3);
	TIM_TimeBaseInitStruct.TIM_Prescaler = 71;
	TIM_TimeBaseInitStruct.TIM_Period = 999;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM3, TIM_IT_Update|TIM_IT_Trigger, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}
u32 Change_GPIOCode(void)
{
	u32 GPIO_Data;
	GPIO_Data=(((GPIOB->IDR)>>11)&0xffff)|(~(KEY1BIT+KEY2BIT +KEY3BIT +KEY4BIT+KEY5BIT));
	return GPIO_Data;
}
u32 KeyRead(void)
{
    u32 ReadData = Change_GPIOCode()^0XFFFFFFFF;   // 1
    KEY_Trg = ReadData & (ReadData ^ KEY_Cont);      // 2
    KEY_Cont = ReadData;

	if(!Trg_state) 
		key_Trgtime = KEY_Sys_Timer + T_10mS;
	if(KEY_Trg)
		Trg_state = YES;
	if(Trg_state)
	{
		if((KEY_Sys_Timer > key_Trgtime)&&(KEY_Sys_Timer<(((u32)0-T_10mS))))  //??
		{
			switch(KEY_Cont)
			{
				case K_1:{Keycode = K_1_S; break;}
				case K_2:{Keycode = K_2_S; break;} 	
				case K_3:{Keycode = K_3_S; break;}
				case K_4:{Keycode = K_4_S; break;}
				case K_5:{Keycode = K_5_S; break;}
				default:{Keycode = K_NO; break;}
			}	
			
		}
	}
	if(KEY_Time >= T_1S)	  	//
	{ 
		KEY_Time = T_1S-T_330mS;
		switch(KEY_Cont)
		{
			case K_1:{Keycode = K_1_L; break;}
			case K_2:{Keycode = K_2_L; break;} 	
			case K_3:{Keycode = K_3_L; break;}
			case K_4:{Keycode = K_4_L; break;}
			case K_5:{Keycode = K_5_L; break;}
			default:{Keycode = K_NO; break;} 
		}
	}
	return Keycode;
}
void KEY_EXIT(void)
{
	if(Keycode != K_NO)
	{
		Trg_state = NO;
		Keycode = K_NO;
	}	
}

