/**********************************************************
                       ��������
										 
���ܣ�stm32f103rct6����
			��ʾ��12864
�ӿڣ������ӿ������key.h
ʱ�䣺2015/11/3
�汾��1.0
���ߣ���������
������

������������뵽�Ա��꣬�������ӽ߳�Ϊ������ ^_^
https://shop110336474.taobao.com/?spm=a230r.7195193.1997079397.2.Ic3MRJ

**********************************************************/


#include "led.h"

/**********************************************************
* �������� ---> LED�ӿڳ�ʼ��
* ��ڲ��� ---> none
* ���ز��� ---> none 
* ����˵�� ---> none
**********************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);	//����GPIOC����ʱ��	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA, GPIO_Pin_15);	//����ߵ�ƽ��Ϩ���
	GPIO_SetBits(GPIOB, GPIO_Pin_2);	//����ߵ�ƽ��Ϩ���
}

