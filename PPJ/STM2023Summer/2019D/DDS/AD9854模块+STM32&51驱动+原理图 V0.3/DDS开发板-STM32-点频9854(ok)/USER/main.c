
/**********************************************************
                       �����Ƽ�
											 
//Ӳ������: PC7~-PC0    ����Data;	  
//          PC13~PC8   ����Adr;    
//          RESET ����PA6;     
//          UDCLK ����PA4;   
//          WR    ����PA5;	  
//          RD    ����PA8;    
//          FDATA ����PB10;     
//          OSK   ����PA2;  
//          VDD--�߼���Դ(3.3V)
//          VSS--GND(0V)  

������������뵽�Ա��꣬�������ӽ߳�Ϊ������ ^_^
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

char str[30];	//��ʾ����
extern u8 _return;
int main(void)
{
	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2);	//�����жϷ���
	delay_init(72);	//��ʼ����ʱ����
	LED_Init();	//��ʼ��LED�ӿ�
	key_init();
	initial_lcd();
	LCD_Clear();
	delay_ms(300);
	LCD_Refresh_Gram();
	
	Timerx_Init(99,71);//��ʱ��
	LCD_Clear();


	AD9854_Init();
	AD9854_SetSine_double(1000000,4095);//дƵ��1M Hz,0X0000~4095��Ӧ���ֵ0mv~550mv(����)
	
	
	//1��
	//���������漰���漰�����������ܣ�Ƶ�ʻ���Ȼ������������ܱ���д�����ܵ���������Ĳ�����Ч
	//���������ȡ������ע�ͼ��ɣ���ֱ�Ӹ���Ƶ�ʼ����ȣ�
////	AD9854_SetSine_double(1000000,4095);//дƵ��1M Hz,0X0000~4095��Ӧ���ֵ0mv~550mv(����)
////	while(1);
	
	//2��	
//	����ɨƵ��˵��
//	�ó����ɨƵ�������ö�ʱ���жϣ�����д���Լӵ�Ƶ��ʵ�֣�
//	��timer.C��TIM4_IRQHandler�н��ԼӺ��Ƶ��д��

	while(1)
	{
		KeyRead();
		Set_PointFre(Keycode, 0);
		if(_return){_return=0;LCD_Refresh_Gram();}
		KEY_EXIT();
	}	
}

