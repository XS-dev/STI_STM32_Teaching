#include "JDqi.h"


void JD_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructurejd0;
	GPIO_InitTypeDef GPIO_InitStructurejd1;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	

	GPIO_InitStructurejd0.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructurejd0.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructurejd0.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructurejd0);
	
	
	GPIO_InitStructurejd1.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructurejd1.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructurejd1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructurejd1);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_9|GPIO_Pin_13|GPIO_Pin_15);//初始情况全部断开
	GPIO_SetBits(GPIOC,GPIO_Pin_7);

}
