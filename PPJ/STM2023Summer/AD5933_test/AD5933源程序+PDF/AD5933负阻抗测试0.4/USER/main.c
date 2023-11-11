/**********************************************************
                       ��������
										 
�汾��0.4
���ߣ���������
�������˳�������ο������辫ȷ����������У׼

������������뵽�Ա��꣬�������ӽ߳�Ϊ������ ^_^
https://shop110336474.taobao.com/?spm=a230r.7195193.1997079397.2.Ic3MRJ

**********************************************************/

#include "stm32_config.h"
#include "task_manage.h"
#include "led.h"
#include "lcd.h"
#include "I2C.h"
#include "key.h"

u8 Task_ID = Max_Task;
char str[30];
extern u32 SysTimer;
extern u32 Keycode;
extern	u8 _return;
/**********************************************************
                           ������
**********************************************************/

int main(void)
{
	u16 LED_time=0;
	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2);	//�����жϷ���
	delay_init(72);	//��ʼ����ʱ����
	LED_Init();	//��ʼ��LED�ӿ�
	key_init();
	initial_lcd();
	LCD_Clear();
	LCD_Refresh_Gram();
	
	while (1)
	{
		LED_time++;
		KeyRead();
		switch(Task_ID)
		{
			case Max_Task: Main_Menu(Keycode, &Task_ID); break;
			case 0: Get_Rs(Keycode, &Task_ID);break;
			case 1: Get_Cap(Keycode, &Task_ID);break;
			case 2: Get_L(Keycode, &Task_ID);break;
		}
		if(Keycode != K_NO)LCD_Refresh_Gram();
		if(_return){_return=0;LCD_Refresh_Gram();}
		if(LED_time>10000){LED1=!LED1;LED_time=0;}
		KEY_EXIT();
	}
}

