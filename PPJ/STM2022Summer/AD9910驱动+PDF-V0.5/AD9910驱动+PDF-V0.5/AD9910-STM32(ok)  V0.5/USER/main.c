/**********************************************************
                       ��������
										 
���ܣ�stm32f103rct6����
			��ʾ��12864
�ӿڣ�
AD9910ģ��							STM32��Ƭ���ӿ�
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

ʱ�䣺2015/11/3
�汾��1.0
���ߣ���������
������

������������뵽�Ա��꣬�������ӽ߳�Ϊ������ ^_^
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

char str[30];	//��ʾ����
extern u8 _return;
int main(void)
{
	u16 i=0;

	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2);	//�����жϷ���
	delay_init(72);	//��ʼ����ʱ����
	LED_Init();	//��ʼ��LED�ӿ�
	key_init();//������ʼ��
	initial_lcd();//Һ����ʼ��
	LCD_Clear();
	delay_ms(300);
	LCD_Refresh_Gram();
	
	Timerx_Init(99,71);
	
	LCD_Clear();
	LCD_Show_CEStr(0,0,"5");//��ɫ orange
	
	Init_ad9910();//9910��ʼ��
	Freq_convert(1000000);//дƵ��1MHz
	AD9910_AmpWrite(16383);//0X0000~16383��Ӧ���ֵ0mv~800mv(����)
	
	//1��
	//���������漰���漰�����������ܣ�Ƶ�ʻ���Ȼ������������ܱ���д�����ܵ���������Ĳ�����Ч
	//���������ȡ������ע�ͼ��ɣ���ֱ�Ӹ���Ƶ�ʼ����ȣ�
//	Freq_convert(10000);	//дƵ��10kHz
//	AD9910_AmpWrite(16383);//0X0000~16383��Ӧ���ֵ0mv~800mv(����)
//	while(1);

	//2��
//	����ɨƵ��˵��
//	�ó����ɨƵ�������ö�ʱ���жϣ�����д���Լӵ�Ƶ��ʵ�֣�
//	��timer.C��TIM4_IRQHandler�н��ԼӺ��Ƶ��д��
	while(1)
	{
		KeyRead();//��ȡ����ֵ ���ڲ���ע���꣬���ùܣ� 
		Set_PointFre(Keycode, 0);//��������
		if(_return){_return=0;LCD_Refresh_Gram();}//������ʾ
		KEY_EXIT();
	}	
}

